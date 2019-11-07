#pragma once
#include "Vector.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//void swap(double& a, double& b)
//{
//	double temp = a;
//	a = b;
//	b = temp;
//}
class Matrix
{
private:
	double **A;
public:
	int row, col;
public:
	Matrix(const Matrix& _matrix);
	Matrix();
	Matrix(int n);
	Matrix(int _row, int _col);
	~Matrix();
	void clear();
	void setValue(int _row, int _col, double value);
	bool Is_empty();
	const Matrix& operator = (const Matrix& A);
	friend istream& operator >> (istream& inDev, Matrix& matrix);
	friend ostream& operator << (ostream& outDev, Matrix& matrix);
	static double det(Matrix& X);
	double det();
	Matrix T()const;
	Matrix Adj()const;
	Matrix inverse();
	const Matrix operator * (const Matrix& a) const;
	const Matrix operator * (double X) const;
	Matrix subMatrix(int _row, int _col);
	Matrix subMatrix(int _col);
	const Matrix MatrixRank();
	int rank();
	static void solve();
};
