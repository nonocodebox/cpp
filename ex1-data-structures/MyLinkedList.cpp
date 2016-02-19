/**
 * This file contains the implementations of MyLinkedList methods.
 */
#include "MyLinkedList.h"
#include <iostream>

using namespace std;

/**
 * This class represents a node in a list.
 */
class MyLinkedListNode
{
public:

	/**
	 * class constructor each node contains string and double.
	 */
	MyLinkedListNode(const string& key, double data);

	/**
	 * a node's key getter.
	 */
	string getKey();

	/**
	 * a node's data getter.
	 */
	double getData();

	/**
	 * a node's data setter.
	 */
	void setData(double data);

	/**
	 * a node's next getter.
	 */
	MyLinkedListNode* getNext();

	/**
	 * a node's previous getter.
	 */
	MyLinkedListNode* getPrev();

	/**
	 * a node's next setter.
	 */
	void setNext(MyLinkedListNode *next);

	/**
	 * a node's previous setter.
	 */
	void setPrev(MyLinkedListNode *prev);

private:
	string _key;
	double _data;
	MyLinkedListNode * _pNext;
	MyLinkedListNode * _pPrev;
};

/**
 * Class constructor
 */
MyLinkedListNode::MyLinkedListNode(const string& key, double data)
: _key(key), _data(data), _pNext(NULL), _pPrev(NULL)
{
}

/**
 * see explanation in where declared.
 */
string MyLinkedListNode::getKey()
{
	return _key;
}


/**
 * see explanation in where declared.
 */
double MyLinkedListNode::getData()
{
	return _data;
}


/**
 * see explanation in where declared.
 */
void MyLinkedListNode::setData(double data)
{
	_data = data;
}


/**
 * see explanation in where declared.
 */
MyLinkedListNode* MyLinkedListNode::getNext()
{
	return _pNext;
}


/**
 * see explanation in where declared.
 */
MyLinkedListNode* MyLinkedListNode::getPrev()
{
	return _pPrev;
}

/**
 * see explanation in where declared.
 */
void MyLinkedListNode::setNext(MyLinkedListNode *next)
{
	_pNext = next;
}

/**
 * see explanation in where declared.
 */
void MyLinkedListNode::setPrev(MyLinkedListNode *prev)
{
	_pPrev = prev;
}

/**
 * see explanation in header file.
 */
int MyLinkedList::size()
{
	return _size;
}
/**
 * This method releases a list
 * by deleting each node that was allocated on the heap.
 * pNext is used in order to accsess pCurrent's next after deleted.
 */
void MyLinkedList::_releaseList()
{
	MyLinkedListNode *pNext;
	for (MyLinkedListNode *pCurrent = _pHead; pCurrent != NULL; )
	{
		pNext = pCurrent->getNext();
		delete pCurrent;
		pCurrent = pNext;
	}
	_pHead = _pTail = NULL;
	_size = 0;
}

/**
 * This method releases a node,
 * please see the explanations for each
 * case handled inside the method.
 */
void MyLinkedList::_remove(MyLinkedListNode ** ppNode)
{
	_size--;

	/* Empty list or delete null */
	MyLinkedListNode * pNode = *ppNode;
	if (_pHead == NULL || pNode == NULL)
	{
		return;
	}

	/* Last Node in the list (single head) */
	if (pNode->getPrev() == NULL && pNode->getNext() == NULL)
	{
		delete pNode;
		*ppNode = NULL;
		_pHead = NULL;
		_pTail = NULL;
		return;
	}

	/* Remove head : pNode->m_pPrev == NULL && pNode->m_pNext != NULL */
	if (_pHead == pNode)
	{
		MyLinkedListNode *pTemp = _pHead;
		_pHead = _pHead->getNext();
		_pHead->setPrev(NULL);
		delete pTemp;
		*ppNode = NULL;
		return;
	}

	/* Remove tail: pNode->m_pPrev != NULL && pNode->m_pNext == NULL*/
	if (pNode == _pTail)
	{
		MyLinkedListNode *pTemp = _pTail;
		_pTail = _pTail->getPrev();
		_pTail->setNext(NULL);
		delete pTemp;
		*ppNode = NULL;
		return;
	}

	/* node has two neighbors */
	pNode->getPrev()->setNext(pNode->getNext());
	pNode->getNext()->setPrev(pNode->getPrev());
	delete pNode;
	*ppNode = NULL;
}

/**
 * when head is null we threat a list as empty.
 */
bool MyLinkedList::_isEmpty() const
{
	return (_pHead == NULL);
}

/**
 * Initializes list with head null.
 */
void MyLinkedList::_init(MyLinkedListNode *pNode)
{
	_pHead = _pTail = pNode;
	_size = (pNode != NULL) ? 1 : 0;
}

/**
 * if l is empty, no need to copy
 * else add each node's values one by one.
 */
void MyLinkedList::_copy(const MyLinkedList &l)
{
	_init();

	if (l._isEmpty())
	{
		return;
	}

	for (MyLinkedListNode *pCurrent = l._pHead; pCurrent != NULL ;
			pCurrent = pCurrent->getNext())
	{
		add(pCurrent->getKey(), pCurrent->getData());
	}
}

/**
 * This method acts acordingly by the chosen operation op:
 *  MINUS: start with coping this (left) and remove each node in other that has
 *  same key as this.
 *
 *  UNION: start with coping this (left) and add
 *  each node in other that a different key than this.
 *
 *  INTERSECTION: start with an empty list adding each node
 *  that has same key as this, with this's data.
 *
 *  NOTE: The input lists (this instance and other) should not have duplicate
 *  keys, otherwise the output is undefined.
 *
 */
MyLinkedList MyLinkedList::_operatorChoice(const MyLinkedList& other,
										   Operation op) const
{
	MyLinkedList result;
	if(op != INTERSECTION)
	{
		result = *this; // O(m)
	}

	for (MyLinkedListNode *pCurrent = other._pHead; pCurrent != NULL ;
			pCurrent = pCurrent->getNext())
	{
		MyLinkedListNode * pFound = _findInList(pCurrent->getKey());
		if (pFound == NULL)
		{
			if(op == UNION) // union operation is O(m*(m+n))
			{
				result.add(pCurrent->getKey(), pCurrent->getData()); // O(1)
			}

			continue;
		}

		if (op == MINUS) // minus operation is O(m*(m + n))
		{
			result.remove(pFound->getKey());
		}
		else if (op == INTERSECTION) // and operation is O(m*(m + n))
		{
			result.add(pFound->getKey(), pFound->getData());
		}
	}

	return result; // copy ctor
}

/**
 * initializes a list with a new node.
 */
MyLinkedList::MyLinkedList(const string &key, double data)
{
	_init(new MyLinkedListNode(key, data));
}

/**
 * see _init().
 */
MyLinkedList::MyLinkedList()
{
	_init();
}

/**
 * see _releaseList().
 */
MyLinkedList::~MyLinkedList()
{
	_releaseList();
}

/**
 * Copy constructor. see _copy().
 */
MyLinkedList::MyLinkedList(const MyLinkedList& l)
{
	_copy(l);
}

/**
 * if list is empty pLast is the first element.
 * else set tail's next to be pLast,
 * pLast is tail.
 */
void MyLinkedList::add(const string& key, double data)
{
	_size++;
	MyLinkedListNode *pLast = new MyLinkedListNode(key, data);
	if (_isEmpty())
	{
		_pHead = pLast;
		_pTail = _pHead;
		return;
	}

	_pTail->setNext(pLast);
	pLast->setPrev(_pTail);
	_pTail = pLast;
}

/**
 * if there was no update, add a new node.
 * see _updateList()
 */
bool MyLinkedList::addUnique(const string& key, double data)
{
	if (!_updateList(key, data))
	{
		add(key, data);
		return true; // New node added.
	}

	return false;
}

/**
 * look for nodes with the same key, using _remove(&node),
 * update counter.
 * pKeeper is used in order to access pCurrent's next
 * after deleted.
 *
 * O(n + m)
 */
int MyLinkedList::remove(const string& key)
{
	int removed = 0;
	for (MyLinkedListNode *pCurrent = _pHead; pCurrent != NULL; )
	{
		MyLinkedListNode *pKeeper = pCurrent->getNext();
		if (pCurrent->getKey() == key) // O(n), n size of string
		{
			_remove(&pCurrent); // O(1)
			removed++;
		}
		pCurrent = pKeeper;
	}

	return removed;
}

/**
 * Checks each node's key in list, if a node with the requested key is found
 * return its address.
 *
 * O(m +n) n is key size, m is list size
 */
MyLinkedListNode* MyLinkedList::_findInList(const string& key) const
{
	for (MyLinkedListNode *pCurrent = _pHead; pCurrent != NULL;
			pCurrent = pCurrent->getNext())
	{
		if (pCurrent->getKey() == key)
		{
			return pCurrent;
		}
	}
	return NULL;
}

/**
 * if there is a node with the same key update its data
 * to the parameter's data.
 */
bool MyLinkedList::_updateList(const string& key, double data)
{
	bool isIn = false;
	MyLinkedListNode* pFound = _findInList(key);

	if (pFound != NULL)
	{
		isIn = true;
		pFound->setData(data);
	}
	
	return isIn;
}

/**
 * looks for a node it the list that has the same key,
 * if found, change data and return true.
 * see _findInList()
 *
 * O(m+n)
 */
bool MyLinkedList::isInList(const string& key, double& data) const
{
	bool isIn = false;
	MyLinkedListNode* pFound = _findInList(key); // O(m+n)

	if (pFound != NULL)
	{
		isIn = true;
		data = pFound->getData();
	}
	
	return isIn;
}

/**
 * see explanation in header file.
 */
void MyLinkedList::printList() const
{
	if (_isEmpty())
	{
		cout << "Empty" << endl;
		return;
	}

	for (MyLinkedListNode *pCurrent = _pHead; pCurrent != NULL;
			pCurrent = pCurrent->getNext())
	{
		cout << pCurrent->getKey() << "," << pCurrent->getData() << endl;
	}
}

/**
 * see explanation in header file.
 */
double MyLinkedList::sumList() const
{
	double sum = 0.0;
	for (MyLinkedListNode *pCurrent = _pHead; pCurrent != NULL ;
			pCurrent = pCurrent->getNext())
	{
		sum += pCurrent->getData();
	}

	return sum;
}

/**
 * checks intersection by checking every combination of key pair
 * see _findInList()
 *
 * O(m*(m+n))
 */
bool MyLinkedList::isIntersect(const MyLinkedList& l) const
{
	MyLinkedListNode* pFound;
	for (MyLinkedListNode *pCurrentL = l._pHead; pCurrentL != NULL;
			pCurrentL = pCurrentL->getNext())
	{
		pFound = _findInList(pCurrentL->getKey()); // O(m +n)
		if (pFound != NULL)
		{
			return true;
		}
	}

	return false;
}

/**
 * if self = self return this, no need to copy.
 * else release old  left list and copy other's values.
 * see _copy() and _releaseList()
 *
 * O(m)
 */
MyLinkedList& MyLinkedList::operator=(const MyLinkedList& other)
{
	if (this == &other)
	{
		return *this;
	}

	_releaseList(); // O(m)
	_copy(other); // O(m)
	return *this;
}

/**
 * see explanation in header file and _operatorChoice.
 */
MyLinkedList MyLinkedList::operator-(const MyLinkedList&  other) const
{
	return _operatorChoice(other, MINUS);
}

/**
 * see explanation in header file and _operatorChoice.
 */
MyLinkedList MyLinkedList::operator&(const MyLinkedList&  other) const
{
	return _operatorChoice(other, INTERSECTION);
}

/**
 * see explanation in header file and _operatorChoice.
 */
MyLinkedList MyLinkedList::operator|(const MyLinkedList&  other) const
{
	return _operatorChoice(other, UNION);
}


