#include "stack.h"
#include <iostream>

using namespace std;

template <class Object>
Stack<Object>::Stack()
{
	topOfStack = NULL;
}

template <class Object>
bool Stack<Object>::isFull() const
{
	return false;
}

template <class Object>
bool Stack<Object>::isEmpty() const
{
	if (topOfStack == nullptr)
	{
		return true;
	}
	else
		return false;
}

template <class Object>
const Object & Stack<Object>::top() const
{
	/*if (isEmpty())
	{
		cout << "Stack is empty!" << endl;
	}
	return topOfStack->element;*/
	if (topOfStack != nullptr)
	{
		return topOfStack->element;
	}
	else
	{
		cout << "Stack is empty!" << endl;
	}
}

template <class Object>
void Stack<Object>::pop()
{
	if ( isEmpty())
		cout << "Stack is empty!" << endl;
	ListNode *oldTop = topOfStack;
	topOfStack = topOfStack->next;
	delete oldTop;
}

template <class Object>
void Stack<Object>::push( const Object & x )
{
	topOfStack = new ListNode( x, topOfStack );
}

template <class Object>
Object Stack<Object>::topAndPop()
{
	Object topItem= top();
	pop();
	return topItem;
}

template <class Object>
void Stack<Object>::makeEmpty( )
{
	while (!isEmpty())
		pop( );
}
//Deep copy
template <class Object>
const Stack<Object> & Stack<Object>::operator=( const Stack<Object> & rhs )
{
	if ( this != &rhs )
	{
		makeEmpty( );
		if ( rhs.isEmpty())
			return *this;
		ListNode *rptr = rhs.topOfStack;
		ListNode *ptr = new ListNode( rptr->element );
		topOfStack = ptr;
		for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
			ptr = ptr->next = new ListNode( rptr->element );
	}
	return *this;
}

//Copy constructor
template <class Object>
Stack<Object>::Stack( const Stack<Object> & rhs )
{
	topOfStack = NULL;
	*this = rhs;
}

//Destructor
template <class Object>
Stack<Object>::~Stack( )
{
	makeEmpty( );
}