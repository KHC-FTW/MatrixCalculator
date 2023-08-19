#pragma once

template<typename T>
bool inverseMatrix(T** matrix, T** inverse, int& size) {

    bool detIsZero = false;

    for (int i = 0; i < size - 1; i++) { // each row
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
                T* matrixTemp = new T[size];
                T* inverseTemp = new T[size];
                for (int swapFrom = 0; swapFrom < size; swapFrom++) {
                    matrixTemp[swapFrom] = matrix[i][swapFrom];
                    matrix[i][swapFrom] = matrix[below][swapFrom];
                    matrix[below][swapFrom] = matrixTemp[swapFrom];

                    inverseTemp[swapFrom] = inverse[i][swapFrom];
                    inverse[i][swapFrom] = inverse[below][swapFrom];
                    inverse[below][swapFrom] = inverseTemp[swapFrom];

                }

                // delete raw pointer

                delete[] matrixTemp;
                matrixTemp = nullptr;
                delete[] inverseTemp;
                inverseTemp = nullptr;

            }
            else {
                // determinant is zero
                //detIsZero = true;
                //std::cout << std::endl << "The determinant is zero. Thus, inverse matrix does not exist.\n" << std::endl;
                return detIsZero = true;
            }
        }

        for (int j = i + 1; j < size; j++) {  // one row less

            T diff = (matrix[j][i] * -1) / matrix[i][i]; // e.g. (1 * -1)/-2 = 0.

            for (int k = 0; k < size; k++) {
                matrix[j][k] += matrix[i][k] * diff;
                inverse[j][k] += inverse[i][k] * diff;
            }
        }
    }

    for (int i = size - 1; i >= 0; i--) {
        if (matrix[i][i] == 0) {
            return detIsZero = true;
        }
        for (int j = i - 1; j >= 0; j--) {
            T diff = (matrix[j][i] * -1) / matrix[i][i];
            matrix[j][i] = 0; //matrix[j][i] += matrix[i][i] * diff
            for (int k = size - 1; k >= 0; k--) {
                inverse[j][k] += inverse[i][k] * diff;
            }
        }
        for (int l = size - 1; l >= 0; l--) {
            inverse[i][l] /= matrix[i][i];
        }
    }

    return detIsZero;

}