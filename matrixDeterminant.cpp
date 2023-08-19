#include<iostream>
#include<iomanip>
#include"matrixDeterminant.h"

using namespace std;

void matrixDeterminant(double** matrix, const int& size) {
    double sign = 1;

    cout << fixed << setprecision(2) << endl;
    for (int i = 0; i < size - 1; i++) { // each row
        //swap rows if first item is zero
        if (matrix[i][i] == 0) {
            // a function for swaping
            bool nonZero = false;
            int below = i + 1;
            for (; below < size; below++) {
                if (matrix[below][i] != 0) {
                    nonZero = true;
                    break;
                }
            }
            if (nonZero) {
                double* temp = new double[size - i];
                for (int swapFrom = 0; swapFrom < size - i; swapFrom++) {
                    temp[swapFrom] = matrix[i][swapFrom + i];
                    matrix[i][swapFrom + i] = matrix[below][swapFrom + i];
                    matrix[below][swapFrom + i] = temp[swapFrom];
                }
                sign *= -1;
                // delete raw pointer
                delete[] temp;
                temp = nullptr;
            }
            else {
                // determinant is zero
                cout << "The determinant is: " << setprecision(0) << 0 << endl << endl;
                return;
            }
        }
        // REWORK this part


        for (int j = i + 1; j < size; j++) {  // for each row below
            double diff = (matrix[j][i] * -1) / matrix[i][i]; // e.g. (1 * -1)/-2 = 0.5
            for (int k = i; k < size; k++) {
                matrix[j][k] += matrix[i][k] * diff; // e.g. 1 + (-2)*0.5 = 0
            }
            /*cout << "Row " << i+1 << " times " << diff << ", plus row " << j+1 << ':' << endl << endl;*/
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    /*cout << matrix[i][j] << '\t';*/
                }
                /*cout << endl;*/
            }
            /*cout << endl << endl;*/
        }
    }

    // calculate determinant
    double determinant = 1.0;
    for (int i = 0; i < size; i++) {
        determinant *= matrix[i][i];
    }
    cout << "The determinant is: " << setprecision(0) << sign * determinant << endl << endl;
}