#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Matrix{
public:
	int rSize, cSize;
	vector< vector<T> > mat;

	Matrix(int r = 0, int c = 0) :rSize(r), cSize(c), mat(rSize, vector<T>(cSize)){}
	vector<T>& operator[](int i) {
		return mat[i];
	}
	void print();
};

template <class T>
void Matrix<T>::print() {
	cout << "Matrix elements:" << endl;
	for (int i = 0; i < rSize; i++) {
		cout << "[";
		for (int j = 0; j < cSize; j++) {
			cout << "\t" << mat[i][j];
			if (j != cSize - 1)cout << ",";
		}
		cout << " ]" << endl;
	}
}

#endif