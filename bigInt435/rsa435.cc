// You need to complete this program for the first part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdlib.h> 
#include <fstream>


// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

/* Function that returns a boolean value based on the result
 of Fermats Test */
bool fermatTest(BigUnsigned testNum, int base){
   return(modexp(base, testNum - 1, testNum) == 1);
}

/* Function that generates a large prime number of demical digits
   according to input. Prime validness checked by using Fermat's test */
BigUnsigned bigNumGenarator(int numDigits){
   //declare the returnValue
   BigUnsigned returnValue = BigUnsigned(1);
   //make it the correct number of digits by looping and multypling 10
   for(int i = 0; i < numDigits; i++){
      returnValue = returnValue * 10 +rand();
   }
   return returnValue;
}

//Function that writes the p,q numbers into both directories
void writePQ(BigUnsigned p, BigUnsigned q){
   std::ofstream pqFile("p_q.txt", std::ofstream::out);
   //Do not need to write to this file
   //std::ofstream pqFile2("..//messageDigest435//p_q.txt", std::ofstream::out);
   if(pqFile.is_open()){
      pqFile << p << "\n";
      pqFile << q << "\n";
      pqFile.close();
   } else {
      std::cout << "Problem with opening file p_q.txt";
   }
}

//Function that writes the e_n.txt and d_n.txt files in both directories
void writeENDN(BigUnsigned e, BigUnsigned d, BigUnsigned n){
   std::ofstream enFile("e_n.txt", std::ofstream::out);
   //Do not need to write to this directory. Professor will input her own values.
   //std::ofstream enFile2("..//messageDigest435//e_n.txt", std::ofstream::out);
   if(enFile.is_open()){
      enFile << e << "\n";
      enFile << n << "\n";
      enFile.close();
   } else {
      std::cout << "Problem with opening file e_n.txt";
   }
   std::ofstream dnFile("d_n.txt", std::ofstream::out);
   //Do not need to write to this directory. Professor will input her own values.
   //std::ofstream dnFile2("..//messageDigest435//d_n.txt", std::ofstream::out);
   if(dnFile.is_open()){
      dnFile << d << "\n";
      dnFile << n << "\n";
      dnFile.close();
   } else {
      std::cout << "Problem with opening file d_n.txt";
   }
}

int main(){
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */
	try {

      /* Examples and test cases for use of libraries      
      std::cout << "a couple of test cases for 3460:435/535 Algorithms!!!\n";
      BigUnsigned big1 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big1 = big1*10 +rand();
      }
      std::cout << "my big1 !!!\n";
      std::cout << big1;
      BigUnsigned big2 = BigUnsigned(1);
      for (int i=0;i<400;i++) {
         big2 = big2*10 +rand();
      }
      std::cout << "\nmy big2 !!!\n";
      std::cout << big2;
      std::cout << "\nmy big3 = big1*big2 !!!\n";
      BigUnsigned big3 = big1*big2;
      std::cout <<big3;
      std::cout << "\nmy big3/big2 !!!\n";
      std::cout <<big3/big2;
      
      std::cout <<"\nABC\n";
      BigUnsignedInABase abc = BigUnsignedInABase("ABC", 16);
      std::cout <<"\n***********\n";
      std::cout <<std::string(abc)<<"\n";
      BigUnsigned abc10 = abc;
      std::cout <<abc10<<"\n"; */
      
      //Send message to ensure generating 
      std::cout << "Genarating RSA Keys... \n";

      // generate p and see if it is prime
      BigUnsigned p = bigNumGenarator(154);
      // See what P is 
      // std::cout << "\n P: \n" << p;
      BigUnsigned q = bigNumGenarator(154);
      // See what Q is
      // std::cout << "\nQ: \n" << q;

      // We want to ensure p and q are prime and is relatively prime to 3 and 5
      // Test to see if p is prime
      bool pCheck = (p % 2 != 0) && fermatTest(p, 3) && fermatTest(p, 5);
      // std::cout << "\n Is P prime: " << pCheck;
      // Test to see if p is prime
      bool qCheck = (q % 2 != 0) && fermatTest(q, 3) && fermatTest(q, 5);
      // std::cout << "\n Is q prime: " << qCheck;

      //So if p isnt prime, we need to loop until it is are
      while(!pCheck){
         p = bigNumGenarator(154);
         if((p % 2 != 0) && (fermatTest(p, 3)) && (fermatTest(p, 5))){
            pCheck = true;
         }
      }
      
      // Check to see if P is actually prime
      //std::cout << "\n P: " << p;
      //std::cout << "\n Is P prime: " << pCheck;

      //So if q isnt prime, we need to loop until it is are
      while(!qCheck){
         q = bigNumGenarator(154);
         if((q % 2 != 0) && (fermatTest(q, 3)) && (fermatTest(q, 5))){
            qCheck = true;
         }
      }

      // Check to see if Q is actually prime
      //std::cout << "\n Q: " << q;
      // std::cout << "\n Is Q prime: " << qCheck;
      
      //write p,q to its respective directories
      writePQ(p,q);

      //Use the extended Euclidean algorithm to generate two pairs of keys: (e,n), (d,n), where n=p*q;
      BigUnsigned n = p*q;
      //see n to compare to txt files
      //std::cout << "\n n: " << n;
      //calculate phi
      BigUnsigned phi = (p-1)*(q-1);
      // Tested "BigUnsigned e = 65537;" first and was successful
      BigUnsigned e = bigNumGenarator(67);
      //e and phi need to be coprimes, best way to check that is if their gcd is equal to 1, if not add two to e
      while(gcd(e, phi) != 1){
         e = e+2;
      }
      // Test to see if these are actually coprimes
      //std::cout << "\n e: " << e;
      //std::cout << "\n phi: " << phi << "\n";
      // are they coprimes though
      //bool ePhiTest = (gcd(e, phi) == 1);
      // if 1, they are coprimecd
      //std::cout << "\n Coprime Test for e and Phi: " << ePhiTest << "\n";
      // Now we need to calculate d which is the mod inverse of e and phi
      BigUnsigned d = modinv(e, phi);
      //std::cout << " d: " << d << "\n";

      //write e_n.txt and d_n.txt
      writeENDN(e, d, n);

      std::cout << "Completed generation.\n";

      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl; 
	}

	return 0;
}
