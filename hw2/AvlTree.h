#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
using namespace std;

template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
	Comparable 	element;
	AvlNode* left;
	AvlNode* right;
	int height;

	AvlNode(const Comparable& theElement, AvlNode* lt, AvlNode* rt, int h = 0) : element(theElement), left(lt), right(rt), height(h) {}

	friend class AvlTree<Comparable>;
};

template <class Comparable>
class AvlTree
{
public:
	AvlTree(const Comparable& notFound) : ITEM_NOT_FOUND(notFound), root(nullptr) {}
	AvlTree(const AvlTree& rhs);
	~AvlTree()
	{
		makeEmpty();
	}

	const Comparable& findMin() const;
	const Comparable& findMax() const;
	const Comparable& find(Comparable& x) const;
	bool isEmpty() const;
	void printTreeInorder() const;
	void printTreePreorder() const;
	void getHeight();

	void drawTree() const;
	void makeEmpty();
	void insert(Comparable& x);
	void remove(Comparable& x);

	const AvlTree& operator=(const AvlTree& rhs);

	bool AVL() { // to check if it is avl or not
		return AVL(root);
	}

	bool AVL(AvlNode<Comparable>* n) {
		int lh;
		int rh;
		if (n == NULL)
			return 1;
		lh = height(n->left); // left height
		rh = height(n->right); // right height
		if (abs(lh - rh) <= 1 && AVL(n->left) && AVL(n->right)) return 1;
		return 0;
	}

private:
	AvlNode<Comparable>* root;
	const Comparable ITEM_NOT_FOUND;

	const Comparable& elementAt(AvlNode<Comparable>* t) const;

	void drawTree(ostream& os, const string& prefix, const AvlNode<Comparable>* node, bool isLeft) const;
	void insert( Comparable& x, AvlNode<Comparable>*& t) const;
	void remove(Comparable& x, AvlNode<Comparable>*& t) const;

	AvlNode<Comparable>* findMin(AvlNode<Comparable>* t) const;
	AvlNode<Comparable>* findMax(AvlNode<Comparable>* t) const;
	AvlNode<Comparable>* find(Comparable& x, AvlNode<Comparable>* t) const;
	void makeEmpty(AvlNode<Comparable>*& t) const;
	void printTreeInorder(ostream& out, AvlNode<Comparable>* t) const;
	void printTreePreorder(ostream& out, AvlNode<Comparable>* t) const;
	AvlNode<Comparable>* clone() const;
	void cloneHelper(AvlNode<Comparable>* source, AvlNode<Comparable>*& destination) const;
	// Avl manipulations
	int height(AvlNode<Comparable>* t) const;
	int max(int lhs, int rhs) const;
	void rotateWithLeftChild(AvlNode<Comparable>*& k2) const;
	void rotateWithRightChild(AvlNode<Comparable>*& k1) const;
	void doubleWithLeftChild(AvlNode<Comparable>*& k3) const;
	void doubleWithRightChild(AvlNode<Comparable>*& k1) const;

	// Get Balance factor of node N  
	int getBalance(AvlNode<Comparable>* N) const
	{
		if (N == nullptr)
			return 0;
		return height(N->left) - height(N->right);
	}
};

#endif