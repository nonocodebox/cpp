/**
 * This file contains a implementation to matrix,
 * This implementation switches between two different matrix representation.
 * (Sparse and Reg) this class decides the better representation to work with
 * according to a matrix's data.
 * this class uses polymorphism in order to preform matrix operations.
 */
/**
 * Answers:
 * 1. when preforming an operation, the matrix is calculated,
 * the type of the result is same as the calling instance.
 * After the calculation of the operation, the result is sent
 * to the constructor that receives its pointer.
 * inside decideReprestetion() by counting zeros the right
 * representation is to be chosen. then a new space is allocated for the 
 * copied result. I chose to check if we should cange to another represintation when the operations:
 * multiply, add, subtract - becaue during these operations the reprsetation of the 
 * matrix may change.
 * 
 * 2. Matrix: is an abstract class. using the iterators it gives us the ability
 * to implement the matrix operations no matter what the implementation is.
 * using polymorphism we deal with Matrix class only implementing
 * these operations. it holds rows' and columns' size.
 * Sparse : I implemented sparse with map, the key is the index of the matrix (1,j) so
 * the index is unique, all the matrix elements to be inserted must have a non zero value
 * Regular: I implemented regular with vector that holds a matrix's values ordered by rows.
 * operation and access are done by calculating the matrix's indexes.
 * MyMatrix: this wraps everything it has a Matrix pointer and the implement operation are called
 * using polymorphism inside this class.
 * Sparse and Reg are implementing iterator so the operations inside Matrix.h can be used and
 * written "without any connection" to a specific implementation.
 * inside Matrix we have an matrix iterator interface that is implemented inside SparseMatrix
 * and RegMatrix.
 */

#include "MyMatrix.h"
#include "RegMatrix.h"
#include "SparseMatrix.h"
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;
/**
 * decides better representation and creates a copy according to the decision.
 */
MyMatrix::MyMatrix(const MatrixPointer &_pMatrix)
{
	_copyMatrix(_pMatrix, true);
}

	/** 
	 * decides better representation if decideRepresentation is true, and creates a copy.
	 */
MyMatrix::MyMatrix(const MatrixPointer &_pMatrix, bool decideRepresentation)
{
	_copyMatrix(_pMatrix, decideRepresentation);
}

/** 
 * a class constructor, matrix's data is received by a string.
 */
MyMatrix::MyMatrix(std::string &matrix_str)
{
	_strategy(matrix_str);
}

/** 
 * a class constructor matrix's data is received by an array and size.
 */
MyMatrix::MyMatrix(double arr[], unsigned int col_size, unsigned int row_size)
{
	_strategy(arr, col_size, row_size); 
}

/** 
 * a class copy constructor.
 */
MyMatrix::MyMatrix(const MyMatrix &other)
{
	_pMatrix = other._pMatrix->createNew(other._pMatrix->getRows(), other._pMatrix->getColumns());
	_pMatrix->assign(*other._pMatrix);
}

/** 
 * array is received in constructor ordered by cols,
 * This returns a flipped one (by rows).
 */
vector<double> MyMatrix::_flipArray(const double arr[], 
									unsigned int col_size, 
									unsigned int row_size) const
{
	vector<double> result;

	for (unsigned int j = 0; j < row_size; j++)
	{
		for (unsigned int i = 0; i < col_size; i++)
		{
			result.push_back(arr[i*row_size + j]);
		}
	}

	return result;
}

/** 
 * chooses the right representation and creates a matrix by a string.
 * this method parses the string according to the given pattern,
 * decides which a representation is better.
 */
void MyMatrix::_strategy(const std::string &matrix_str)
{
	int zero = 0;
	vector<double> arr;
	istringstream iss(matrix_str);
	unsigned int rows = 0, cols = 0;

	do
	{
		string line;

		getline(iss, line);

		if (line.empty())
		{
			break;
		}

		istringstream issLine(line);

		cols = 0;

		do
		{
			double value;
			string sep;

			issLine >> value;
			issLine >> sep;

			if (fabs(value) <= EPSILON_CONST)
			{
				zero++;
			}

			arr.push_back(value);
			cols++;
		}
		while (issLine.good());

		rows++;
	}
	while (iss.good());

	int matrix_size = rows * cols;

	if (matrix_size == 0)
	{
		arr.push_back(0); // Push a dummy value so we can access &arr[0]
	}

	if (zero <= matrix_size / 2)
	{
		_pMatrix = MatrixPointer(new RegMatrix(&arr[0], rows, cols));
	}
	else
	{
		_pMatrix = MatrixPointer(new SparseMatrix(&arr[0], rows, cols));
	}
}

/** 
 * chooses the right representation and creates a matrix by a given array.
 * this method counts zeros and by that decides which a representation is better.
 */
void MyMatrix::_strategy(const double arr[], unsigned int col_size, unsigned int row_size)
{
	int zero = 0;
	int matrix_size = row_size * col_size;
	for (int i = 0; i < matrix_size; i++)
	{
		if (fabs(arr[i]) <= EPSILON_CONST)
		{
			zero++;
		}
	}

	vector <double> data = _flipArray(arr, col_size, row_size);

	if (matrix_size == 0)
	{
		data.push_back(0); // Push a dummy value so we can access &data[0]
	}

	if (zero <= matrix_size / 2)
	{
		_pMatrix = MatrixPointer(new RegMatrix(&data[0], row_size, col_size));
	}
	else
	{
		_pMatrix = MatrixPointer(new SparseMatrix(&data[0], row_size, col_size));
	}
}

/** 
 * calculates a matrix's trace.
 */
double MyMatrix::trace() const
{
	return _pMatrix->trace();
}

/** 
 * calculates a matrix's frobenius norm.
 */
double MyMatrix::frobeniusNorm() const
{
	return _pMatrix->frobeniusNorm();
}

/** 
 * a class destructor.
 */
MyMatrix::~MyMatrix()
{
}

/** 
 * an assignment operator.
 */
MyMatrix& MyMatrix::operator=(const MyMatrix& other)
{
	if (&other != this)
	{
		_pMatrix = other._pMatrix->createNew(other._pMatrix->getRows(), other._pMatrix->getRows());
		_pMatrix->assign(*(other._pMatrix));
	}

	return *this;
}

/** 
 * minus operator.
 */
MyMatrix MyMatrix::operator-(const MyMatrix&  other) const
{
	return *this + (-other);
}

/** 
 * plus operator.
 */
MyMatrix MyMatrix::operator+(const MyMatrix&  other) const
{
	MatrixPointer pResult = _pMatrix->add(*(other._pMatrix));
	return MyMatrix(pResult);
}

/** This method counts zeros and by that decides which a representation is better.
 */
Matrix::Type MyMatrix::_decideRepresintation(const MatrixPointer &matrix) const
{
	unsigned int zero = 0;
	for (Matrix::IteratorPointer it = matrix->createIterator(); !it->isEnd(); ++(*it))
	{
		if (fabs((**it).second) <= EPSILON_CONST)
		{
			zero++;
		}
	}

	if (zero > matrix->getRows() * matrix->getColumns() / 2)
	{
		return Matrix::SPARSE_MATRIX;
	}
	else
	{
		return Matrix::REG_MATRIX;
	}
}

/** 
 * by creates a suitable matrix by decision or directly and assigns pOriginal.
 */
void MyMatrix::_copyMatrix(const MatrixPointer &pOriginal, bool decideRepresintation)
{
	MatrixPointer pConvert;

	if (decideRepresintation)
	{
		if(_decideRepresintation(pOriginal) == Matrix::REG_MATRIX)
		{
			pConvert = MatrixPointer(new RegMatrix(pOriginal->getRows(), pOriginal->getColumns()));
		}
		else 
		{
			pConvert = MatrixPointer(new SparseMatrix(pOriginal->getRows(), 
													  pOriginal->getColumns()));
		}
	}
	else
	{
		pConvert = pOriginal->createNew(pOriginal->getRows(), pOriginal->getColumns());
	}
	
	pConvert->assign(*pOriginal);
	_pMatrix = pConvert;
}

/** 
 * multiply operator.
 */
MyMatrix MyMatrix::operator*(const MyMatrix&  other) const
{
	MatrixPointer pResult = _pMatrix->multiply(*(other._pMatrix));
	return MyMatrix(pResult);
}

/** 
 * += operator
 */
MyMatrix& MyMatrix::operator+=(const MyMatrix& other)
{
	*this = *this + other;
	return *this;
}

/** 
 * -= operator
 */
MyMatrix& MyMatrix::operator-=(const MyMatrix& other)
{
	*this = *this - other;
	return *this;
}

/** 
 * *= operator
 */
MyMatrix& MyMatrix::operator*=(const MyMatrix& other)
{
	*this = *this * other;
	return *this;
}

/** 
 * equals operator.
 */
bool MyMatrix::operator==(const MyMatrix& other) const
{
	return _pMatrix->isEquals(*(other._pMatrix));
}

/** 
 * not equals operator.
 */
bool MyMatrix::operator!=(const MyMatrix& other) const
{
	return !(*this == other);
}

/** 
 *  unary minus operator.
 */
MyMatrix MyMatrix::operator-() const
{
	MatrixPointer pResult = _pMatrix->minus();
	return MyMatrix(pResult, false);
}

/** 
 * << operator.
 */
ostream& MyMatrix::operator<<(ostream& os) const
{
	return _pMatrix->printMatrix(os);
}

Matrix::Type MyMatrix::getType() const
{
	return _pMatrix->getType();
}
