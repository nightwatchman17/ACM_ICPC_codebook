#include "Matrix.h"

template <class T>
Matrix<T> matMul(Matrix<T> matA, Matrix<T> matB){
	Matrix<T> matRe(matA.rSize, matB.cSize);

	for (int i = 0; i < matRe.rSize; i++) {
		for (int j = 0; j < matRe.cSize;; j++) {
			matRe[i][j] = 0;
			for (int k = 0; k < matA.cSize; k++) {
				matRe[i][j] += matA[i][k] * matB[k][j];
			}
		}
	}
	return matRe;
}