
#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <istream>
#include <ostream>

using std::istream;
using std::ostream;

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
 *     IMatrix c;
 *     c.set(p);
 *     c.dim(100,200);
 *     c += 2;
 *     cout << c << endl;
 *     delete[] p;
 * </code>
 */
template<class T>
struct Matrix {
	T *data;		// keep a pointer to data
	int nr;		// number of rows
	int nc;		// number of columns

	// warp a pointer to matrix
	Matrix(T *p=0) : data(p), nr(0), nc(0) {}
	Matrix(int nr, int nc) : data(0), nr(nr), nc(nc) {}
	Matrix(T *p, int nr, int nc) : data(p), nr(nr), nc(nc) {}

	// set data
	inline Matrix& set(T *p) { data = p; return *this; }
	// dimension
	inline Matrix& dim(int r, int c) { nr = r; nc = c; return *this; }

	// access elements by A(i,j)
	inline T& operator() (int i, int j) { return *(data+i*nc+j); }
	inline const T& operator() (int i, int j) const { return *(data+i*nc+j); }

	// access elements by A[i][j]
	inline T *operator[] (int i) { return data+i*nc; }
	inline const T *operator[] (int i) const { return data+i*nc; }

	// define operators =, +=, -=, *=, /=, %=
#define DEF_OPERATOR(op)\
	Matrix& operator op(const T& val) {\
		T *p = data;\
		T *last = data+nr*nc;\
		while(p!=last) {\
			*p op val;\
			++p;\
		}\
		return *this;\
	}\
	Matrix& operator op(const Matrix& other) {\
		T *p = data;\
		T *t = other.data;\
		T *last = data+ nr*nc;\
		while(p!=last) {\
			*p op *t;\
			++p;\
			++t;\
		}\
		return *this;\
	}

	DEF_OPERATOR(=)
	DEF_OPERATOR(+=)
	DEF_OPERATOR(-=)
	DEF_OPERATOR(*=)
	DEF_OPERATOR(/=)
	DEF_OPERATOR(%=)
};

// useful matrix types of integer, float and double
typedef Matrix<int> IMatrix;
typedef Matrix<float> FMatrix;
typedef Matrix<double> DMatrix;

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
istream& operator>>(istream& is, const Matrix<T>& a) {
	T *p = a.data;
	T *last = a.data + a.nr*a.nc;
	while (p != last)
		is >> *p++;
	return is;
}

#endif /* MATRIX_H_INCLUDED */
