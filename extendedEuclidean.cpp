/***************************************************************************
    MAXINE NICOLE B. BERNALES
    CSMC121 ZC11 (Discrete Structures 2)
    2.25.2023
    E4[Extended Euclidean Algorithm]

    Program Description: A C++ Program that follows the Extended Euclidean Algorithm to find the GCF of the two command-line arguments.
    Implemented:
    - math
    - command-line arguments
    - exception handling
***************************************************************************/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]){
    //set the first and second arguments after the filename(or object code) to value of num1 and num2
    int num1 = stoi(argv[1]);
    int num2 = stoi(argv[2]);
    try{ //use exception handling to prevent user from inputting wrong arguments
        if(argc<3 || argc>3) throw invalid_argument("Invalid input. The input should start with the object code, followed by first number then the second number. Try again");
        if(num1<=0||num2<=0) throw invalid_argument("Invalid Input. No input should be negative or zero. Try again!");

        //determine larger and smaller number between the inputs
        int larger = std::max(num1, num2);
        int smaller = std::min(num1, num2);

        //store the values to other variables; to be used in displaying the original numbers
        int l = larger;
        int s = smaller;

        //set gcf to the smaller value and set a counter
        int remainder, gcf = s;
        int sJ = 1, tJ = 0, quotient;
        int firstCE, secondCE; //declare first and second coefficients in the Bezout's identity
        int s0 = 1, s1 = 0, t0 = 0, t1 = 1;

        int counter = 0;

        //loop for Euclidean Theorem

        printf("\n");
        while(smaller!=0){
            //find remainder and quotient
            remainder = larger%smaller;
            quotient = larger/smaller;

            //display iteration#, first number, second number, quotient, remainder, sJ and tJ for each iteration
            cout << right << setw(2) << counter << setw(4) << larger << setw(4) << smaller << setw(3) << quotient << setw(3) << remainder << setw(3) << s0 << setw(3) << t0 << endl;

            //as loop iterates, smaller becomes the larger and the remainder becomes the smaller
            larger = smaller;
            smaller = remainder;

            if(remainder!=0) gcf = remainder; //gcf is the last remainder that is not zero

            //follow formula of extended Euclidean Algorithm
            sJ = s0 - s1*quotient;
            tJ = t0 - t1*quotient;

            if(smaller!=0){
                s0 = s1; s1 = sJ; //s1 becomes s0 and sJ becomes the s1
                t0 = t1; t1 = tJ; //t1 becomes t0, and tJ becomes the t1
                firstCE = sJ; //first coefficient is the value of sJ before smaller becomes 0
                secondCE = tJ; //second coefficient is the value of tJ before smaller becomes 0
            }
            counter++;
        }

        if(l%s==0){ //if the smaller number divides larger number, first coefficient = 0 and second coefficient = 1
            firstCE = 0;
            secondCE = 1;
        }

        //displays Bezout's identity
        cout << setw(16) << " " << setw(3) << firstCE << setw(3) << secondCE << endl;
        printf("\n %d = gcd(%d,%d) = (%d*%d)%c(%d*%d)\n\n", gcf, num1, num2, firstCE, l, '+', secondCE, s);

    }catch(const invalid_argument &e){ //displays error message
        cout << e.what() << endl;
    }

    return 0;
}
