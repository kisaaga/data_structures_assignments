
#ifndef LinkedList_H

#define LinkedList_H

#include "dsexceptions.h"
#include <iostream>    
using namespace std;
struct Product {
	int count;
	string name;
	double s_value;

	bool operator == (const Product& rhs) {
		return this->name == rhs.name;
	}
	bool operator != (const Product& rhs) {
		return this->name != rhs.name;
	}
};


template <class Object>
class List;     

template <class Object>
class ListItr;     

template <class Object>
class ListNode
{
	ListNode(const Object& theElement = Object(), ListNode* n = NULL)
		: element(theElement), next(n) { }

	Object   element;
	ListNode* next;

	friend class List<Object>;
	friend class ListItr<Object>;
};


template <class Object>
class List
{
public:
	List();
	List(const List& rhs);
	~List();

	bool isEmpty() const;
	void makeEmpty();
	ListItr<Object> zeroth() const;
	ListItr<Object> first() const;
	void insert(const Object& x, const ListItr<Object>& p);
	ListItr<Object> find(const Object& x) const;
	ListItr<Object> findPrevious(const Object& x) const;
	void remove(const Object& x);

	const List& operator=(const List& rhs);

private:
	ListNode<Object>* header;
};



template <class Object>
class ListItr
{
public:
	ListItr() : current(NULL) { }
	bool isPastEnd() const
	{
		return current == NULL;
	}
	void advance()
	{
		if (!isPastEnd()) current = current->next;
	}
	Object& retrieve() const
	{
		if (isPastEnd()) throw BadIterator();
		return current->element;
	}

private:
	ListNode<Object>* current;    // Current position

	ListItr(ListNode<Object>* theNode)
		: current(theNode) { }

	friend class List<Object>; 
};

//#include "LinkedList.cpp"
#endif
