/**
 * This file contains a implementation to matrix,
 * This implementation switches between two different matrix representation.
 * (Sparse and Reg) this class decides the better representation to work with
 * according to a matrix's data.
 */
#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include "Matrix.h"
#include <string>
#include <ostream>
#include <vector>

/**
 * This class switches between two different matrix representation.
 * (Sparse and Reg) this class decides the better representation to work with
 * according to a matrix's data, using strategy pattern.
 */
class MyMatrix
{
public:
	/** 
	 * a class copy constructor.
	 */
	MyMatrix(const MyMatrix &other);

	/** 
	 * a class constructor, matrix's data is received by a string.
	 */
	MyMatrix(std::string& matrix_str);

	/** 
	 * a class constructor matrix's data is received by an array and size.
	 */
	MyMatrix(double arr[], unsigned int col_size, unsigned int row_size);

	/** 
	 * calculates a matrix's trace.
	 */
	virtual double trace() const;

	/** 
	 * calculates a matrix's frobenius norm.
	 */
	virtual double frobeniusNorm() const;

	/** 
	 * a class destructor.
	 */
	virtual ~MyMatrix();

	/** 
	 * an assignment operator.
	 */
	virtual MyMatrix& operator=(const MyMatrix& other);

	/** 
	 * minus operator.
	 */
	virtual MyMatrix operator-(const MyMatrix&  other) const;

	/** 
	 * plus operator.
	 */
	virtual MyMatrix operator+(const MyMatrix&  other) const;

	/** 
	 * multiply operator.
	 */
	virtual MyMatrix operator*(const MyMatrix&  other) const;

	/** 
	 * += operator.
	 */
	virtual MyMatrix& operator+=(const MyMatrix& other);

	/** 
	 * -= operator.
	 */
	virtual MyMatrix& operator-=(const MyMatrix& other);

	/** 
	 * *= operator
	 */
	virtual MyMatrix& operator*=(const MyMatrix& other);

	/** 
	 * equals operator.
	 */
	virtual bool operator==(const MyMatrix& other) const;

	/** 
	 * not equals operator.
	 */
	virtual bool operator!=(const MyMatrix& other) const;

	/** 
	 *  unary minus operator.
	 */
	virtual MyMatrix operator-() const;

	/** 
	 * << operator.
	 */
	virtual std::ostream& operator<<(std::ostream& os) const;
	
	/**
	 *
	 */
	virtual Matrix::Type getType() const;

private:
	MatrixPointer _pMatrix;

	/** 
	 * array is received in constructor ordered by cols,
	 * This returns a flipped one (by rows).
	 */
	std::vector<double> _flipArray(const double arr[], 
								   unsigned int col_size, 
								   unsigned int row_size) const;

	/** 
	 * chooses the right representation and creates a matrix by a string.
	 */
	void _strategy(const std::string& matrix_str);

	/** 
	 * chooses the right representation and creates a matrix by an array.
	 */
	void _strategy(const double arr[], unsigned int col_size, unsigned int row_size);

	/** 
	 * decides what representation is better.
	 */
	Matrix::Type _decideRepresintation(const MatrixPointer &matrix) const;

	/** 
	 * by creates a suitable matrix by decision or directly and assigns pOriginal.
	 */
	void _copyMatrix(const MatrixPointer &pOriginal, bool decideRepresentation);

	/** 
	 * a class copy constructor by pointer.
	 * decides better representation.
	 */
	MyMatrix(const MatrixPointer &_pMatrix);
	
	/** 
	 * a class copy constructor by pointer.
	 * decides better representation if decideRepresentation is true.
	 */
	MyMatrix(const MatrixPointer &_pMatrix, bool decideRepresentation);
};

#endif
