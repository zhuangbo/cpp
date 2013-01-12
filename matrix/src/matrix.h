/*
 * matrix.h
 *
 *  Created on: 2013-1-12
 *      Author: zhbo
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <algorithm>
#include <istream>
#include <ostream>
using std::size_t;
using std::istream;
using std::ostream;

template<class T>
class Matrix {
public:
	typedef T value_type;
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;

public:
	// construct zero matrix
	Matrix() :
			data(NULL), m(0), n(0) {
	}

	// construct m*n matrix
	Matrix(size_type m, size_type n, value_type val = value_type()) :
			data(new value_type[m * n]), m(m), n(n) {
		assert(data);
		std::fill(data, data + m * n, val);
	}

	// construct m*n matrix from data p
	Matrix(size_type m, size_type n, const_pointer p) :
			data(new value_type[m * n]), m(m), n(n) {
		assert(this->data);
		std::copy(p, p + m * n, this->data);
	}

	// construct matrix from another
	Matrix(const Matrix& other) :
			data(
					other.data && other.m && other.n ?
							new value_type[other.m * other.n] : NULL), m(
					other.m), n(other.n) {
		assert(data);
		std::copy(other.data, other.data + other.m * other.n, data);
	}

	// destroy it
	~Matrix() {
		if (data)
			delete[] data;
	}

	// matrix assignment
	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			Matrix temp(other);
			swap(temp);
		}
		return *this;
	}

	// swap matrix
	void swap(Matrix& other) {
		std::swap(data, other.data);
		std::swap(m, other.m);
		std::swap(n, other.n);
	}

	// rows
	size_type rows() const {
		return m;
	}

	// cols
	size_type cols() const {
		return n;
	}

	// m*n
	size_type size() const {
		return m * n;
	}

	// resize
	void resize(size_type m, size_type n, value_type val = value_type(),
			bool preserved = true) {
		Matrix& old = *this;
		Matrix tmp(m, n);
		if (!preserved) {
			std::fill(tmp.data, tmp.data + m * n, val);
		} else {
			size_type mprsvd = m > old.m ? old.m : m;
			size_type nprsvd = n > old.n ? old.n : n;
			if (n == old.n) {
				std::copy(old.data, old.data + mprsvd * nprsvd, tmp.data);
				if (m > mprsvd)
					std::fill(tmp.data + mprsvd * nprsvd, tmp.data + m * n,
							val);
			} else {
				for (size_type i = 0; i < mprsvd; ++i) {
					std::copy(old[i], old[i] + nprsvd, tmp[i]);
					if (n > nprsvd)
						std::fill(tmp[i] + nprsvd, tmp[i] + n, val);
				}
				for (size_type i = mprsvd; i < m; ++i)
					std::fill(tmp[i], tmp[i] + n, val);
			}
		}
		swap(tmp);
	}

	// clear
	void clear() {
		std::fill(data, data + m * n, value_type());
	}

	// begin
	pointer begin() {
		return data;
	}
	const_pointer begin() const {
		return data;
	}

	// end
	pointer end() {
		return data + m * n;
	}
	const_pointer end() const {
		return data + m * n;
	}

	// A(i,j) for element
	reference operator()(int i, int j) {
		return *(data + i * n + j);
	}
	const_reference operator()(int i, int j) const {
		return *(data + i * n + j);
	}

	// A[i][j] for element
	pointer operator[](int i) {
		return data + i * n;
	}
	const_pointer operator[](int i) const {
		return data + i * n;
	}

	// number operators
#define NUMBER_OP(op)\
	template <class V>\
	Matrix& operator op(const V& x) {\
		pointer p = begin();\
		while(p!=end()) *p++ op x;\
		return *this;\
	}

	NUMBER_OP(+=)
	NUMBER_OP(-=)
	NUMBER_OP(*=)
	NUMBER_OP(/=)
	NUMBER_OP(%=)

private:
	pointer data;
	size_type m; // rows
	size_type n; // cols
};

template<class T>
ostream& operator<<(ostream& os, const Matrix<T>& a) {
	typename Matrix<T>::const_pointer p = a.begin();
	for (size_t i = 0; i < a.rows(); i++) {
		for (size_t j = 0; j < a.cols(); j++)
			os << '\t' << (*p++);
		os << '\n';
	}
	return os;
}

template<class T>
istream& operator>>(istream& is, Matrix<T>& a) {
	typename Matrix<T>::pointer p = a.begin();
	while (p != a.end())
		is >> *p++;
	return is;
}

#endif /* MATRIX_H_ */
