/**
 * This file is a header file for MyLinkedList class.
 * This class represents an implementation to a linked list,
 * each instance created is a linked list.
 */

#ifndef __MYLINKEDLIST_H__
#define __MYLINKEDLIST_H__

#include <string>

class MyLinkedListNode;

/**
 * This class is an implementation of linked list.
 */
class MyLinkedList
{

public:
	/**
	 * class default constructor that initializes empty list.
	 */
	MyLinkedList();

	/**
	 * class constructor that initializes list with a single node.
	 */
	MyLinkedList(const std::string& key, double data);

	/**
	 * class copy constructor.
	 */
	MyLinkedList(const MyLinkedList& l);

	/**
	 * class copy destructor.
	 */
	~MyLinkedList();

	/**
	 * an assignment operator.
	 */
	MyLinkedList& operator=(const MyLinkedList& other);

   /**
	* Minus set-like operation (set contains keys). The lists must not have
	* duplicate keys.
	*/
	MyLinkedList operator-(const MyLinkedList&  other) const;

	/**
	 * returns the intersection (by key) between two lists. The lists must
	 * not have duplicate keys.
	 */
	MyLinkedList operator&(const MyLinkedList&  other) const;

	/**
	 * returns the union (by key) of two lists. The lists must not have
	 * duplicate keys.
	 */
	MyLinkedList operator|(const MyLinkedList&  other) const;

	/**
	 * adds pair of <string,double> to a list.
	 */
	void add(const std::string& key, double data);

	/**
	 * adds pair of <string,double> to a list,
	 * if the key already in the list updates the list with data.
	 * return true if a new node was added.
	 */
	bool addUnique(const std::string& key, double data);

	/**
	 * removes all nodes with key = key in a list.
	 * returns the number of removed nodes.
	 */
	int remove(const std::string& key);

	/**
	 * Whether there is a node in a list with the given key,
	 * if so updates data with the nodes's data.
	 */
	bool isInList(const std::string& key, double& data) const;
	/**
	 * prints a list.
	 */
	void printList() const;

	/**
	 * sums up all nodes' data.
	 */
	double sumList() const;

	/**
	 * Whether two lists intersect.
	 */
	bool isIntersect(const MyLinkedList& l) const;

	/**
	 * returns a size of a list.
	 */
	int size();

private:

	MyLinkedListNode *_pHead;
	MyLinkedListNode *_pTail;
	int _size;

	enum Operation
	{
		MINUS,
		UNION,
		INTERSECTION
	};

	bool _updateList(const std::string& key, double data);
	MyLinkedListNode* _findInList(const std::string& key) const;
	void _remove(MyLinkedListNode ** pNode);
	bool _isEmpty() const;
	void _releaseList();
	void _init(MyLinkedListNode *pNode = NULL);
	void _copy(const MyLinkedList &l);
	MyLinkedList _operatorChoice(const MyLinkedList& other, Operation op) const;
};

#endif // __MYLINKEDLIST_H__
