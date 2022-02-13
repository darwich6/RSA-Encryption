/***
   prepared for CS435 Project 1 part 2
**/

#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

 
int main(int argc, char *argv[])
{
   //demonstrating how sha256 works
   /*std::string input = "testing";
   std::string output1 = sha256(input);
   std::cout << "sha256('"<< input << "'):" << output1 << "\n"; */
   
   //demo bigInt works here
   /*BigUnsigned a = stringToBigUnsigned("124338907642982722929222542626327282");
   BigUnsigned b = stringToBigUnsigned("124338907642977775546469426263278643");
   std::cout << "big a = " <<a<<"\n";
   std::cout << "big b = " <<b<<"\n";
   std::cout << "big a*b = " <<a*b<<"\n";
   BigUnsigned c = BigUnsignedInABase("ABC",16);
   std::cout << "big c = " <<c<<"\n"; */

   //Second part of your project starts here
   //Remove this its for undergrad students
   //if ((argc != 3 || argv[1][0]!='s') && (argc !=4 || argv[1][0]!='v')) 
      //std::cout << "wrong format! should be \"a.exe s filename\" or \"a.exe v filename signature\"" << "\n";
   // for graduate students  
   if ((argc != 3 || argv[1][0]!='s') && (argc !=3 || argv[1][0]!='v')) 
      std::cout << "wrong format! should be \"a.exe s filename\" or \"a.exe v filename.signed\""; 
   else {
      
      // work on your part2, my code here is just for illustration; don't rely on it
   
      std::string filename = argv[2];
      /*if (argv[1][0] == 'v')
           std::string filename_sig = argv[3];*/
            
      //read the file
      std::streampos begin,end;
      std::ifstream myfile (filename.c_str(), std::ios::binary);
      begin = myfile.tellg();
      myfile.seekg (0, std::ios::end);
      end = myfile.tellg();
      std::streampos size = end-begin;
      //std::cout << "size of the file: " << size << " bytes.\n"; //size of the file
      
      myfile.seekg (0, std::ios::beg);
      char * memblock = new char[size];
      myfile.read (memblock, size); //read file; it's saved in the char array memblock
      myfile.close();
      
      //to illustrate the file was read correctly.
      std::string copyOFfile = filename+".Copy"; 
      std::ofstream myfile2 (copyOFfile.c_str(), std::ios::binary);
      myfile2.write (memblock, size); //write to a file
      myfile2.close();
      
      //Test to see what memblock looks like
      //std::cout<< "Memblock: \n" << memblock;

      //Lets grab our private and public keys from the txt files e_n.txt and d_n.txt
      std::fstream inputFile1("d_n.txt");
      std::fstream inputFile2("e_n.txt");
      std::string currentLine1, currentLine2;
      BigUnsigned d;
      BigUnsigned e;
      BigUnsigned n1, n2;
      if(inputFile1.is_open() && inputFile2.is_open()){
         //get d
         getline(inputFile1, currentLine1);
         d = stringToBigUnsigned(currentLine1);
         //get e
         getline(inputFile2, currentLine2);
         e = stringToBigUnsigned(currentLine2);
         // get n from e
         getline(inputFile1, currentLine1);
         n1 = stringToBigUnsigned(currentLine1);
         //get n from d
         getline(inputFile2, currentLine2);
         n2 = stringToBigUnsigned(currentLine2);
         // make sure the n's are the same. They should be.
         if(n1.compareTo(n2) == 0){
            std::cout << "\n Read files correctly, n from e_n.txt and d_n.txt are equal \n";
         } else {
            std::cerr << "Error: n values are not the same from e_n.txt and d_n.txt \n";
         }
      } else {
         std::cerr << "Error: opening input files \n";
      }
      inputFile1.close();
      inputFile2.close();
        
      if (argv[1][0]=='s') {
         std::cout << "\n"<<" Need to sign the doc.\n";
         std::cout << "\n"<<" Signing the document... \n";
         //Generate a SHA‐256 hash of the content of the file to be signed (e.g., "file.txt");
         // The Sha256 function returns a string in hexadecimal
         std::string hashedContentHex = sha256(memblock);
         //We must convert the hashedContent from hex to base 10
         BigUnsigned hashedContentDec = BigUnsignedInABase(hashedContentHex, 16);

         // Test to see that the conversion worked successfully. It does.
         // std::cout << " Hashed Content Hex: \n" << hashedContentHex;
         // std::cout << "\n Hashed Content Dec: \n" << hashedContentDec << "\n";
         
         // Now sign "decrypt" the hash value using the private key stored in d_n.txt.
         // d is the private key, use the n from d_n.txt file (n2). Either works since
         // they are the same but lets remain consistent.
         BigUnsigned signature = modexp(hashedContentDec, d, n2);
         // std::cout << " Signature: \n" << signature << "\n";

         // Now save the original content of the file and the signature into one file
         // named file.txt.signature
         std::string sigFileName = filename + ".signed";
         //Test to see that the filename was produced correctly
         // std::cout << " Signature File Name: " << sigFileName << "\n";
         //create the file to write too
         std::ofstream finalFile(sigFileName.c_str(), std::ios::binary);
         // make sure the file is open and write to it
         if(finalFile.is_open()){
            finalFile << memblock;
            //convert the bigUnsigned to a string so that way you can write it to the fiel
            std::string signatureString = bigUnsignedToString(signature);
            finalFile << signatureString;
            finalFile.close();
            std::cout << "\n Document is signed. \n";
            std::cout << " Signature File Name: " << sigFileName << "\n";
         } else{
            std::cerr << "Unable to open: " << sigFileName << "\n";
         }
      }
      else {
         std::cout << "\n"<<" Need to verify the doc.\n";
         std::cout << " Verfying the document. \n";
         //Separate the signature from the content of the file in the signed document (e.g. "file.txt.signed");
         //filename stores the string of the signed document name
         std::ifstream comboFile(filename.c_str());
         char currentChar;
         std::string content;
         std::string signature;
         //while we aren't at the end of the file
         while(!comboFile.eof()){
            //grab the current char
            currentChar = comboFile.get();
            //if it is the new line, our delimeter in this case
            if(currentChar == '\n'){
               //the next line would be the signature
               getline(comboFile, signature);
            }
            //else the character is apart of the content
            content += currentChar;
         }
         //test to see if we actually grabbed the right parts of the file
         // it worked :)
         //std::cout << "Content: " << content << "\n";
         //std::cout << "Signature: " << signature << "\n";

         // "encrypt" signature using the public key stored in e_n.txt;
         // Do this using the modexp function
         // To do this, use modexp with the public key e
         // convert the string to a big integer
         BigInteger signatureBig = stringToBigInteger(signature);
         //Test to see what the values look like.
         //std::cout << "signatureBig: " << signatureBig << "\n";
         //std::cout << "e: " << e << "\n";
         //std::cout << "n: " << n1 << "\n";
         BigUnsigned encryptedValue = modexp(signatureBig, e, n1);

         //compare the encrypted value to the hashedcontent
         std::string hashedContentHex = sha256(content);
         //std::cout << "HashedContentHex: " << hashedContentHex << "\n";
         //convert this hexadecimal to base 10
         BigUnsigned hashedContentDec = BigUnsignedInABase(hashedContentHex, 16);
         //std::cout << "HashedContentDec: " << hashedContentDec << "\n";

         // Test to see how they look
         //std::cout << "\n Hashed Content Final: " << hashedContentDec << "\n";
         //std::cout << " Encrypted Signature: " << encryptedValue << "\n";

         //Report on whether the document is authentic or modified.
         if(hashedContentDec == encryptedValue){
            std::cout << "\n \n Document is authentic. \n";
         } else{
            std::cout << "\n \n Document is modified. \n";
         }

      }
      delete[] memblock;
    }
    return 0;
}
