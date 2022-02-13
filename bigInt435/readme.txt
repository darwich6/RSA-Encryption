Ahmed Darwich
Algorithms 435/535

Part 1: RSA Key Generation

High Level Explanation:
This executable generates values for an RSA key encryption and writes them to a file in their respective directories. It starts by utilizing the BigUnsigned
library to generate a value of 1. This value then enters a loop in which the value is multiplied by ten and summed with a random number. The loop iteration 
is based on user input that refers to the total number of digits that the value should result in. Therefore, for our P and Q number generation, we looped 
154 times which should generate a P and Q value of at least 512 bits. Furthermore, P and Q should both be prime. In order to generate such large prime 
numbers, a fermat's test was implemented. This fermat's test function was then utilized to ensure that the BigUnsigned numbers generated for both P and Q 
were prime. Once confirmed that they were prime, the values generated for P and Q were written to a text file named p_q.txt in ../bigInt435. Additionally, 
the Extended Euclidean algorithm was used to generate two pairs of key reliant on P and Q called e and d. The pairs (e,n)and (d,n) were generated where n 
is the result of multiplying p and q. Another value, phi, was generated as the result of (p-1) multiplied with (q-1). We know that e is a coprime to the 
phi value, so we generated a large BigUnsigned with a number of digits of 67, and we checked to see if that value and phi had a greatest common 
denominator of 1. If it did not, we continued to add 2 to the value of e until it did. The value stored in d was then calculated as the mod inverse of e 
and phi. This values were then written to their respective text files where e_n.txt and d_n.txt exist in the directories ../bigInt435. Testing of values 
were written to std::cout and commented out once process was determined successgul.

Running The Program:
1.) Ensure you are in ../bigInt435
2.) Run "make clean"
3.) Run "make"
4.) Run "./rsa435" and wait for "Completed generation" message on command line
5.) Values should be written to "p_q.txt", "e_n.txt", "d_n.txt" in ../bigInt
