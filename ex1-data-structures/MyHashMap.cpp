/**
 * This file contains the implementations of MyHashMap methods.
 */

#include "MyHashMap.h"

using namespace std;

/**
 * sums each key's char.
 * n-char string is O(n)
 */
int MyHashMap::myHashFunction(const std::string &str)
{
	int hashedValue = 0;
	for (int i = 0; i < (int)str.size() ; i++)
	{
		hashedValue += str[i];
	}

	hashedValue %= HASH_SIZE;
	return hashedValue;
}

/**
 * Class constructor
 * O(1)
 */
MyHashMap::MyHashMap()
: _size(0)
{
}

/**
 * copies other's lists by their index.
 * using MyLinkedList's assignment operator.
 * used by calling ctor.
 *
 * m - size of biggest list:
 *
 * list = operator =>O(m)
 * O(m*HASH_SIZE)
 */
void MyHashMap::_copy(const MyHashMap& other)
{
	for (int i = 0; i < HASH_SIZE ; i++)
	{
		_hashT[i] = other._hashT[i];
	}

	_size = other._size;
}

/**
 * Copy constructor. see _copy()
 */
MyHashMap::MyHashMap(const MyHashMap& other)
: _size(other._size)
{
	_copy(other);
}

/**
 * Class destructor (default)
 * O(m*HASH_SIZE) - delete each list
 */
MyHashMap::~MyHashMap()
{
}

/**
 * adds to the right list (by index) using addUnique(),
 * increase size only if a new item was added.
 *
 * n - size of string
 * m - size of list no. index.
 *
 * addUnique - O(m +n)
 * O(n) + O (m + n) = O(n + m)
 */
void MyHashMap::add(const std::string &str, double data)
{
	int index = myHashFunction(str);
	if(_hashT[index].addUnique(str, data))
	{
		_size++;
	}
}

/**
 * removes a node from the right list (by index) using remove().
 * decrease size only if a new item was added.
 *
 * * n - size of string
 * m - size of list no. index.
 *
 * remove - O(m + n)
 * O(n) + O (m + n) = O(n + m)
 */
size_t MyHashMap::remove(const std::string &str)
{
	int index = myHashFunction(str);
	if (_hashT[index].remove(str) != 0) // O(m + n)
	{
		_size--; // only one is deleted, unique.
		return SUCCSES;
	}
	return FAILURE;
}

/**
 * checks whether str (as a key) in a hash map (by index) using isInList().
 *
 * n - size of string
 * m - size of list no. index.
 *
 * isInList - O(m + n)
 * O(n) + O (m + n) = O(n + m)
 */
bool MyHashMap::isInHashMap(const std::string &str, double &data) const
{
	int index = myHashFunction(str);
	return _hashT[index].isInList(str, data);
}

/**
 * Return number of elements stored in the HashMap
 *
 * O(1)
 */
int MyHashMap::size() const
{
	return _size;
}

/**
 * checks whether two hash maps intersects it uses isIntersect(),
 * because if there was a common key it would map to the same cell.
 *
 *  n - size of string
 * m - size of biggest list
 * isIntersect - O(m*(m+n))
 *
 * => O(m*(m+n)*HASH_SIZE)
 *
 */
bool MyHashMap::isIntersect(const MyHashMap &h1) const
{
	for (int i = 0; i < HASH_SIZE ; i++)
	{
		if(_hashT[i].isIntersect(h1._hashT[i]))
		{
			return true;
		}
	}
	return false;
}

/**
 * Return the total wight of the hash elements
 * sums each list in it.
 *
 * m - size of biggest list
 * =>  O(m*HASH_SIZE)
 */
double MyHashMap::totWeight() const
{
	double sumHash = 0.0;
	for (int i = 0; i < HASH_SIZE ; i++)
	{
		sumHash += _hashT[i].sumList(); // O(m)
	}

	return sumHash;
}

/**
 * see explanation in header file.
 *
 * m - size of biggest list
 *
 * O(m*HASH_SIZE) see totWeight()
 */
bool MyHashMap::operator<(const MyHashMap& other) const
{
	return (this->totWeight() < other.totWeight());
}

/**
 * see explanation in header file.
 *
 * m - size of biggest list
 *
 * O(m*HASH_SIZE) see totWeight()
 */
bool MyHashMap::operator>(const MyHashMap& other) const
{
	return (this->totWeight() > other.totWeight());
}

/**
 * see explanation in header file.
 * m - size of biggest list
 *
 * O(m*HASH_SIZE) see totWeight()
 */
bool MyHashMap::operator==(const MyHashMap& other) const
{
	return (this->totWeight() == other.totWeight());
}

/**
 * see explanation in header file.
 *
 * m - size of biggest list
 *
 * O(m*HASH_SIZE) => see operator==().
 */
bool MyHashMap::operator!=(const MyHashMap& other) const
{
	return !(*this == other);
}

/**
 * see explanation in header file and _operatorChoice().
 *
 *  m - size of biggest list
 *
 * list minus operation is O(m*(m + n))
 * => O(m*(m + n)*HASH_SIZE)
 */
MyHashMap MyHashMap::operator-(const MyHashMap&  other) const
{
	return _operatorChoice(other, MINUS);
}

/**
 * see explanation in header file and _operatorChoice().
 * m - size of biggest list
 *
 * list and operation is O(m*(m + n))
 * => O(m*(m + n)*HASH_SIZE)
 */
MyHashMap MyHashMap::operator&(const MyHashMap&  other) const
{
	return _operatorChoice(other, INTERSCTION);
}

/**
 * see explanation in header file and _operatorChoice().
 *
 * list union operation is O(m*(m + n))
 * => O(m*(m + n)*HASH_SIZE)
 */
MyHashMap MyHashMap::operator|(const MyHashMap&  other) const
{
	return _operatorChoice(other, UNION);
}

/**
 * copies other value's to the current instance.
 *
 * =>  O(m*HASH_SIZE) [_copy()]
 */
MyHashMap& MyHashMap::operator=(const MyHashMap& other)
{
	if (this == &other)
	{
		return *this;
	}

	_copy(other);

	return *this;
}

/**
 * using Operation in order to perform the right operation(&,-,|).
 *
 * O(HASH_SIZE* heaviest operation) = => O(m*(m + n)*HASH_SIZE)
 */
MyHashMap MyHashMap::_operatorChoice(const MyHashMap& other, Operation op) const
{
	MyHashMap result;
	for (int i = 0; i < HASH_SIZE ; i++)
	{
		if (op == MINUS)
		{
			result._hashT[i] = _hashT[i] - other._hashT[i];
		}
		else if(op == UNION)
		{
			result._hashT[i] = _hashT[i] | other._hashT[i];
		}
		else
		{
			result._hashT[i] = _hashT[i] & other._hashT[i];
		}

		result._size += result._hashT[i].size();
	}

	return result;
}

