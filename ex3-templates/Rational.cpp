/**
 * contains the implemtaion of a Rational class which represents
 * a ratioanl number - a ratio between two integers.
 */

#include "Rational.h"
#include "ExceptionBadInput.h"

#include <sstream>

#define INITALIZE_DENOMINATOR 1
#define DIVIDE_BY_ZERO "Ratinal: Devision by zero"
#define USAGE_BAD_INPUT_STR "Usage Rational: wrong input string"
#define SEPERATOR '/'

using namespace std;

/**
* Constructors geting int or default which is set to 0
*/
Rational::Rational(const long int &value)
	: _numerator(value), _denominator(INITALIZE_DENOMINATOR)
{
	_makeRepresentationCoprime();
}

/**
* Constructors geting numerator and denominator
*/
Rational::Rational(const long int &numerator, const long int &denominator)
{
	if (denominator == 0)
	{
		throw ExceptionBadInput(DIVIDE_BY_ZERO);
	}
	
	_numerator = numerator;
	_denominator = denominator;

	_makeRepresentationCoprime();
}

/**
* Constructors a Ratinal number by a given string: "numerator/denominator"
*/
Rational::Rational(const std::string &str)
{
	if (str.find(SEPERATOR) == string::npos)
	{
		throw ExceptionBadInput(USAGE_BAD_INPUT_STR);
	}
	
	try
	{
		istringstream iss(str);
		char seperator;
		iss >> _numerator;
		iss >> seperator;
		iss >> _denominator;
		
		if (_denominator == 0)
		{
			throw ExceptionBadInput(DIVIDE_BY_ZERO);
		}
		
		_makeRepresentationCoprime();
	}
	catch (ios_base::failure&)
	{
		throw ExceptionBadInput(USAGE_BAD_INPUT_STR);
	}
}

/**
 * Constructors copy constructor. 
 */
Rational::Rational(const Rational &other)
{
	// knowing other already called the ctor, so no need to check the values.
	_numerator = other._numerator;
	_denominator = other._denominator;
}

/**
* Constructors move constructor
*/
Rational::Rational(Rational && other)
	:_numerator(other._numerator), _denominator(other._denominator)
{
	// initialize other(clean)
	other._numerator = 0;
	other._denominator = INITALIZE_DENOMINATOR;
}

/**
* Assignment operator, use copy-and-swap idiom
*/
Rational& Rational::operator=(Rational other)
{
	std::swap(_numerator, other._numerator);
	std::swap(_denominator, other._denominator);
	return *this;
}

/**
* Returns the numerator
*/
const long int Rational::getNumerator() const
{
	return _numerator;
}

/**
* Returns the denominator
*/
const long int Rational::getDenominator() const
{
	return _denominator;
}

/**
* Summing two Rationals
* Addition should be calculated in the way we calculate addition of 2
* ratios (using their common denominator).
*/
const Rational Rational::operator+(const Rational &other) const
{
	Rational result;
	result._numerator = _numerator * other._denominator + other._numerator * _denominator;
	result._denominator = _denominator * other._denominator;
	result._makeRepresentationCoprime();

	return result;
}

/**
* Multiplying operator for Rational
* Multiplication should be calculated in the way we calculate
* multiplication of 2 ratios (separately for the numerator and for the
* denominator).
*/
const Rational Rational::operator*(const Rational &other) const
{
	Rational result;
	result._numerator = _numerator * other._numerator;
	result._denominator = _denominator * other._denominator;
	result._makeRepresentationCoprime();
	return result;
}

/**
* operator<< for stream insertion
* The format is numerator/denominator w/o spaces or addional characters
*
* recives an osteam and the rational number to be printed to it.
*/
std::ostream& operator<<(std::ostream &os, const Rational &number)
{
	return os << number._numerator << SEPERATOR << number._denominator;
}

/**
 * fix a zero rational number so the denominator = 0.
 */
void Rational::_fixZero()
{
	if (_numerator == 0)
	{
		_denominator = INITALIZE_DENOMINATOR;
	}
}

/**
 * fix a negative rational number so the numerator < 0 and the denominator > 0.
 */
void Rational::_fixNegativity()
{
	if ((_numerator < 0 && _denominator < 0) || 
		(_numerator > 0 && _denominator < 0))
	{
		_numerator = -_numerator;
		_denominator = -_denominator;
	}
}

/**
 * normalize the number: if the mone and the mehane are not metzomzamim, then zamzem.
 * also fix zeros and negativity.
 */
void Rational::_makeRepresentationCoprime()
{
	_fixZero();
	_fixNegativity();
	
	if (_numerator == 0)
	{
		return;
	}

	long int gcd = _greatestCommonDivisor(abs(_numerator), _denominator);
	
	_numerator /= gcd;
	_denominator /= gcd;

}

/**
 * GCD algorith.
 * recives two numbers and finds thier GCD.
 */
const long int Rational::_greatestCommonDivisor(const long int &a, const long int &b)
{
	long int a1 = a, b1 = b;

	while (a1 != b1)
	{
		if (a1 > b1)
		{
			a1 = a1 - b1;
		}
		else
		{
			b1 = b1 - a1;
		}
	}

	return a1;
}
