#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cctype>
#include <string>
#include "matrixDeterminant.h"
#include "InverseMatrixTemplate.h"
#include "fraction.h"

bool hasException = false;

int main() {

	std::cout << "Welcome to the matrix calculator." << std::endl;
	char option{};

	do {
		std::cout << "\nPlease choose an option below (Press 'e' to exit):\n" << std::endl;
		std::cout << "1. Calculate determinant.\n" << std::endl;
		std::cout << "2. Find inverse matrix (Results in decimals).\n" << std::endl;
		std::cout << "3. Find inverse matrix (Results in fractions).\n" <<
			 "\n!!!Warning!!! Option 3 may not work with large matrices (>8)\n" << std::endl;
		std::cout << "Your option: ";
		
		std::cin >> option;
		if (option == 'e') {
			std::cout << "\nProgram exited. Thank you for trying!\n" << 
				"(The program will close in 2 seconds.)" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			break;
		}
		switch (option) {
		case '1':
		{
			int size{};
			do {
				std::cout << "\nEnter the size of the square matrix: ";
				std::string input;
				std::cin >> input;
				bool validNum = true;
				for (int i = 0; i < input.length(); i++) {
					if (!std::isdigit(input[i])) {
						validNum = false;
						break;
					}
				}
				if (validNum) size = std::stoi(input);

				if (!validNum || size < 2)
					std::cout << "\nThe input should be a number of at least 2. Please try again." << std::endl;

			} while (size < 2);

			double** matrix = new double* [size];
			for (int i = 0; i < size; i++) {
				matrix[i] = new double[size];
			}

			std::cout << "\nEnter the content of the matrix:\n" << std::endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					std::cin >> matrix[i][j];
					// matrix[i][j] *= 1.0;
				}
			}

			matrixDeterminant(matrix, size);

			for (int i = 0; i < size; i++) {
				delete[] matrix[i];
				matrix[i] = nullptr;
			}
			delete[] matrix;
			matrix = nullptr;
		}
			break;

		case '2':
		{
			int size{};
			do {
				std::cout << "\nEnter the size of the square matrix: ";
				std::string input;
				std::cin >> input;
				bool validNum = true;
				for (int i = 0; i < input.length(); i++) {
					if (!std::isdigit(input[i])) {
						validNum = false;
						break;
					}
				}
				if (validNum) size = std::stoi(input);

				if (!validNum || size < 2)
					std::cout << "\nThe input should be a number of at least 2. Please try again." << std::endl;

			} while (size < 2);

			double** matrix = new double* [size];
			for (int i = 0; i < size; i++) {
				matrix[i] = new double[size];
			}

			std::cout << "\nEnter the content of the matrix:\n" << std::endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					std::cin >> matrix[i][j];
					// matrix[i][j] *= 1.0;
				}
			}

			double** inverse = new double * [size];
			for (int i = 0; i < size; i++) {
				inverse[i] = new double[size];
			}
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					inverse[i][j] = (j == i) ? 1 : 0;
				}
			}

			int sigFig{};
			bool validNum;
			do {
				validNum = true;
				std::cout << "\nNumber of significant figures to be displayed: ";
				std::string input{};
				std::cin >> input;
				for (int i = 0; i < input.length(); i++) {
					if (!std::isdigit(input[i])) {
						validNum = false;
						break;
					}
				}
				if (validNum) sigFig = std::stoi(input);
				else std::cout << "\nInvalid input. Please try again." << std::endl;

			} while (!validNum);

			bool detIsZero = inverseMatrix(matrix, inverse, size);

			if (detIsZero) {
				std::cout << "\nThe determinant is zero. Inverse matrix does not exist.\n" << std::endl;
			}
			else {
				std::cout << "\nThe inverse matrix is:\n" << std::endl;
				std::cout << std::fixed << std::setprecision(sigFig);
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
					std::cout << inverse[i][j] + 0 << "         ";
					}
					std::cout << "\n" << std::endl;
				}
				//std::cout << std::endl;
			}

			// free memory

			for (int i = 0; i < size; i++) {
				delete[] matrix[i];
				matrix[i] = nullptr;
				delete[] inverse[i];
				inverse[i] = nullptr;
			}

			delete[] matrix;
			matrix = nullptr;
			delete[] inverse;
			inverse = nullptr;

		}
			break;
		case '3':
		{
			int size{};
			do {
				std::cout << "\nEnter the size of the square matrix: ";
				std::string input;
				std::cin >> input;
				bool validNum = true;
				for (int i = 0; i < input.length(); i++) {
					if (!std::isdigit(input[i])) {
						validNum = false;
						break;
					}
				}
				if (validNum) size = std::stoi(input);

				if (!validNum || size < 2)
					std::cout << "\nThe input should be a number of at least 2. Please try again." << std::endl;

			} while (size < 2);

			// create matrix of user input size
            Fraction** matrix = new Fraction * [size];
            for (int i = 0; i < size; i++) {
                matrix[i] = new Fraction[size];
            }

			std::cout << "\nEnter the content of the matrix:\n" << std::endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					std::cin >> matrix[i][j];
				}
				std::cout << "\n" << std::endl;
			}

			Fraction** inverse = new Fraction* [size];
			for (int i = 0; i < size; i++) {
				inverse[i] = new Fraction[size];
			}
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					inverse[i][j] = (j == i) ? 1 : 0;
				}
			}

			bool detIsZero = inverseMatrix(matrix, inverse, size);

			if (detIsZero) {
				std::cout << "The determinant is zero. Inverse matrix does not exist.\n" << std::endl;
			}
			else if (hasException) {
				std::cout << "Intergers overflowed, incalculable." << std::endl;
				std::cout << "Try reducing the size of the matrix.\n" << std::endl;
			}
			else {
				std::cout << "The inverse matrix is:\n" << std::endl;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						if (inverse[i][j] > 0) {
							std::cout << ' ';
						}
						std::cout << inverse[i][j] + 0 << "         ";
					}
					std::cout << "\n" << std::endl;
				}
			}

			// free memory

			for (int i = 0; i < size; i++) {
				delete[] matrix[i];
				matrix[i] = nullptr;
				delete[] inverse[i];
				inverse[i] = nullptr;
			}

			delete[] matrix;
			matrix = nullptr;
			delete[] inverse;
			inverse = nullptr;

		}
			break;
		default:
			std::cout << "\nUnknown command. Please try again.\n" << std::endl;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(800));

	} while (option != 'e');

	return 0;
}