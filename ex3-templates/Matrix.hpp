/** 
 * Was written by:
 *      .-') _                          ('-.     _  .-')   
 *     ( OO ) )                        ( OO ).-.( \( -O )  
 * ,--./ ,--,'  .-'),-----.    ,------./ . --. / ,------.  
 * |   \ |  |\ ( OO'  .-.  '('-| _.---'| \-.  \  |   /`. ' 
 * |    \|  | )/   |  | |  |(OO|(_\  .-'-'  |  | |  /  | | 
 * |  .     |/ \_) |  |\|  |/  |  '--.\| |_.'  | |  |_.' | 
 * |  |\    |    \ |  | |  |\_)|  .--' |  .-.  | |  .  '.' 
 * |  | \   |     `'  '-'  '  \|  |_)  |  | |  | |  |\  \  
 * `--'  `--'       `-----'    `--'    `--' `--' `--' '--'
 *
 * This file contaims implementation of a template matrix.
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "ExceptionBadSize.h"
#include "ExceptionBadInput.h"
#include "Rational.h"
#include <vector>
#include <algorithm> // for std::swap()
#include <utility> // for std::move()

#define MATRIX_ELEM_SEPERATOR " "
#define INITIAL_SIZE 1
#define NEW_LINE "\n"
#define END_NEW_LINE " \n"
#define SEPCIAL_STR "Performing specialized function of trace for Rational values"

#define CTOR_BAD_SIZE "Bad input size"
#define ADD_BAD_SIZE "Bad addition, sizes don't match"
#define MULTIPLY_BAD_SIZE "Bad multiply, sizes don't match"

template <typename T> class Matrix;
template <typename T> Matrix<T> operator*(const T& scalar, const Matrix<T> &matrix);
template <typename T> std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

/**
 * This represents a tempate matrix class, it supports the operations:
 * <<, +, *, = .
 */
template <class T>
class Matrix
{
public:
	/**
	 * a default constructor initializes 1X1 matrix
	 */
	Matrix()
		: Matrix(INITIAL_SIZE, INITIAL_SIZE)
	{
	}

	/**
	 * a class constructor that recives row size and col size.
	 */
	Matrix(unsigned int rows, unsigned int cols)
	{
	    if (rows == 0 || cols == 0)
		{
			throw ExceptionBadInput(CTOR_BAD_SIZE);
		}
		
		_rows = rows;
		_cols = cols;
		_matrix.clear();
		_matrix.resize(rows * cols);
	}

	/**
	* a class constructor that recives row size, col size and vector
	* of matrix's elements in order to inizialize a metrix's values.
	*/
	Matrix(unsigned int rows, unsigned int cols, std::vector<T> t_arr)
		: Matrix(rows, cols)
	{
		if (t_arr.size() != rows * cols)
		{
			throw ExceptionBadInput(CTOR_BAD_SIZE);
		}

		_matrix = std::vector<T>(t_arr);
	}

	/**
	* a class copy constructor.
	*/
	Matrix(const Matrix<T> & t_other)
		: Matrix(t_other._rows, t_other._cols)
	{
		_matrix = std::vector<T>(t_other._matrix);
	}

	/**
	* a class move constructor.
	*/
	Matrix(Matrix<T> && t_other)
		: _rows(t_other._rows), _cols(t_other._cols), _matrix(std::move(t_other._matrix))
	{
		// initialize other's values.
		t_other._rows = INITIAL_SIZE;
		t_other._cols = INITIAL_SIZE;
		// no need to call t_other._matrix.clear() we already called the vector's move ctor.
	}

	/**
	 * plus operator.
	 * sets result's values with the sum of other's and current instance's values.
	 */
	Matrix<T> operator+(const Matrix<T>&  t_other) const
	{
		if (_rows != t_other._rows || _cols != t_other._cols)
		{
			throw ExceptionBadSize(ADD_BAD_SIZE);
		}

		Matrix<T> result(_rows, _cols);

		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				result._setValue(i, j, _getValue(i, j) + t_other._getValue(i, j));
			}
		}

		return result;
	}

	/**
	 * multiply operator.
	 * multiplies this matrix and other.
	 * this is done by transposing other and multiply each row of this matrix,
	 * by all other's elements by order.
	 * allocates new space for the result matrix and fills it by the
	 * explained calculation.
	 */
	Matrix<T> operator*(const Matrix<T>&  t_other) const
	{
		if (_cols != t_other._rows)
		{
			throw ExceptionBadSize(MULTIPLY_BAD_SIZE);
		}

		Matrix<T> result(_rows, t_other._cols);
		Matrix<T> t_otherTranspose = t_other.transpose();

		for (unsigned int i = 0; i < _rows; ++i)
		{
			/**
			* create a this matrix row
			*/
			std::vector<T> row;

			for (unsigned int j = 0; j < _cols; ++j)
			{
				row.push_back(_getValue(i, j));
			}

			for (unsigned int p = 0; p < t_other._cols; ++p)
			{
				T value = T();

				for (unsigned int q = 0; q < _cols; ++q)
				{
					value = value + (row[q] * t_otherTranspose._getValue(p, q));
				}

				result._setValue(i, p, value);
			}
		}

		return result;
	}

	/**
	 * multiplies a matrix by a scalar. 
	 * simply done by multiply each matrix element with a scalar.
	 */
	Matrix<T> operator*(const T& t_scalar) const
	{
		Matrix<T> diag(_cols, _cols);
		
		for (unsigned int i = 0; i < _cols; i++)
		{
			diag._setValue(i, i, t_scalar);
		}

		return *this * diag;
	}

	/**
	 * a copy-and-swap assignment operator.
	 */
	Matrix<T> & operator=(Matrix<T> t_other)
	{
		swap(*this, t_other);

		return *this;
	}

	/**
	 * whether a matrix has a trace. if it does, overrides trace's value with a matrix's trace.
	 */
	bool hasTrace(T& t_trace) const
	{
		t_trace = T();
		if (_rows != _cols)
		{
			return false;
		}

		for (unsigned int i = 0; i < _rows; i++)
		{
			t_trace = t_trace + _getValue(i, i);
		}

		return true;
	}

	/**
	 * Tansposes a matrix. calculated by switching <i,j> to <j,i>.
	 */
	Matrix<T> transpose() const
	{
		Matrix<T> result(_cols, _rows);

		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				result._setValue(j, i, _getValue(i, j));
			}
		}

		return result;
	}

	/**
	 * prints a matrix by the given structue of printing.
	 * recives an osteam and the matrix to be printed to it.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Matrix<T> & t_matrix)
	{
		for (unsigned int i = 0; i < t_matrix._rows; i++)
		{
			for (unsigned int j = 0; j < t_matrix._cols; j++)
			{
				os << t_matrix._getValue(i, j);

				if (i == t_matrix._rows - 1 && j == t_matrix._cols - 1)
				{
					os << NEW_LINE;
					break;
				}

				if (j != t_matrix._cols - 1)
				{
					os << MATRIX_ELEM_SEPERATOR;
				}
				else
				{
					os << END_NEW_LINE;
				}
			}
		}

		return os;
	}

	/**
	 * multiplies a scalar by a matrix.
	 * simply done by multiply each matrix element with a scalar.
	 *
	 * see Matrix<T> operator*(const T& scalar) const.
	 */
	friend Matrix<T> operator*(const T& t_scalar, const Matrix<T>& t_matrix)
	{
		return t_matrix * t_scalar;
	}
	
	/**
	 * swaps this instance's members with an other instance's members.
	 */
	friend void swap(Matrix<T> &lhs, Matrix<T> &rhs)
	{
		using std::swap;
		
		swap(lhs._rows, rhs._rows);
		swap(lhs._cols, rhs._cols);
		swap(lhs._matrix, rhs._matrix);
	}
	
private:
	unsigned int _rows;
	unsigned int _cols;
	std::vector<T> _matrix;
	
	/**
     * changes a value in matrix (row, col and value).
	 */
	void _setValue(unsigned int row, unsigned int col, T t_value)
	{
		_matrix[row * _cols + col] = t_value;
	}
	
	/**
	* gets a value in matrix at index <row, col>.
	*/
	T _getValue(unsigned int row, unsigned int col) const
	{
		return _matrix[row * _cols + col];
	}
};

/**
 * a specialized function of hasTrace.
 * first, find the multyplation of all denominators.
 * then, multiply each numerator with all other denominators.
 *
 * see hasTrace()
 */
template<>
bool Matrix<Rational>::hasTrace(Rational& trace) const
{
	std::cout << SEPCIAL_STR << std::endl;
	trace = Rational();

	if (_rows != _cols)
	{
		return false;
	}

	long int resultNumerator = 0;
	long int resultDeninator = 1;

	for (unsigned int i = 0; i < _rows; i++)
	{
		resultDeninator *= _getValue(i, i).getDenominator();
	}

	for (unsigned int i = 0; i < _rows; i++)
	{
		resultNumerator += 
			(_getValue(i, i).getNumerator() * resultDeninator) / _getValue(i, i).getDenominator();
	}

	trace = Rational(resultNumerator, resultDeninator);

	return true;
}

#endif
