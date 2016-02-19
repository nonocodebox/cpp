/**
 * This file contains an implemntation for exception type of a bad input type.
 */

#include "ExceptionBadInput.h"
#define EMPTY_MSG "Bad input"

#include <string>

/**
 * a defult constractor.
 */
ExceptionBadInput::ExceptionBadInput() noexcept
: _msg(EMPTY_MSG)
{
}

/**
 * a class constractor.
 * error message input.
 */
ExceptionBadInput::ExceptionBadInput(const std::string & msg) noexcept
{
	_msg = msg;
}

/**
 * a class destractor.
 */
ExceptionBadInput::~ExceptionBadInput() noexcept
{
}

/**
 * returns an error message .
 */
const char * ExceptionBadInput::what() const noexcept
{
	return _msg.c_str();
}
