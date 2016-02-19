/**
 * This file contains an implemntation for exception type of a bad size type.
 */
#include "ExceptionBadSize.h"
#define EMPTY_MSG "Bad size"

#include <string>

/**
 * a defult constractor.
 */
ExceptionBadSize::ExceptionBadSize() noexcept
: _msg(EMPTY_MSG)
{
}

/**
 * a class constractor.
 * error message input.
 */
ExceptionBadSize::ExceptionBadSize(const std::string & msg) noexcept
{
	_msg = msg;
}
 
/**
 * a class destractor.
 */
ExceptionBadSize::~ExceptionBadSize() noexcept
{
}

/**
 * returns an error message .
 */
const char * ExceptionBadSize::what() const noexcept
{
	return _msg.c_str();
}
