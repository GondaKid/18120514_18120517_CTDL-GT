#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <string>
#include <Windows.h>
using namespace std;
class Vector
{
private:
	float* Data;
	int size;
public:
	Vector(const Vector& A);
	Vector();
	Vector(int _size);
	bool is_empty();
	friend ostream& operator << (ostream& outDev, Vector& A);
	friend istream& operator >> (istream& inDev, Vector& A);
	const Vector operator + (const Vector& A) const;
	const Vector operator * (double A);
	friend Vector operator* (double A, Vector& X);
	void clear();
	~Vector();
};

