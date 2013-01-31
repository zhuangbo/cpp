/*
 * matrix2.cpp
 *
 *  Created on: 2013-1-31
 *      Author: zhbo
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "matrix.h"

int main()
{
	int nr = 3, nc = 5;
	// 还是自己分配内存，待需要时包装成矩阵
	int *p = (int *) calloc(nr*nc, sizeof(int));

	// 包装成 3 x 5 的矩阵
	IMatrix a(p, nr, nc);
	// 先建立 3 x 5 矩阵，再设置数据
	IMatrix b(3, 5);
	b.set(p);
	// 先建立矩阵，再设置数据和行数、列数
	IMatrix c;
	c.set(p).dim(3,5);
	// 根据其他对象建立矩阵
	IMatrix d(b);
	// 访问元素
	a[1][1] = 11;
	a(2,4) = 24;  // FORTRAN 风格
	cout << a << endl;

	// 基本运算
	a = 10;
	cout << a << endl;
	a += 3;
	cout << a << endl;
	a += IMatrix(p, 3, 5);
	cout << a << endl;
	a += p;
	cout << a << endl;

	// 随时需要，都可以临时转换成矩阵，代价极小
	cout << IMatrix(p, nr, nc) << endl;

	// 自己释放内存
	free(p);

	return 0;
}
