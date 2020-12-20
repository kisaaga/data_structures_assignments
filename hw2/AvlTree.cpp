#include "AvlTree.h"
#include <iostream>
#include <string>

using namespace std;

/**
  * Construct the tree.
  */
//template <class Comparable>
//AvlTree<Comparable>::AvlTree(const Comparable& notFound) : ITEM_NOT_FOUND(notFound), root(NULL) {}

/**
  * Copy constructor.
  */
template <class Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree<Comparable>& rhs) : root(NULL), ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
	*this = rhs;
}

/**
  * Destructor for the tree.
  */
//template <class Comparable>
//AvlTree<Comparable>::~AvlTree()
//{
//	makeEmpty();
//}

/**
  * Find the smallest item in the tree.
  * Return smallest item or ITEM_NOT_FOUND if empty.
  */
template <class Comparable>
const Comparable& AvlTree<Comparable>::findMin() const
{
	return elementAt(findMin(root));
}

/**
 * Internal method to find the smallest item in a subtree t.
 * Return node containing the smallest item.
 */
template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMin(AvlNode<Comparable>* t)
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
const Comparable& AvlTree<Comparable>::findMax() const
{
	return elementAt(findMax(root));
}

/**
 * Internal method to find the largest item in a subtree t.
 * Return node containing the largest item.
 */
template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::findMax(AvlNode<Comparable>* t) const
{
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;
	return t;
}

/**
  * Find item x in the tree.
  * Return the matching item or ITEM_NOT_FOUND if not found.
  */
template <class Comparable>
const Comparable& AvlTree<Comparable>::find(Comparable& x) const
{
	return elementAt(find(x, root));
}

/**
 * Internal method to find an item in a subtree.
 * x is item to search for.
 * t is the node that roots the tree.
 * Return node containing the matched item.
 */
template <class Comparable>
AvlNode<Comparable>* AvlTree<Comparable>::find(Comparable& x, AvlNode<Comparable>* t) const
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
  * Make the tree logically empty.
  */
template <class Comparable>
void AvlTree<Comparable>::makeEmpty()
{
	makeEmpty(root);
}

/**
  * Internal method to make subtree empty.
  */
template <class Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode<Comparable>*& t) const
{
	if (t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}
template<class Comparable>
bool AvlTree<Comparable>::isEmpty() const
{
	return root == NULL ? true : false;
}

/**
		 * Return the height of node t, or -1, if NULL.
 */
template <class Comparable>
int AvlTree<Comparable>::height(AvlNode<Comparable>* t) const
{
	if (t == NULL)
		return -1;

	return t->height;
}

/**
		* Return maximum of lhs and rhs.
*/
template <class Comparable>
int AvlTree<Comparable>::max(int lhs, int rhs) const
{
	if (lhs > rhs)
		return lhs;

	return rhs;
}

/**
  * Internal method to get element field in node t.
  * Return the element field or ITEM_NOT_FOUND if t is NULL.
  */
template <class Comparable>
const Comparable& AvlTree<Comparable>::elementAt(AvlNode<Comparable>* t) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
  * Insert x into the tree; duplicates are ignored.
  */
template <class Comparable>
void AvlTree<Comparable>::insert( Comparable& x)
{
	insert(x, root);
}
template <class Comparable>
void AvlTree<Comparable>::insert( Comparable& x, AvlNode<Comparable>*& t) const
{
	if (t == NULL)
		t = new AvlNode<Comparable>(x, NULL, NULL);

	else if (x < t->element) {
		// X should be inserted to the left tree!
		insert(x, t->left);
		// Check if the left tree is out of balance (left subtree grew in height!)
		if (height(t->left) - height(t->right) == 2)
			if (x < t->left->element)  // X was inserted to the left-left subtree!
				rotateWithLeftChild(t);
			else			     // X was inserted to the left-right subtree!
				doubleWithLeftChild(t);
	}
	else if (t->element < x)
	{    // Otherwise X is inserted to the right subtree
		insert(x, t->right);
		if (height(t->right) - height(t->left) == 2)
			// height of the right subtree increased
			if (t->right->element < x)
				// X was inserted to right-right subtree
				rotateWithRightChild(t);
			else // X was inserted to right-left subtree
				doubleWithRightChild(t);
	}
	else
		;  // Duplicate; do nothing

// update the height the node
	t->height = max(height(t->left), height(t->right)) + 1;
}

/**
  * Remove x from the tree. Nothing is done if x is not found.
  */
template <class Comparable>
void AvlTree<Comparable>::remove(Comparable& x)
{
	remove(x, root);
}

template <class Comparable>
void AvlTree<Comparable>::remove( Comparable& x, AvlNode<Comparable>*& t) const
{

	// STEP 1: PERFORM STANDARD BST DELETE  
	if (t == NULL)
		return;

	// If the x to be deleted is smaller  
	// than the t's x, then it lies 
	// in left subtree  
	if (x < t->element)
		remove(x, t->left);

	// If the x to be deleted is greater  
	// than the t's x, then it lies  
	// in right subtree  
	else if (x > t->element)
		remove(x, t->right);

	// if x is same as t's x, then  
	// This is the node to be deleted  
	else
	{
		// node with only one child or no child  
		if ((t->left == NULL) ||
			(t->right == NULL))
		{
			AvlNode<Comparable>* temp = t->left ?
				t->left :
				t->right;

			// No child case  
			if (temp == NULL)
			{
				temp = t;
				t = NULL;
			}
			else // One child case  
				*t = *temp; // Copy the contents of  
							   // the non-empty child  
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder  
			// successor (smallest in the right subtree)  
			AvlNode<Comparable>* temp = findMin(t->right);

			// Copy the inorder successor's  
			// data to this node  
			t->element = temp->element;

			// Delete the inorder successor  
			remove(temp->element, t->right);
		}
	}

	// If the tree had only one node 
	// then return  
	if (t == NULL)
		return;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
	t->height = 1 + max(height(t->left), height(t->right));

	// STEP 3: GET THE BALANCE FACTOR OF  
	// THIS NODE (to check whether this  
	// node became unbalanced)  
	int balance = getBalance(t);

	// If this node becomes unbalanced,  
	// then there are 4 cases  

	// Left Left Case  
	if (balance > 1 && getBalance(t->left) >= 0)
		rotateWithLeftChild(t);

	// Left Right Case  
	if (balance > 1 && getBalance(t->left) < 0)
		doubleWithLeftChild(t);

	// Right Right Case  
	if (balance < -1 && getBalance(t->right) <= 0)
		rotateWithRightChild(t);

	// Right Left Case  
	if (balance < -1 && getBalance(t->right) > 0)
		doubleWithRightChild(t);
}

/**
  * Rotate binary tree node with left child.
  * For AVL trees, this is a single rotation for case 1.
  * Update heights, then set new root.
  */
template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(
	AvlNode<Comparable>*& k2) const
{
	AvlNode<Comparable>* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

/**
 * Rotate binary tree node with right child.
 * For AVL trees, this is a single rotation for case 4.
 * Update heights, then set new root.
 */
template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild
(AvlNode<Comparable>*& k1) const
{
	AvlNode<Comparable>* k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	k1 = k2;
}

/**
  * Double rotate binary tree node: first left child.
  * with its right child; then node k3 with new left child.
  * For AVL trees, this is a double rotation for case 2.
  * Update heights, then set new root.
  */
template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild
(AvlNode<Comparable>*& k3) const
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

/**
 * Double rotate binary tree node: first right child.
 * with its left child; then node k1 with new right child.
 * For AVL trees, this is a double rotation for case 3.
 * Update heights, then set new root.
 */
template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild
(AvlNode<Comparable>*& k1) const
{
	rotateWithLeftChild(k1->right);
	rotateWithRightChild(k1);
}

template<class Comparable> // private
AvlNode<Comparable>* AvlTree<Comparable>::clone() const
{
	if (root == nullptr)  //if tree is empty
		return nullptr;   //clone becomes empty

	AvlNode<Comparable>* headClone = new AvlNode<Comparable>(root->element, NULL, NULL);
	AvlNode<Comparable>* dest = headClone;
	AvlNode<Comparable>* src = root;
	if (root) // if root is not nullpointer
		cloneHelper(src, dest);

	return headClone;
}

template<class Comparable> // private
void AvlTree<Comparable>::cloneHelper(AvlNode<Comparable>* source, AvlNode<Comparable>*& destination) const {

	destination->element = source->element;

	if (source->right)
	{
		destination->right = new AvlNode<Comparable>(source->element, NULL, NULL);
		cloneHelper(source->right, destination->right);
	}
	if (source->left)
	{
		destination->left = new AvlNode<Comparable>(source->element, NULL, NULL);
		cloneHelper(source->left, destination->left);
	}
}

/**
  * Print the tree contents inorder.
  */
template <class Comparable>
void AvlTree<Comparable>::printTreeInorder() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else {
		ofstream os;
		os.open("phonebookInOrderAVL.txt");
		printTreeInorder(os, root);
		os.close();
	}
}

template <class Comparable>
void AvlTree<Comparable>::printTreePreorder() const
{
	if (isEmpty())
		cout << "Empty tree" << endl;
	else {
		ofstream os;
		os.open("phonebookPreOrderAVL.txt");
		printTreePreorder(os, root);
		os.close();
	}
}

template<class Comparable>
void AvlTree<Comparable>::printTreeInorder(ostream& out, AvlNode<Comparable>* t) const// private
{
	if (t == NULL) return;
	printTreeInorder(out, t->left);
	out << t->element << endl;
	printTreeInorder(out, t->right);
}

template<class Comparable>
void AvlTree<Comparable>::printTreePreorder(ostream& out, AvlNode<Comparable>* t) const // private
{
	if (t == NULL) return;
	out << t->element << endl;
	printTreePreorder(out, t->left);
	printTreePreorder(out, t->right);
}

template<class Comparable>
const AvlTree<Comparable>& AvlTree<Comparable>::operator=(const AvlTree& rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		root = rhs.clone();
	}
	return *this;
}

template<class Comparable>
void AvlTree<Comparable>::drawTree() const
{
	ofstream os;
	os.open("phonebookTreeAVL.txt");
	drawTree(os, "", root, false);
	os.close();
}

template<class Comparable>
void AvlTree<Comparable>::drawTree(ostream& os, const string& prefix, const AvlNode<Comparable>* node, bool isLeft) const
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

template<class Comparable>
void AvlTree<Comparable>::getHeight() {
	int lh = height(root->left) + 1;
	int rh = height(root->right) + 1;
	cout << "The heights of AVL are for left: " << lh << " and right: " << rh << endl;
}