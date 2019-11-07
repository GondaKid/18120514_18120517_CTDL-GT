#include "Vector.h"


Vector::Vector(const Vector& A)
{
	Data = new float[A.size];
	size = A.size;
	for (int i = 0; i < size; i++)
		Data[i] = 0;
}


Vector::Vector()
{
	Data = NULL;
	size = 0;
}

Vector::Vector(int _size)
{
	size = _size;
	Data = new float[size];
	for (int i = 0; i < size; i++)
		Data[i] = 0;
}

bool Vector::is_empty()
{
	return Data == NULL;
}


ostream& operator << (ostream& outDev, Vector& A)
{
	for (int i = 0; i < A.size; i++)
		outDev << (float)A.Data[i] << " ";
	return outDev;
}

istream& operator >> (istream& inDev, Vector& A)
{
	if (A.Data == NULL)
	{
		cout << "\nsize: ";
		inDev >> A.size;
		A.Data = new float[A.size];
	}
	cout << "input element: ";
	for (int i = 0; i < A.size; i++)
		inDev >> A.Data[i];

	return inDev;
}

const Vector Vector::operator + (const Vector& A) const
{
	Vector Sum;
	Sum.size = size > A.size ? size : A.size;
	Sum.Data = new float[Sum.size];
	for (int i = 0; i < Sum.size; i++)
	{
		Sum.Data[i] = 0;
		if (i < A.size)
			Sum.Data[i] += A.Data[i];
		if (i < size)
			Sum.Data[i] += Data[i];
	}
	return Sum;
}

const Vector Vector::operator * (double A)
{
	Vector S(A);
	for (int i = 0; i < S.size; i++)
		S.Data[i] *= A;
	return S;
}

Vector operator* (double A, Vector& X)
{
	return X * A;
}

void Vector::clear()
{
	if (Data != NULL)
	{
		delete[]Data;
		Data = NULL;
		size = 0;
	}
}

Vector::~Vector()
{
	clear();
}
