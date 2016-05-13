#include "Matrix.h"
#include <algorithm>
using namespace std;

template <class T>
Matrix<T> matInv(Matrix<T> mat) {
	if (mat.rSize != mat.cSize)
		return Matrix<T>(0, 0);

	int n = mat.rSize;
	Matrix<T> matRe(n, n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matRe[i][j] = (i == j) ? 1 : 0;

	for (int i = 0; i < n - 1; i++)
		if (mat[i][1] < mat[i + 1][1]) {
			swap(mat[i], mat[i + 1]);
			swap(matRe[i], matRe[i + 1]);
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j) {
				double div = mat[j][i] / mat[i][i];
				for (int k = 0; k < n; k++) {
					mat[j][k] -= mat[i][k] * div;
					matRe[j][k] -= matRe[i][k] * div;
				}
			}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matRe[i][j] /= mat[i][i];

	return matRe;
}