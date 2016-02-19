/**
 * This file contains a "generic" implemntation to matrix,
 * Sparse and Reg are to be oprerated using Matrix.h's functions
 * due to polymorphism.
 * implementation of Matrix.h
 */

#include "Matrix.h"
#include <vector>
#include <cmath>
#include <sstream>

#define ZERO_MATRIX_STRING "0\n"
#define MATRIX_ELEM_SEPERATOR " , "
#define PRECISION 5

//TODO: const param, magic, valgrined
using namespace std;

/** 
 * a class constructor [used by the derives].
 */
Matrix::Matrix(unsigned int rows, unsigned int cols)
: _rows(rows), _cols(cols)
{
}


/** 
 * a class destructor.
 */
Matrix::~Matrix()
{
}

/**
 * if matrix is not N*N return zero.
 * this is done by iterating each element in matrix s.t i = j
 */
double Matrix::trace() const
{
	double trace = 0.0;
	if (_rows != _cols)
	{
		return trace;
	}

	for (IteratorPointer it = createIterator(); !it->isEnd(); ++(*it))
	{
		if ((**it).first.first == (**it).first.second)
		{
			trace += (**it).second;
		}
	}

	return trace;
}

/**
 * returns new allocated traced matrix.
 * calculated by switching <i,j> to <j,i>.
 */
MatrixPointer Matrix::transpose() const
{
	MatrixPointer pMatrix = createNew(_cols, _rows);

	for (IteratorPointer it = createIterator(); !it->isEnd(); ++(*it))
	{
		pMatrix->setValue((**it).first.second, (**it).first.first, (**it).second);
	}

	return pMatrix;
}

/**
 * calculated : trace(AA^t).
 */
double Matrix::frobeniusNorm() const
{
	MatrixPointer transMat = transpose();
	MatrixPointer result = multiply(*transMat);
	return result->trace();
}

/**
 * resets the current matrix, and filling it with other's values.
 */
void Matrix::assign(const Matrix& other)
{
	_resetMatrix(other._rows, other._cols);

	for (IteratorPointer it = other.createIterator(); !it->isEnd(); ++(*it))
	{
		setValue((**it).first.first, (**it).first.second, (**it).second);
	}
}

/** 
 * adds this to other assuming.
 * this is done by iterating on both at the same time.
 */
MatrixPointer Matrix::add(const Matrix&  other) const
{
	if (other._rows != _rows || other._cols != _cols)
	{
		return MatrixPointer(NULL);
	}

	MatrixPointer pResult = createNew(_rows, _cols);

	auto_ptr<Iterator> itOther = other.createIterator();
	auto_ptr<Iterator> itThis = createIterator();

	for (; !itThis->isEnd(); ++(*itThis), ++(*itOther))
	{
		pResult->setValue((**itThis).first.first, 
						  (**itThis).first.second, 
						  (**itThis).second + (**itOther).second);	
	}

	return pResult;
}

/** 
 * multiplies this matrix and other.
 * this is done by transposing other and multiply each row of this matrix,
 * by all other's elements by order.
 * allocates new space for the result matrix and fills it by the 
 * explained calculation.
 */
MatrixPointer Matrix::multiply(const Matrix&  other) const
{
	MatrixPointer pResult = createNew(_rows, other._cols);
	MatrixPointer pOtherTranspose = other.transpose();

	IteratorPointer itThis = createIterator();

	for (unsigned int i = 0; i < _rows; ++i)
	{
		/**
		 * create a this matrix row
		 */
		vector<double> row;
		
		for (unsigned int j = 0; j < _cols; ++j, ++(*itThis))
		{
			row.push_back((**itThis).second);
		}

		IteratorPointer itOther = pOtherTranspose->createIterator();

		for (unsigned int p = 0; p < other._cols; ++p)
		{
			double value = 0;

			for (unsigned int q = 0; q < _cols; ++q, ++(*itOther))
			{
				value += row[q] * (**itOther).second;
			}

			pResult->setValue(i, p, value);
		}
	}

	return pResult;
}

/** 
 * checks whether this matrix elements' are equals to other.
 * this is done by iterating on both at the same time.
 */
bool Matrix::isEquals(const Matrix& other) const
{
	if (other._rows != _rows || other._cols != _cols)
	{
		return false;
	}

	IteratorPointer itThis = createIterator();
	IteratorPointer itOther = other.createIterator();

	for (; !itThis->isEnd(); ++(*itThis), ++(*itOther))
	{
		if (fabs((**itThis).second - (**itOther).second) > EPSILON_CONST)
		{
			return false;
		}
	}

	return true;
}

/** 
 * negates matrix's elements by using an iterator.
 */
MatrixPointer Matrix::minus() const
{
	MatrixPointer pMatrix = createNew(_rows, _cols);

	for (IteratorPointer it = createIterator(); !it->isEnd(); ++(*it))
	{
		pMatrix->setValue((**it).first.first, (**it).first.second, -((**it).second));
	}

	return pMatrix;
}

/** 
 * whether a zero matrix.
 */
bool Matrix::_isAllZero() const
{
	unsigned int zero = 0;
	for (IteratorPointer it = createIterator(); !it->isEnd(); ++(*it))
	{
		if (fabs((**it).second) <= EPSILON_CONST)
		{
			zero++;
		}
	}

	return (zero == _cols * _rows);
}

/**
 * Print a double value with precision PRECISION.
 * If the value is too long it is rounded to PRECISION.
 */
string Matrix::_printDouble(double value) const
{
	if (fabs(value) <= EPSILON_CONST)
	{
		return "0"; // Handle negative zeros
	}
	
	ostringstream oss;
	
	// Get the number of digits to the left of the floating point
	int digits = floor(log10(fabs(value))) + 1;
	
	oss.precision(digits + PRECISION);
	oss << value;
	
	return oss.str();
}

/**
 * if matrix is all zero we print zero,
 * else we iterate each element and read the next number:
 * if we reach the last column we print "new line",
 * else a matrix's element separator
 */
ostream& Matrix::printMatrix(ostream& os) const
{
	if (_isAllZero())
	{
		os << ZERO_MATRIX_STRING;
	}

	else
	{
		IteratorPointer it = createIterator();

		os.precision(PRECISION);
		
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				os << _printDouble((**it).second);

				if (j != _cols - 1)
				{
					os << MATRIX_ELEM_SEPERATOR;
				}
				else
				{
					os << "\n";
				}

				++(*it);
			}
		}
	}

	return os;
}

/** 
 * returns a matrix's number of rows.
 */
unsigned int Matrix::getRows() const
{
	return _rows;
}

/** 
 * returns a matrix's number of columns.
 */
unsigned int Matrix::getColumns() const
{
	return _cols;
}
