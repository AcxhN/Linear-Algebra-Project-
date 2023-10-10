#include <iostream>
#include <string>
#include <math.h>

#include "qbMatrix.h"

using namespace std;

// A simple function to print a matrix to stdout 
template <class T>
void PrintMatrix(qbMatrix2<T> matrix) {
    int nRows = matrix.GetNumRows();
    int nCols = matrix.GetNumCols();
    for (int row = 0; row < nCols; ++row) {
        for (int col = 0; col < nCols; ++ col) {
            cout << matrix.GetElement(row, col) << "  ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Code to test qbMatrix2" << endl;

    // 
    // Create an instance of the qbMartrix2 class
    // This will contain a simple 3x3 matrix 
    double simpleData[12] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0};
    qbMatrix2<double> testMatrix(3, 4, simpleData);

    //Extract and print the elements of testMatrix 
    cout << endl << "**********************************" << endl;
    cout << "3x4 matrix test (testMatrix)." << endl;
    PrintMatrix(testMatrix);

    // Test element retrival  
    cout << endl << "**********************************" << endl;
    cout << "Test element retrieval." << endl;
    cout << "Element (0,0) = " << testMatrix.GetElement(0,0) << endl;
    cout << "Element (1,0) = " << testMatrix.GetElement(1,0) << endl;
    cout << "Element (2,0) = " << testMatrix.GetElement(2,0) << endl;
    cout << "Element (0,1) = " << testMatrix.GetElement(0,1) << endl;
    cout << "Element (1,1) = " << testMatrix.GetElement(1,1) << endl;
    cout << "Element (2,1) = " << testMatrix.GetElement(2,1) << endl;
    cout << "Element (5,5) = " << testMatrix.GetElement(5,5) << endl; // retriving an invalid element!

    // Test matrix multiplication 
    cout << endl << "**********************************" << endl;
    cout << "Test matrix multiplication" << endl;
    double simpleData2[12] = {1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0};
    qbMatrix2<double> testMatrix2(4, 3, simpleData2);
    cout << "4x3 matrix (testMatix2)" << endl;
    PrintMatrix(testMatrix2);
    cout << "Multiplication(testMatrix * testMatrix2) result:" << endl;
    qbMatrix2<double> multTest1 = testMatrix * testMatrix2;
    PrintMatrix(multTest1);

    cout << "Multiplication(testMatrix2 * testMatrix1) result:" << endl;
    qbMatrix2<double> multTest2 = testMatrix2 * testMatrix;
    PrintMatrix(multTest2);

    cout << endl << "**********************************" << endl;
    cout << "Test multiplication of coloumn vector by matrix." << endl;
    double columnData[3] = {1.5, 2.5, 3.5};
    double squareData[9] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    qbMatrix2<double> testColoumn(3, 1, columnData);
    qbMatrix2<double> squareMatrix(3, 3, squareData);
    cout << "Coloumn vector =" << endl;
    PrintMatrix(testColoumn);
    cout << "Square matrix = " << endl;
    PrintMatrix(squareMatrix);
    cout << "Coloumn vector * Square Matrix" << endl;
    PrintMatrix(testColoumn * squareMatrix);
    cout << "Square matrix * Coloumn vector" << endl;
    PrintMatrix(squareMatrix * testColoumn);
    cout << "Square Matrix + 1.0 = " << endl;
    qbMatrix2<double> squareMatrix2 = squareMatrix + 1.0;
    PrintMatrix(squareMatrix2);
    cout << "(Square matrix + 1.0) * Coloumn vector =" << endl;
    PrintMatrix(squareMatrix2 * testColoumn);

    /* 
            test the equality operator 
    */

    cout << endl << "**********************************" << endl;
    cout << "Test equality operator:" << endl;
    cout << "testmatrix == testMatrix2: " << (testMatrix == testMatrix2) << endl;
    cout << "testmatrix2 == testMatrix: " << (testMatrix2 == testMatrix) << endl;
    cout << "(Let testMatrix3 = testMatrix) " << endl;
    qbMatrix2<double> testMatrix3 = testMatrix;
    cout << "testMatrix == testMatrix3: " << (testMatrix == testMatrix3)<< endl;
    cout << "testMatrix3 == testMatrix: " << (testMatrix3 == testMatrix) << endl;

    // test matrix addition by scalar 
    cout << endl << "**********************************" << endl;
    cout << "Test addition by scalar" << endl;
    cout << "testmatrix + 2.0 = " << endl;
    PrintMatrix(testMatrix + 2.0);
    cout << endl;
    cout << "2.0 + testMatrix = " << endl;
    PrintMatrix(2.0 + testMatrix);

    /*
        Test matrix subraction by scalar 
    */
    cout << endl << "**********************************" << endl;
    cout << "Test subtraction by scalar" << endl;
    cout << "testmatrix - 2.0 = " << endl;
    PrintMatrix(testMatrix - 2.0);
    cout << endl;
    cout << "2.0 - testMatrix = " << endl;
    PrintMatrix(2.0 - testMatrix);

    /*
            Test matrix multiplication by scalar 
    */
       cout << endl << "**********************************" << endl;
    cout << "Test multiplication by scalar" << endl;
    cout << "testmatrix * 2.0 = " << endl;
    PrintMatrix(testMatrix * 2.0);
    cout << endl;
    cout << "2.0 * testMatrix = " << endl;
    PrintMatrix(2.0 * testMatrix);

    return 0;
}
