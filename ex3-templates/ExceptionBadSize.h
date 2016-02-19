/**
 * This file contains definions for exception type of a bad size type.
 */
#ifndef EXCEPT_BAD_SIZE_H
#define EXCEPT_BAD_SIZE_H

#include <exception>
#include <string>

/**
 * exception class of bad size type.
 */
class ExceptionBadSize : public std::exception
{
public:
	/**
	* a defult constractor.
	*/
	ExceptionBadSize() noexcept;
	/**
	 * a class constractor.
	 * error message input.
	 */
	ExceptionBadSize(const std::string & msg) noexcept;

	/**
	 * a class destractor.
	 */
	virtual ~ExceptionBadSize() noexcept;

	/**
	 * returns an error message .
	 */
	virtual const char * what() const noexcept;
  
private:
	std::string _msg;
};

#endif
