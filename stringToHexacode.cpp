/*******************************************
    MAXINE NICOLE B. BERNALES
    CSDC102 ZC11 (Intermediate Programming)
    1.12.2023
    DE1[Convert String to Hexacode]

    Program Description: A C++ Program that allows user to input a string and the program will convert it into hexacode. Explanation of the algorithm is as follows:
        BINARY CODE
                128  64  32  16  8  4  2  1
        -------------------------------------------
        65 =     0  1    0   0   0  0  0  1

        HEXACODE
        0 : 0000
        1 : 0001
        2 : 0010
        3 : 0011
        4 : 0100
        5 : 0101
        6 : 0110
        7 : 0111
        8 : 1000
        9 : 1001
        A : 1010
        B : 1011
        C : 1100
        D : 1101
        E : 1110
        F : 1111

        A ---------------> 65 -------------> 41
    Implemented:
    - math
    - command-line arguments
    - exception handling 
*********************************************/


#include <iostream>
#include <string>
using namespace std;

string binary(int);//converts decimal to binary code
string hexacode(string);//converts binary code to hexacode

int main(){
    //displays "Hello World"
    string hw = "Hello World";
    cout << hw << endl;

    //display hexacode of "Hello World"
    for(int i=0; i<hw.length(); i++){ //loops through every character of the string
        char e = hw[i];
        string bin = binary(e); //returns an 8-digit binary code
        string hex = hexacode(bin.substr(0,4)) + hexacode(bin.substr(4,4)); //divide the binary code to two substrings and return its equivalent hexacode
        cout << hex;
    }

    cout << endl;
	
    //display binary code
    for(int i=0; i<hw.length(); i++){
        char e = hw[i];
        string bin = binary(e);

        cout << bin;
    }

    cout << endl;

    return 0;
}

string binary(int num){
    string bincode;
    int sub = 128;
    while(sub!=0){
        if(sub<=num){
            bincode+='1';
            num-=sub;
        }else bincode+='0';
        sub/=2;
    }
    return bincode;
}

string hexacode(string f){
    if(f=="0000") return "0";
    else if(f=="0001") return "1";
    else if(f=="0010") return "2";
    else if(f=="0011") return "3";
    else if(f=="0100") return "4";
    else if(f=="0101") return "5";
    else if(f=="0110") return "6";
    else if(f=="0111") return "7";
    else if(f=="1000") return "8";
    else if(f=="1001") return "9";
    else if(f=="1010") return "a";
    else if(f=="1011") return "b";
    else if(f=="1100") return "c";
    else if(f=="1101") return "d";
    else if(f=="1110") return "e";
    else if(f=="1111") return "f";
    return 0;
}
