
#ifndef SEPARATE_CHAINING_H_
#define SEPARATE_CHAINING_H_

#include <vector>
#include <string>
#include "LinkedList.h"
using namespace std;


template <class HashedObj>
class HashTable
{
public:
	explicit HashTable(const HashedObj& notFound, int size = 101);
	HashTable(const HashTable& rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), theLists(rhs.theLists) { }

	const HashedObj& find(const HashedObj& x) const;

	void makeEmpty();
	void insert(const HashedObj& x);
	void remove(const HashedObj& x);
	vector<List<HashedObj>>& getLists() { return theLists; }

	const HashTable& operator=(const HashTable& rhs);
private:
	vector<List<HashedObj>> theLists;   // The array of Lists
	const HashedObj ITEM_NOT_FOUND;
};

int hhash(const string& key, int tableSize);
int hhash(int key, int tableSize);
int hhash(const Product& str, int tableSize);

//#include "HashTable.cpp"

#endif
