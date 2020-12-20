#include "BinarySearchTree.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
  * Construct the tree.
  */
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable& notFound) : ITEM_NOT_FOUND(notFound), root(NULL) {}

/**
  * Internal method to get element field in node t.
  * Return the element field or ITEM_NOT_FOUND if t is NULL.
  */
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::elementAt(BinaryNode<Comparable>* t) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
  * Find item x in the tree.
  * Return the matching item or ITEM_NOT_FOUND if not found.
  */
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::find(Comparable& x) const
{
	return elementAt(find(x, root));
}

template<class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
	return root == NULL ? true : false;
}

/**
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */
template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::find(Comparable& x, BinaryNode<Comparable>* t) const
{
	if (t == NULL)
		return NULL;
	else if (x < t->element)
		return find(x, t->left);
	else if (t->element < x)
		return find(x, t->right);
	else
		return t;    // Match
}

/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::findMin() const
{
	return elementAt(findMin(root));
}

/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable>* t)
const
{
	if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;
	return findMin(t->left);
}

/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
template <class Comparable>
const Comparable& BinarySearchTree<Comparable>::findMax() const
{
	return elementAt(findMax(root));
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <class Comparable>
BinaryNode<Comparable>* BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable>* t) const
{
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;
	return t;
}

/**
  * Insert x into the tree; duplicates are ignored.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::insert( Comparable& x)
{
	insert(x, root);
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Comparable>
void BinarySearchTree<Comparable>::insert( Comparable& x, BinaryNode<Comparable>*& t) const
{
	if (t == NULL) //  create a new node at the right place
		t = new BinaryNode<Comparable>(x, NULL, NULL);
	else if (x < t->element)
		insert(x, t->left);  // insert at the left or 
	else if (t->element < x)
		insert(x, t->right);  // right subtree
	else
		;  // Duplicate; do nothing
}

/**
  * Remove x from the tree. Nothing is done if x is not found.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::remove(Comparable& x)
{
	remove(x, root);
}

template<class Comparable>
const BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree& rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		root = rhs.clone();
	}
	return *this;
}

/**
		 * Internal method to remove from a subtree.
		 * x is the item to remove.
		 * t is the node that roots the tree.
		 * Set the new root.
		 */
template <class Comparable>
void BinarySearchTree<Comparable>::remove(Comparable& x, BinaryNode<Comparable>*& t) const
{
	if (t == NULL)
		return;   // Item not found; do nothing
	if (x < t->element)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	else if (t->left != NULL && t->right != NULL) // Two children
	{
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else // one or no children
	{
		BinaryNode<Comparable>* oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
}

/**
  * Make the tree logically empty.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
	makeEmpty(root);
}

/**
  * Internal method to make subtree empty.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable>*& t) const
{
	if (t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}

template<class Comparable> // private
BinaryNode<Comparable>* BinarySearchTree<Comparable>::clone() const
{
	if (root == nullptr)  //if tree is empty
		return nullptr;   //clone becomes empty

	BinaryNode<Comparable>* headClone = new BinaryNode<Comparable>(root->element, NULL, NULL);
	BinaryNode<Comparable>* dest = headClone;
	BinaryNode<Comparable>* src = root;
	if (root) // if root is not nullpointer
		cloneHelper(src, dest);

	return headClone;
}

template<class Comparable> // private
void BinarySearchTree<Comparable>::cloneHelper(BinaryNode<Comparable>* source, BinaryNode<Comparable>*& destination) const {

	destination->element = source->element;

	if (source->right)
	{
		destination->right = new BinaryNode<Comparable>(source->element, NULL, NULL);
		cloneHelper(source->right, destination->right);
	}
	if (source->left)
	{
		destination->left = new BinaryNode<Comparable>(source->element, NULL, NULL);
		cloneHelper(source->left, destination->left);
	}
}

/**
  * Print the tree contents inorder.
  */
template <class Comparable>
void BinarySearchTree<Comparable>::printTreeInorder() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else {
		ofstream os;
		os.open("phonebookInOrderBST.txt");
		printTreeInorder(os, root);
		os.close();
	}
}

template <class Comparable>
void BinarySearchTree<Comparable>::printTreePreorder() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else {
		ofstream os;
		os.open("phonebookPreOrderBST.txt");
		printTreePreorder(os, root);
		os.close();
	}
}

template<class Comparable>
void BinarySearchTree<Comparable>::printTreeInorder(ostream& out, BinaryNode<Comparable>* t) const// private
{
	if (t == NULL) return;
	printTreeInorder(out, t->left);
	out << t->element << endl;
	printTreeInorder(out, t->right);
}

template<class Comparable>
void BinarySearchTree<Comparable>::printTreePreorder(ostream& out, BinaryNode<Comparable>* t) const // private
{
	if (t == NULL) return;
	out << t->element << endl;
	printTreePreorder(out, t->left);
	printTreePreorder(out, t->right);
}

template<class Comparable>
void BinarySearchTree<Comparable>::drawTree() const
{
	ofstream os;
	os.open("phonebookTreeBST.txt");
	drawTree(os, "", root, false);
	os.close();
}

template<class Comparable>
void BinarySearchTree<Comparable>::drawTree(ostream& os, const string& prefix, const BinaryNode<Comparable>* node, bool isLeft) const
{
	if (node != nullptr)
	{
		os << prefix;

		os << (isLeft ? "|---" : "|___");

		// print the value of the node
		os << node->element.fullName << endl;

		// enter the next tree level - left and right branch
		drawTree(os, prefix + (isLeft ? "|   " : "    "), node->left, true);
		drawTree(os, prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}

/**
  * Destructor for the tree.
  */
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
	makeEmpty();
}

/**
  * Copy constructor.
  */
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree<Comparable>& rhs) : root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
	*this = rhs;
}

template <class Comparable>
void BinarySearchTree<Comparable>::getHeight() {
	cout << "The heights of BST are for left: " << getHeight(root->left) << " and right: " << getHeight(root->right) << endl;
}