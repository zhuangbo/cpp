/*
 * test.cpp
 *
 *  Created on: 2013-1-11
 *      Author: zhbo
 */

#include <iostream>
#include <valarray>
#include <ctime>
using namespace std;

#include "matrix.h"

int main() {
	int arr[] = {1,2,3,4,5,6,7,8,9,0};
	Matrix<int> a;
	cout << "a=\n" << a << endl;
	Matrix<int> b(3,5);
	cout << "b=\n" << b << endl;
	Matrix<int> c(4,3,9);
	cout << "c=\n" << c << endl;
	Matrix<int> d(2,5,arr);
	cout << "d=\n" << d << endl;
	Matrix<int> e(d);
	cout << "e=\n" << e << endl;

	a = e;
	cout << "a=\n" << a << endl;

	for(size_t i=0; i<a.rows(); i++)
		for(size_t j=0; j<a.cols(); j++)
			cout << a[i][j];
	cout << endl;

	a += 2;
	cout << "a=\n" << a << endl;
	a -= 2;
	cout << "a=\n" << a << endl;
	a *= 2;
	cout << "a=\n" << a << endl;
	a /= 2;
	cout << "a=\n" << a << endl;
	a %= 2;
	cout << "a=\n" << a << endl;

	{
		long start = clock();
		Matrix<int> a(10000,10000, 1);
		a[10000-1][10000-1] = 9;
		long end = clock();
		cout << (end-start) << "ms" << endl;
	}
	{
		long start = clock();
		valarray<int> a(1, 10000*10000);
		a[100000000-1] = 9;
		long end = clock();
		cout << (end-start) << "ms" << endl;
	}

	return 0;
}
