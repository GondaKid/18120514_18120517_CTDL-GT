#include "Matrix.h"


Matrix::Matrix(const Matrix& _matrix)
{
	row = _matrix.row;
	col = _matrix.col;
	A = new double*[row];
	for (int i = 0; i < row; i++)
		A[i] = new double[col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			A[i][j] = _matrix.A[i][j];
}

Matrix::Matrix()
{
	A = NULL;
	row = 0;
	col = 0;
}

Matrix::Matrix(int n) :Matrix(n, n) { }

Matrix::Matrix(int _row, int _col)
{
	row = _row;
	col = _col;
	A = new double*[row];
	for (int i = 0; i < row; i++)
		A[i] = new double[col];

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			A[i][j] = 0;
	}
}

Matrix::~Matrix()
{
	clear();
}

bool Matrix::Is_empty()
{
	return row == 0;
}

const Matrix& Matrix::operator = (const Matrix& A)
{
	if (this->A != NULL)
	{
		this->clear();
	}

	this->row = A.row;
	this->col = A.col;
	this->A = new double*[row];
	for (int i = 0; i < row; i++)
		this->A[i] = new  double[col];

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			this->A[i][j] = A.A[i][j];
	return *this;
}

istream& operator >> (istream& inDev, Matrix& matrix)
{
	if (matrix.row == 0 && matrix.col == 0) {
		cout << "\nrow = "; inDev >> matrix.row;
		cout << "col = ";   inDev >> matrix.col;
		matrix.A = new double*[matrix.row];
		for (int i = 0; i < matrix.row; i++)
			matrix.A[i] = new double[matrix.col];
	}
	cout << "\n input matrix\n";
	for (int i = 0; i < matrix.row; i++) {
		for (int j = 0; j < matrix.col; j++)
			inDev >> matrix.A[i][j];
	}
	return inDev;
}

ostream& operator << (ostream& outDev, Matrix& matrix)
{
	if (matrix.A != NULL)
	{
		for (int i = 0; i < matrix.row; i++)
		{
			for (int j = 0; j < matrix.col; j++)
				cout << matrix.A[i][j] << " ";
			cout << endl;
		}
	}
	return outDev;
}

double Matrix::det(Matrix& X)
{
	if (X.row == 1 && X.col == 1)
		return X.A[0][0];
	else if (X.row == 2 && X.col == 2)
	{
		return X.A[0][0] * X.A[1][1] - X.A[1][0] * X.A[0][1];
	}
	else
	{
		double sum = 0;
		for (int i = 0; i < X.col; i++)
		{
			Matrix A = X.subMatrix(0, i);
			sum += pow(-1, 2 + i)*X.A[0][i] * Matrix::det(A);
		}
		return sum;
	}

}

double Matrix::det()
{
	return Matrix::det(*this);
}


Matrix Matrix::Adj()const
{
	Matrix Adj(row, col);
	Matrix temp = *this;
	for(int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			Matrix X = temp.subMatrix(i, j);
			Adj.A[i][j] = pow(-1, i + j + 2) * X.det();
			
		}
	return Adj.T();
}


Matrix Matrix::T()const
{
	Matrix newMatrix(col, row);
	int idex = 0;
	for (int i = 0; i < col; i++)
		for (int j = 0; j < row; j++)
		{
			newMatrix.A[idex / row][idex%row] = A[j][i];
			idex++;
		}
	return newMatrix;
}

// return inverse of this matrix
Matrix Matrix::inverse()
{
	if (this->det() != 0.0)
		return this->Adj() * abs(this->det());
	else
		throw;
}

const Matrix Matrix::operator * (const Matrix& a) const
{
	if (col != a.row)
	{
		throw;
	}
	else
	{
		Matrix newMatrix(row, a.col);
		for (int i_newMatrix = 0; i_newMatrix < row; i_newMatrix++)
			for (int j_newMatrix = 0; j_newMatrix < a.col; j_newMatrix++)
			{
				newMatrix.A[i_newMatrix][j_newMatrix] = 0;
				// mutiply row_i of this and col_j of a
				for (int i = 0; i < col; i++)
				{
					newMatrix.A[i_newMatrix][j_newMatrix] += A[i_newMatrix][i] * a.A[i][j_newMatrix];
				}
			}
		return newMatrix;
	}
}

const Matrix Matrix::operator * (double X) const
{
	Matrix newMatrix(row, col);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
			newMatrix.A[i][j] = X * A[i][j];
	}
	return newMatrix;
}
	
// creates a Matrix without _row && _col 
Matrix Matrix::subMatrix(int _row, int _col) 
{
	Matrix newMatrix(row - 1, col - 1);
	int idex = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i != _row && j != _col) {
				newMatrix.A[idex / newMatrix.col][idex%newMatrix.col] = A[i][j];
				idex++;
			}
		}
	}
	return newMatrix;
}

Matrix Matrix::subMatrix(int _col) 
{
	Matrix newMatrix(row, col - 1);
	for (int i = 0; i < row; i++)
		newMatrix.A[i][_col] = A[i][col - 1];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col - 1; j++)
			if (j != _col)
				newMatrix.A[i][j] = A[i][j];
	return newMatrix;
}


const Matrix Matrix::MatrixRank()
{
	Matrix temp = *this;
	int _row = 0, _col = 0;
	int rank = 0;
	while (_row < row && _col < col)
	{
		if (temp.A[_row][_col] != 0.0) {
			for (int i = _row + 1; i < row; i++)
			{
				double c = temp.A[i][_col] / temp.A[_row][_col];
				for (int j = _col; j < col; j++)
				{
					temp.A[i][j] = temp.A[i][j] - c * temp.A[_row][j];
				}
			}
			_row++;
			_col++;
		}
		else
		{
			for (int k = _row + 1; k < row; k++)
			{
				if (temp.A[k][_row] != 0)
				{
					swap(temp.A[_row], temp.A[k]);
					continue;
				}
			}
			_col++;
		}
	}
	return temp;
}
int Matrix::rank()
{
	const Matrix temp = this->MatrixRank();
	int rank = 0;
	for (int i = 0; i < row; i++)
	{
		int flag = 0;;
		for (int j = 0; j < col; j++)
		{
			if (temp.A[i][j] != 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
			rank++;
	}
	return rank;
}


void Matrix::setValue(int _row, int _col, double value)
{
	if (_row >= 0 && _row <= row && _col >= 0 && _col <= col)
	{
		A[_row][_col] = value;
	}
	else
	{
		cout << "\nerror row, col !!!";
	}
}

void Matrix::clear()
{
	if (A != NULL)
	{
		for (int i = 0; i < row; i++)
			delete[]A[i];
		delete[]A;
		A = NULL;
		row = 0;
		col = 0;
	}
}


void Matrix::solve()
{
	Matrix X;
	cin >> X;
	if (X.col - 1 == X.row) {
		vector<Matrix> M;
		M.resize(X.col - 1);
		vector <double> det;
		for (int i = 0; i < X.col - 1; i++) {
			Matrix A = X;
			M[i] = A.subMatrix(i);
			det.push_back(M[i].det());
		}

		Matrix M_0(X.row, X.col - 1);
		for (int i = 0; i < X.row; i++)
			for (int j = 0; j < X.col - 1; j++)
				M_0.A[i][j] = X.A[i][j];
		det.push_back(M_0.det());

		if (det.back() != 0.0)
		{
			int n = det.size();
			cout << "\nPhuong trinh co " << n - 1 << " nghiem:\n";
			for (int i = 0; i < n - 1; i++)
				cout << det[i] / det[n - 1] << " ";
		}
		else
		{
			Matrix B = X.MatrixRank();
			for (int i = X.row - 1; i >= 0; i--)
			{
				if ((B.A[i][X.col - 2] == 0.0 && B.A[i][X.col - 1] != 0) || (B.A[i][X.col - 2] != 0.0 && B.A[i][X.col - 1] == 0))
				{
					cout << "He vo nghiem";
					return;
				}
			}
			cout << "He co vo so nghiem";
		}
	}
	else
	{
		Matrix B = X.MatrixRank();
		for (int i = X.row - 1; i >= 0; i--)
		{
			if ((B.A[i][X.col - 2] == 0.0 && B.A[i][X.col - 1] != 0) || (B.A[i][X.col - 2] != 0.0 && B.A[i][X.col - 1] == 0))
			{
				cout << "He vo nghiem";
				return;
			}
		}
		cout << "He co vo so nghiem";

	}
}