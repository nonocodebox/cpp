/**
 * This file contains a "generic" implementation to matrix,
 * Sparse and Reg are to be operated using Matrix.h's functions
 * due to polymorphism.
 */

#ifndef MATRIX_H
#define MATRIX_H

#ifndef EPSILON_CONST
#define EPSILON_CONST (1e-6)
#endif

#include <utility>
#include <memory>
#include <ostream>
#include "Map.h"

class Matrix;

typedef std::pair<Pair, double> MatrixElement;
typedef std::auto_ptr<Matrix> MatrixPointer;

/**
 * an abstract class of matrix.
 */
class Matrix
{
public:
	/**
	 * This class represents iterator to be implemented by Matrix's derives.
	 */
	class Iterator
	{
	public:
		/** 
		 * a class destructor, empty implementation.
		 */
		virtual ~Iterator() {}

		/** 
		 * dereference operator.
		 */
		virtual MatrixElement operator*() const = 0;

		/** 
		 * increment operator.
		 */
		virtual Iterator& operator++() = 0;

		/** 
		 * is container's end.
		 */
		virtual bool isEnd() const = 0;
	};
	

	/** 
	 * different types of derived matrices.
	 */
	enum Type
	{
		/** 
		 * Regular matrix.
		 */
		REG_MATRIX,

		/** 
		 * Sparse matrix.
		 */
		SPARSE_MATRIX
	};

	typedef std::auto_ptr<Iterator> IteratorPointer;

	/** 
	 * a class destructor.
	 */
	virtual ~Matrix() = 0;

	/** 
	 * create and allocate a new derived instance,
	 * with the size rows * cols.
	 */
	virtual MatrixPointer createNew(unsigned int rows, unsigned int cols) const = 0;

	/** 
	 * change value in matrix (row, col and value).
	 */
	virtual void setValue(unsigned int row, unsigned int col, double value) = 0;
	
	/** 
	 * create and allocate a new iterator of derived instance.
	 */
	virtual IteratorPointer createIterator() const = 0;
	
	/** 
	 * calculates a matrix's trace.
	 */
	virtual double trace() const;

	/** 
	 * calculates a matrix's frobenius norm.
	 */
	virtual double frobeniusNorm() const;

	/** 
	 * returns a matrix's transpose.
	 */
	virtual MatrixPointer transpose() const;

	/** 
	 * assign a matrix to current.
	 */
	virtual void assign(const Matrix& other);

	/** 
	 * adds a matrix to current.
	 */
	virtual MatrixPointer add(const Matrix&  other) const;

	/** 
	 * multiply a matrix with current.
	 */
	virtual MatrixPointer multiply(const Matrix&  other) const;

	/** 
	 * whether a matrix equals to current (by elements in matrix).
	 */
	virtual bool isEquals(const Matrix& other) const;

	/** 
	 * substrates a matrix from current.
	 */
	virtual MatrixPointer minus() const;

	/** 
	 * prints a matrix.
	 */
	virtual std::ostream& printMatrix(std::ostream& os) const;

	/** 
	 * returns a matrix's type
	 * see: Matrix::Type.
	 */
	virtual Type getType() const = 0;

	/** 
	 * returns a matrix's number of rows.
	 */
	virtual unsigned int getRows() const;

	/** 
	 * returns a matrix's number of columns.
	 */
	virtual unsigned int getColumns() const;

protected:
	unsigned int _rows;
	unsigned int _cols;

	/** 
	 * a class constrictor [used by the derives].
	 */
	Matrix(unsigned int rows, unsigned int cols);

	
	/** 
	 * resets a matrix with the size rows * cols.
	 */
	virtual void _resetMatrix(unsigned int rows, unsigned int cols) = 0;

	/** 
	 * whether a zero matrix.
	 */
	bool _isAllZero() const;
	
	/**
	 * print a double value with precision PRECISION.
	 */
	std::string _printDouble(double value) const;
};

#endif // MATRIX_H
