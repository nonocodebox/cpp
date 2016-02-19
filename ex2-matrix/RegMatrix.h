/**
 * This file contains an representation implementation to matrix.
 */
#ifndef REG_MATRIX_H
#define REG_MATRIX_H

#include "Matrix.h"
#include <vector>

/**
 * This class is an implementation of representation of a matrix.
 * a regular matrix.
 */
class RegMatrix : public Matrix
{
public:

	/** 
	 * a class constructor matrix's data is received by an array and size.
	 */
	RegMatrix(const double arr[], unsigned int row_size, unsigned int col_size);
	
	/** 
	 * a class constructor by size.
	 */
	RegMatrix(unsigned int row_size, unsigned int col_size);

	/** 
	 * a class destructor.
	 */
	virtual ~RegMatrix();

	/** 
	 * change value in matrix (row, col and value).
	 */
	virtual void setValue(unsigned int row, unsigned int col, double value);

	/** 
	 * create and allocate a new iterator of a regular matrix.
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
	 * a RegIterator iterator.
	 */
	class RegIterator : public Iterator
	{
	public:

		/** 
		 * a class copy constructor.
		 */
		RegIterator(const RegMatrix &mat);

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
		const RegMatrix &_matrix;
		unsigned int _iter;
	};

	std::vector<double> _matrix;

	friend class RegIterator;

	/** 
	 * resets a matrix with the size rows * cols.
	 */
	void _resetMatrix(unsigned int rows, unsigned int cols);
};

#endif //  REG_MATRIX_H