#ifndef BST_H
#define BST_H
#include <iostream>
using namespace std;
template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
	Comparable element;
	BinaryNode* left;
	BinaryNode* right;

	BinaryNode(const Comparable& theElement,
		BinaryNode* lt, BinaryNode* rt)
		: element(theElement), left(lt), right(rt) { }

	friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
public:
	explicit BinarySearchTree(const Comparable& notFound);
	BinarySearchTree(const BinarySearchTree& rhs);
	~BinarySearchTree();

	const Comparable& findMin() const;
	const Comparable& findMax() const;
	const Comparable& find(Comparable& x) const;
	bool isEmpty() const;
	void printTreeInorder() const;
	void printTreePreorder() const;
	void drawTree() const;
	void getHeight();
	void makeEmpty();
	void insert(Comparable& x);
	void remove(Comparable& x);

	bool AVL() { // to check if it is avl or not
		return AVL(root);
	}

	bool AVL(BinaryNode<Comparable>* n) {
		int lh;
		int rh;
		if (n == NULL)
			return 1;
		lh = getHeight(n->left); // left height
		rh = getHeight(n->right); // right height
		if (abs(lh - rh) <= 1 && AVL(n->left) && AVL(n->right)) return 1;
		return 0;
	}

	const BinarySearchTree& operator=(const BinarySearchTree& rhs);
private:
	// compute height of the tree
	int getHeight(BinaryNode<Comparable>* t) {
		if (t == NULL)
			return 0;

		// find the height of each subtree
		int lh = getHeight(t->left);
		int rh = getHeight(t->right);

		return 1 + ((lh > rh) ? lh : rh);
	}
	BinaryNode<Comparable>* root;
	const Comparable ITEM_NOT_FOUND;

	const Comparable& elementAt(BinaryNode<Comparable>* t) const;
	void drawTree(ostream& os, const string& prefix, const BinaryNode<Comparable>* node, bool isLeft) const;
	void insert(Comparable& x, BinaryNode<Comparable>*& t) const;
	void remove(Comparable& x, BinaryNode<Comparable>*& t) const;
	BinaryNode<Comparable>* findMin(BinaryNode<Comparable>* t) const;
	BinaryNode<Comparable>* findMax(BinaryNode<Comparable>* t) const;
	BinaryNode<Comparable>* find(Comparable& x, BinaryNode<Comparable>* t) const;
	void makeEmpty(BinaryNode<Comparable>*& t) const;
	void printTreeInorder(ostream& out, BinaryNode<Comparable>* t) const;
	void printTreePreorder(ostream& out, BinaryNode<Comparable>* t) const;
	BinaryNode<Comparable>* clone() const;
	void cloneHelper(BinaryNode<Comparable>* source, BinaryNode<Comparable>*& destination) const;
};

#endif