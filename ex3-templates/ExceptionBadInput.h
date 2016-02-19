/**
 * This file contains definitions for exception type of a bad input type.
 */
#ifndef EXCEPT_BAD_INPUT_H
#define EXCEPT_BAD_INPUT_H

#include <exception>
#include <string>

/**
 * exception calss of bad input type.
 */
class ExceptionBadInput : public std::exception
{
public:
	/**
	 * a defult constractor.
	 */
	ExceptionBadInput() noexcept;
	/**
	 * a class constractor.
	 * error message input.
	 */
	ExceptionBadInput(const std::string &msg) noexcept;

	/**
	 * a class destractor.
	 */
	virtual ~ExceptionBadInput() noexcept;

	/**
	 * returns an error message .
	 */
	virtual const char * what() const noexcept;

private:
	std::string _msg;
};

#endif
