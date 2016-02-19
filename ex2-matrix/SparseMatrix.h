/**
 * This file contains an representation implementation to matrix.
 */
#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include "Matrix.h"

typedef Map::const_iterator MapIterator;

/**
 * This class is an implementation of representation of a matrix.
 * a sparse matrix.
 */
class SparseMatrix : public Matrix
{
public:
	
	/** 
	 * a class constructor matrix's data is received by an array and size.
	 */
	SparseMatrix(const double arr[], unsigned int row_size, unsigned int col_size);

	/** 
	 * a class constructor by size.
	 */
	SparseMatrix(unsigned int row_size, unsigned int col_size);
	
	/** 
	 * a class destructor.
	 */
	virtual ~SparseMatrix();

	/** 
	 * change value in matrix (row, col and value).
	 */
	virtual void setValue(unsigned int row, unsigned int col, double value);

	/** 
	 * create and allocate a new iterator of a sparse matrix.
	 */
	virtual IteratorPointer createIterator() const;

	/** 
	 * create and allocate a new instance,
	 * with the size rows * cols.
	 */
	virtual MatrixPointer createNew(unsigned int rows, unsigned int cols) const;

	/** 
	 * returns this class matrix type.
	 */
	virtual Matrix::Type getType() const;

private:
	/** 
	 * a SparseMatrix iterator.
	 */
	class SparseIterator : public Iterator
	{
	public:
		/** 
		 * a class copy constructor.
		 */
		SparseIterator(const SparseMatrix &mat);

		/** 
		 * a class destructor.
		 */
		virtual ~SparseIterator();

		/** 
		 * dereference operator.
		 */
		virtual MatrixElement operator*() const;

		/** 
		 * increment operator.
		 */
		virtual Iterator& operator++();

		/** 
		 * is container's end.
		 */
		virtual bool isEnd() const;

	private:
		const SparseMatrix &_matrix;
		MapIterator _iter;
		unsigned int _curRowNum, _curColNum;
		
		/** 
		 * are a iterator and the current index of a matrix the same.
		 */
		bool _isIterCurrent() const;
	};

	friend class SparseIterator;

	Map _matrix;

	/** 
	 * resets a matrix with the size rows * cols.
	 */
	void _resetMatrix(unsigned int rows, unsigned int cols);
};

#endif // SPARSE_MATRIX_H
