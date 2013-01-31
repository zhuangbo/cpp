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
	// �����Լ������ڴ棬����Ҫʱ��װ�ɾ���
	int *p = (int *) calloc(nr*nc, sizeof(int));

	// ��װ�� 3 x 5 �ľ���
	IMatrix a(p, nr, nc);
	// �Ƚ��� 3 x 5 ��������������
	IMatrix b(3, 5);
	b.set(p);
	// �Ƚ����������������ݺ�����������
	IMatrix c;
	c.set(p).dim(3,5);
	// ������������������
	IMatrix d(b);
	// ����Ԫ��
	a[1][1] = 11;
	a(2,4) = 24;  // FORTRAN ���
	cout << a << endl;

	// ��������
	a = 10;
	cout << a << endl;
	a += 3;
	cout << a << endl;
	a += IMatrix(p, 3, 5);
	cout << a << endl;
	a += p;
	cout << a << endl;

	// ��ʱ��Ҫ����������ʱת���ɾ��󣬴��ۼ�С
	cout << IMatrix(p, nr, nc) << endl;

	// �Լ��ͷ��ڴ�
	free(p);

	return 0;
}
