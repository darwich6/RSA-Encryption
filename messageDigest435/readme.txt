Ahmed Darwich
Algorithms 435/535

Part 2: Generate and Verify Digital Signatures using a SHA‐256 hash.

High Level Explanation:
This executable generates and verfies digital signatures using a SHA‐256 hash. Note, all values are written to command
line to showcase flow and validation.

Signing:
Initially based on user input, a file of the form "file.txt" is passed to be signed. It must be signed using the private key 
stored in "d_n.txt". The implementation first reads in the files "d_n.txt" and "e_n.txt" as d will serve as our private key
for signing and e will serve as our public key for verfying. It checks to see if the values of n in both files are the same, 
ensuring the read was correct. The content of the file passed to be signed are read in and stored in a variable named memblock. 
The content stored in memblock is then hashed according to the SHA‐256 library. A link to the library and its documentation 
is provided below for review. This returns a string in base 16 and is then converted to a BigUnsigned variable in base 10.
Furthermore, the signature is not just the value of but rather the mod exp of the Hashed Content in base 10 as the base, 
d as the exponent, and n as the modulus. Now the program has both the signature and the content. It writes these to file 
named "file.txt" + ".signed" where "file.txt" is the user input of the file given to be signed. Thus, both the original content
and the signature are written to "file.txt.signed".

Verfying:
To verify the document, the content and the signature must both be read from the user input. My implementation accomplishes
this by looping over the characters of the input file while searching for the delimiter, "\n", between the content and the 
signature. If the delimiter is found, then we know the next line is the signature and thus it is stored. Any other character 
before the delimiter is considered to be apart of the content and is thus appended to that content string variable. In order to 
verify the signature, the string must be convered to a BigUnsigned. This is then run through the opposite of the modexp ran 
when signing where the signature is now the base, e is the exponent, and n is the modulus. This essentially "encrypts" the 
signature using the public key, e. Then the program looks to the content. A hashed version of the content is generated using 
SHA‐256 function and the encrpyted signature and the hashed content are then compared. If they are the same, the program 
reports that the document is authentic, else the document is modified. 

Running The Program:
1.) Ensure you are in ../messageDigest435
2.) Ensure that ../messageDigest435 has files "p_q.txt", "e_n.txt", and "d_n.txt" in it
2.) Run "make clean"
3.) Run "make"
    To Sign: 
        4.) Run "./messageDigest435 s 'file.txt'" 
        5.) Wait for "Document is signed." to show on command line
        6.) The file signed should be shown after "Signature File Name: "file.txt.signed"
        6.) Open "file.txt.signed" to view content and signature
    To Verify:
        7.) Ensure that "file.txt.signed" exists in ../messageDigest435
        8.) Run "./messageDigest435 v "file.txt.signed"
        9.) Wait for resulting message on terminal to show success or failure
        Success --> "Document is authentic."
        Failure --> "Document is modified."

Resources:
http://www.zedwood.com/article/cpp-sha256-function
