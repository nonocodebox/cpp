/**
 * This file contains an representation implementation to a regular matrix.
 * implementation of "RegMatrix.h".
 */

#include "RegMatrix.h"
#include <cmath>

using namespace std;

/** 
 * a class copy constructor.
 */
RegMatrix::RegIterator::RegIterator(const RegMatrix &mat)
: _matrix(mat), _iter(0)
{
}

/** 
 * dereference operator, calculated by the vector's index.
 */
MatrixElement RegMatrix::RegIterator::operator*() const
{
	return MatrixElement(Pair(_iter / _matrix._cols, _iter % _matrix._cols), 
						 _matrix._matrix[_iter]);
}

/** 
 * increment operator.
 */
Matrix::Iterator& RegMatrix::RegIterator::operator++()
{
	if (!isEnd())
	{
		_iter++;
	}

	return *this;
}

/** 
 * is container's end, whether the current index reached the vector's size. 
 */
bool RegMatrix::RegIterator::isEnd() const
{
	return (_iter == _matrix._rows * _matrix._cols);
}

/** 
 * a class constructor by size.
 */
RegMatrix::RegMatrix(unsigned int row_size, unsigned int col_size)
: Matrix(row_size, col_size)
{
	_resetMatrix(row_size, col_size);
}

/** 
 * a class constructor matrix's data is received by an array and size.
 */
RegMatrix::RegMatrix(const double arr[], unsigned int row_size, unsigned int col_size)
: Matrix(row_size, col_size)
{
	_matrix = vector<double>(arr, arr + col_size * row_size);
}

/** 
 * a class destructor.
 */
RegMatrix::~RegMatrix()
{
}

/** 
 * change value in vector(matrix) (row, col and value).
 */
void RegMatrix::setValue(unsigned int row, unsigned int col, double value)
{
	_matrix[row*_cols + col] = value;
}

/** 
 * create and allocate a new iterator of a sparse matrix.
 */
Matrix::IteratorPointer RegMatrix::createIterator() const
{
	return IteratorPointer(new RegIterator(*this));
}

/** 
 * create and allocate a new instance,
 * with the size rows * cols.
 */
MatrixPointer RegMatrix::createNew(unsigned int rows, unsigned int cols) const
{
	return MatrixPointer(new RegMatrix(rows, cols));
}

/** 
 * resets a matrix with the size rows * cols.
 * cleans vector and resizes vector.
 */
void RegMatrix::_resetMatrix(unsigned int rows, unsigned int cols)
{
	_rows = rows;
	_cols = cols;
	_matrix.clear();
	_matrix.resize(rows * cols);
}

/** 
 * returns this class matrix type.
 */
Matrix::Type RegMatrix::getType() const
{
	return REG_MATRIX;
}
