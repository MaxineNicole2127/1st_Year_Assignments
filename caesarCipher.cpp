/*****************************************************
    MAXINE NICOLE B. BERNALES
    CSMC121 ZC11 (Discrete Structures 2)
    2.25.2023
    E5[+m, *m]

    Program Description: Allows user to input a string and a key, and apply caesar encryption to the string to encrypt and decrypt it.
    Implemented:
    - Math
    - Command-Line Arguments
    - Exception handling
*****************************************************/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int mod(float a, float d){
    return a-(d*floor(a/d));
}

void encrypt(string str, int k, string &NewStr){ //change value of encrypted string and display the decimal equivalent in the ASCII table of each of its letter
    printf("   [");
    for(int i=0; i<str.length(); i++){
        int p = (int)str[i]; //initialize p to the current decimal equivalent of the letter
        int n = mod(p+k,127); //initialize n to the modulo of p+k and 127

        if(p+k>126) n+=32; //adds the modulo to 32 if p+k exceeds 126

        printf("%d",n-32);
        if(i!=str.length()-1) printf(",");

        NewStr+=(char)n; //concatenate the equivalent character of n to the new string
    }
    printf("]\n   ");
}

void decrypt(string str, int k, string &NewStr){ //changes value of decrypted string and display the decimal equivalent in the ASCII table of each of its letter
    printf("   [");
    for(int i=0; i<str.length(); i++){
        int p = (int)str[i]; //initialize p to the current decimal equivalent of the letter
        int n = mod(p-k,127); //initialize n to the modulo of p-k and 127
        if(p-k<32) n=(127-(32-n)); //if (p-k) is less than 32, n will be subtracted from 32(which is the first decimal value in the range) and then subtracted from 127(which is the last decimal value in the range)

        printf("%d",n-32);
        if(i!=str.length()-1) printf(",");

        NewStr+=(char)n; //concatenate the equivalent character of n to the new string
    }
    printf("]\n   ");
}


int main(int argc, char *argv[]){
    string str, encryptedStr, decryptedStr;
    int shift;
    //set the first and second arguments after the filename(or object code) to value of str and shift
    str = argv[1];
    shift = stoi(argv[2]);

    try{ //use exception handling to prevent user from inputting wrong arguments
        if(argc<3 || argc>3) throw invalid_argument("Invalid input. The input should start with the object code, followed by word/phrase then the shift number. Try again!");

    cout << "\n   ENCRYPTED:" << endl;

    //pass original string to the encrypt function
    encrypt(str, shift, encryptedStr);
    cout << encryptedStr << endl; //display encrypted string

    //pass newly encrypted string to the decrypt function
    cout << "\n   DECRYPTED:" << endl;
    decrypt(encryptedStr, shift, decryptedStr);
    cout << decryptedStr << endl << endl; //display decrypted string

    }catch(const invalid_argument &e){
        cout << e.what() << endl;
    }

    return 0;
}
