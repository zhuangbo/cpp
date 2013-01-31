/*
 * matrix1.cpp
 *
 * A simplest matrix implementation, which supports a[i][j] and a(i,j).
 *
 *  Created on: 2013-1-31
 *      Author: zhbo <sdzhuangbo@126.com>
 */

///////////////////////////////////////////////////////////
// Matrix class template
///////////////////////////////////////////////////////////
/**
 * A simple light weight matrix type wrapped from pointer.
 *
 * If you have a pointer p, this class can wrap it to be a matrix,
 * and then, you can use [i][j] or (i,j) to access its elements.
 *
 * For example,
 * <code>
 *     int *p = new int[100*200];
 *     IMatrix a(p, 100, 200);
 *     a[0][0] = 1;
 *     a(1, 0) = 2;
 *     IMatrix b(p, 200, 100);
 *     cout << b[0][0] << "," << b[0][100] << endl;
 *     delete[] p;
 * </code>
 */
template<class T>
struct Matrix {
	T *data;		// keep a pointer to data
	int nr;		// number of rows
	int nc;		// number of columns

	// warp a pointer to matrix
	Matrix(T *p, int nr, int nc) : data(p), nr(nr), nc(nc) {}

	// access elements by A(i,j)
	inline T& operator() (int i, int j) { return *(data+i*nc+j); }
	inline const T& operator() (int i, int j) const { return *(data+i*nc+j); }

	// access elements by A[i][j]
	inline T *operator[] (int i) { return data+i*nc; }
	inline const T *operator[] (int i) const { return data+i*nc; }
};

// useful matrix types of integer, float and double
typedef Matrix<int> IMatrix;
typedef Matrix<float> FMatrix;
typedef Matrix<double> DMatrix;

///////////////////////////////////////////////////////////
// Matrix I/O
///////////////////////////////////////////////////////////
#include <istream>
#include <ostream>

using std::istream;
using std::ostream;

// output matrix to stream
template<class T>
ostream& operator<<(ostream& os, const Matrix<T>& a) {
	const T *p = a.data;
	for (int i = 0; i < a.nr; i++) {
		for (int j = 0; j < a.nc; j++)
			os << '\t' << (*p++);
		os << '\n';
	}
	return os;
}

// input matrix from stream
template<class T>
istream& operator>>(istream& is, Matrix<T>& a) {
	T *p = a.data;
	T *last = a.data + a.nr*a.nc;
	while (p != last)
		is >> *p++;
	return is;
}

///////////////////////////////////////////////////////////
// demo
///////////////////////////////////////////////////////////

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int nr = 3, nc = 5;
	// �����Լ������ڴ棬����Ҫʱ��װ�ɾ���
	int *p = (int *) calloc(nr*nc, sizeof(int));

	// ��װ�� 3 x 5 �ľ���
	IMatrix a(p, nr, nc);

	// ����Ԫ��
	a[1][1] = 11;
	a(2,4) = 24;  // FORTRAN ���

	for (int i=0; i<nr; i++)
		for (int j=0; j<nc; j++)
			cout << "\t" << a[i][j];
	cout << endl;

	// ͬ�������ݣ���ͬ�İ�װ
	IMatrix b(p, 2, 4);
	cout << b[1][2] << endl;

	// �����������������
	cout << "������һ��2x4����";
	cin >> b;
	cout << b << endl;

	// ��ʱ��Ҫ����������ʱת���ɾ��󣬴��ۼ�С
	cout << IMatrix(p, 5, 3) << endl; // ��ʱ��װ��5��3�о������

	// �Լ��ͷ��ڴ�
	free(p);

	return 0;
}
