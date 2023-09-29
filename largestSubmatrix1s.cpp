/****************************************
    MAXINE NICOLE B. BERNALES
    CSDC102 ZC11 (Intermediate Programming)
    4.13.2023
    E2[Largest Submatrix of all 1s]

    Program Description: A C++ Program that accepts a matrix input and finds the index of the first element of the largest submatrix of all 1s.
        ALGORITHM
        1 Take input for the noOfRows and elements of the matrix.
        2 Find the largest block of all 1s:
            o Traverse through the matrix from the (1,1) to last element
            o Check the top, left, and topLeft elements of the element in the matrix.
                If the element==1 and the top, left, and topLeft elements are all greater than 0
                    increment the smallest value among the top, left, and topLeft elements to the element
                Keep track of the largest element, which will be the size of the largestBlock
            o The indices of the first element of the submatrix will be the row and column of the largest subtracted by (largest-1)
        3 Create vector for the answers and display.
    Implemented:
        - Math
        - Vector
        - Iterator
        - Exception Handling
******************************************/

#include <iostream>
#include <vector>
#include <iterator>

std::vector<std::vector<int>> takeInputForMatrix(int &Rows);
std::vector<int> findLargestBlock(const std::vector<std::vector<int>> &m);
int smallest(int &topLeft, int &top, int &left);

int main(){
    int rows;

    std::vector<std::vector<int>> Matrix{takeInputForMatrix(rows)}; //take input for noOfRows and elements of the matrix
    std::vector<int> Answers{findLargestBlock(Matrix)}; //pass the matrix to the function that will return the indices of first element and size

    int First_Index_Of_1st_Element{Answers.at(0)}; // x in FirstElement(x,y) is the first element of the Answers vector
    int Second_Index_Of_1st_Element{Answers.at(1)}; // y in FirstElement(x,y) is the second element of the Answers vector
    int Size_Of_Largest_Block{Answers.at(2)}; // Size of submatrix is the third element of the Answers vector

    if(Size_Of_Largest_Block <= 1) printf("\n There is no submatrix will all elements of 1.\n"); //submatrix with size <= 1 is not considered a submatrix
    else printf("\n The maximum square submatrix is at (%d,%d) with size %d\n", First_Index_Of_1st_Element, Second_Index_Of_1st_Element, Size_Of_Largest_Block);
}


std::vector<std::vector<int>> takeInputForMatrix(int &Rows){
    std::vector<std::vector<int>> Matrix; //create 2D vector

	printf("Enter the number of rows for the matrix: ");
    try{
        std::istream_iterator<int> readNum{std::cin};
        int rows(*readNum); //take input for noOfRows
        if(rows < 2 || rows > 100) throw std::invalid_argument("\n Error! Size of the matrix should be atleast 2 and at most 100.");

        printf("Enter the matrix row by row: \n");

        int n;
        for(size_t r{0}; r < rows; r++){
            std::vector<int> matrixRow; //create 1D vector that will be inserted to the 2D vector
            for(size_t c{0}; c < rows; c++){
                std::cin >> n; //take input for the element and insert it to the 1D vector
                if(n != 0 && n != 1) throw std::invalid_argument("\n Error! Input for the matrix should only be 0 or 1.");
                matrixRow.push_back(n);
            }
            Matrix.push_back(matrixRow);
        }

    }catch(const std::invalid_argument &e){
        std::cerr << e.what() << std::endl;
    }

    return Matrix;
}

int smallest(int &topLeft, int &top, int &left){
    int smallest{topLeft};
    if(top < smallest) smallest = top;
    if(left < smallest) smallest = left;
    return smallest; //return the min value among the three parameters
}

std::vector<int> findLargestBlock(const std::vector<std::vector<int>> &m){
    std::vector<std::vector<int>> matrix{m}; //create another 2D vector and copy contents of the matrix

    int largest{0}, rowOfLargest, columnOfLargest;
    for(size_t r{1}; r < matrix.size(); r++){
        for(size_t c{1}; c < matrix[0].size(); c++){
            //if element == 1 and the top, left, and topLeft elements are greater than 0
            if(matrix[r][c] == 1 && matrix[r-1][c-1] > 0 && matrix[r-1][c] > 0 && matrix[r][c-1] > 0)
                matrix[r][c] += smallest(matrix[r-1][c-1], matrix[r-1][c], matrix[r][c-1]); //increment the smallest value among the top, left, and topLeft elements to the element

            if(matrix[r][c] > largest){ //keep track of the largest element and its indices
                largest = matrix[r][c];
                rowOfLargest = r;
                columnOfLargest = c;
            }
        }
    }

    //The indices of the first element of the submatrix will be the row and column of the largest subtracted by (largest-1)
    int rowOfFirstElement{rowOfLargest-(largest-1)};
    int columnOfFirstElement{columnOfLargest-(largest-1)};

    std::vector<int> Answers{rowOfFirstElement, columnOfFirstElement, largest}; //create vector with the answers and return
    return Answers;
}
