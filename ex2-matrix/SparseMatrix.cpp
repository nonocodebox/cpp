/**
 * This file contains an representation implementation to matrix.
 * a sparse matrix. implementation of "SparseMatrix.h"
 */
#include "SparseMatrix.h"
#include <cmath>

using namespace std;

/** 
 * a class copy constructor.
 */
SparseMatrix::SparseIterator::SparseIterator(const SparseMatrix &mat)
: _matrix(mat), _iter(mat._matrix.begin()), _curRowNum(0), _curColNum(0)
{
}

/** 
 * a class destructor.
 */
SparseMatrix::SparseIterator::~SparseIterator()
{
	_iter = MapIterator(); // Remove connection to parent map
}

/** 
 * dereference operator.
 * if the iterator is not the same as the current index of a matrix,
 * we return zero because there is no such element in the map.
 */
MatrixElement SparseMatrix::SparseIterator::operator*() const
{
	if (_isIterCurrent())
	{
		return *_iter;
	}
	else
	{
		return MatrixElement(Pair(_curRowNum, _curColNum), 0);
	}
}

/** 
 * increment operator. if the iterator is not the same as the current index of a matrix,
 * we increment to the next index, till it matches the iterator.
 */
Matrix::Iterator& SparseMatrix::SparseIterator::operator++()
{
	if (!isEnd())
	{
		if (_isIterCurrent())
		{
			_iter++;
		}

		_curColNum++;

		if (_curColNum >= _matrix._cols)
		{
			_curColNum = 0;
			_curRowNum++;
		}
	}

	return *this;
}

/** 
 * is container's end, if we reached the last row.
 */
bool SparseMatrix::SparseIterator::isEnd() const
{
	return (_curRowNum >= _matrix._rows);
}

/** 
 * are a iterator and the current index of a matrix the same.
 */
bool SparseMatrix::SparseIterator::_isIterCurrent() const
{
	return (_iter != _matrix._matrix.end() && 
		   (_iter->first.first == _curRowNum && _iter->first.second == _curColNum));
}

/** 
 * a class constructor by size.
 */
SparseMatrix::SparseMatrix(unsigned int row_size, unsigned int col_size)
: Matrix(row_size, col_size)
{
	_resetMatrix(row_size, col_size);
}

/** 
 * a class constructor matrix's data is received by an array and size.
 * inserts each element (if bigger than zero).
 */
SparseMatrix::SparseMatrix(const double arr[], unsigned int row_size, unsigned int col_size)
: Matrix(row_size, col_size)
{
	for (unsigned int i = 0; i < row_size * col_size; i++)
	{
		if (fabs(arr[i]) > EPSILON_CONST)
		{
			_matrix.insert(pair<Pair, double>(Pair(i / col_size, i % col_size), arr[i]));
		}
	}
}

/** 
 * a class destructor.
 */
SparseMatrix::~SparseMatrix()
{
}

/** 
 * change value in map(matrix) (row, col and value).
 */
void SparseMatrix::setValue(unsigned int row, unsigned int col, double value)
{
	if (fabs(value) > EPSILON_CONST)
	{
		_matrix.insert(pair<Pair, double>(Pair(row, col), value));
	}
}

/** 
 * create and allocate a new iterator of a sparse matrix.
 */
Matrix::IteratorPointer SparseMatrix::createIterator() const
{
	return IteratorPointer(new SparseIterator(*this));
}

/** 
 * create and allocate a new instance,
 * with the size rows * cols.
 */
MatrixPointer SparseMatrix::createNew(unsigned int rows, unsigned int cols) const
{
	return MatrixPointer(new SparseMatrix(rows, cols));
}

/** 
 * resets a matrix with the size rows * cols.
 * cleans map.
 */
void SparseMatrix::_resetMatrix(unsigned int rows, unsigned int cols)
{
	_rows = rows;
	_cols = cols;
	_matrix.clear();
}

/** 
 * returns this class matrix type.
 */
Matrix::Type SparseMatrix::getType() const
{
	return Matrix::SPARSE_MATRIX;
}
