// Mehmet Efe Kisaaga       25255       CS 300 - Homework 5
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "AvlTree.cpp"
#include "BinarySearchTree.cpp"
#include <chrono>
using namespace std;

void strToUpper(string& str) { // in order to convert strings' all letter to upper case
	for (int i = 0; i < str.length(); i++)
	{
		str.at(i) = toupper(str.at(i));
	}
}

void capitalize(string& str) { // in order to correct city input - to capitalize it
	str.at(0) = toupper(str.at(0));
	for (int i = 1; i < str.length(); i++)
	{
		str.at(i) = tolower(str.at(i));
	}
}

class registry { // this will keep our contact informations and it includes necessary operators
public:
	string firstName, lastName, fullName, phoneNumber, city;

	registry() {
		firstName = "na";
		lastName = "na";
		fullName = "na";
		phoneNumber = "na";
		city = "na";
	}
	registry(string firstName, string lastName, string phoneNumber, string city) :firstName(firstName), lastName(lastName), phoneNumber(phoneNumber), city(city) {
		fullName = firstName + " " + lastName;
	}
	registry(const registry& copy) {
		firstName = copy.firstName;
		lastName = copy.lastName;
		fullName = copy.fullName;
		phoneNumber = copy.phoneNumber;
		city = copy.city;
	}

	bool operator ==(const registry& c) {
		for (unsigned int i = 0; i < c.fullName.length(); i++) {
			if (fullName[i] != c.fullName[i])
				return false;
		}
		return true;
	}

	bool operator !=(const registry& c) {
		return !(*this == c);
	}

	bool operator <(const registry& c) {
		if (fullName.length() > c.fullName.length())
		{
			if (fullName.find(c.fullName) == 0)
			{
				return false;
			}
		}
		else
		{
			if (c.fullName.find(fullName) == 0)
			{
				return false;
			}
		}
		return fullName < c.fullName;
	}

	bool operator >(const registry& c) {
		if (fullName.length() > c.fullName.length())
		{
			if (fullName.find(c.fullName) == 0)
			{
				return false;
			}
		}
		else
		{
			if (c.fullName.find(fullName) == 0)
			{
				return false;
			}
		}
		return fullName > c.fullName;
	}

	bool operator >=(const registry& c) {
		return !(*this < c);
	}

	bool operator <=(const registry& c) {
		return !(*this > c);
	}

	friend ostream& operator << (ostream& os, const registry& rhs);
};

ostream& operator << (ostream& os, const registry& rhs)
{
	os << rhs.fullName << " " << rhs.phoneNumber << " " << rhs.city;
	return os;
}

template<class Comparable>
int binarySearch(vector<Comparable>& arr, int l, int r, Comparable x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		// If the element is present at the middle
		if (arr[mid] == x)
			return mid;

		// If element is smaller than mid
		if (arr[mid] > x)
			return binarySearch<Comparable>(arr, l, mid - 1, x);

		// Else the element can only be present 
		// in right subarray 
		return binarySearch< Comparable>(arr, mid + 1, r, x);
	}
	// We reach here when element is not 
	// present in array 
	return -1;
}

void createTrees(string filename, AvlTree<registry>& AVLTree, BinarySearchTree<registry>& BSTree) // read file and upload trees
{
	ifstream contactFile;
	contactFile.open(filename.c_str());
	string line, fn, ln, p, c;
	while (getline(contactFile, line))
	{
		istringstream ss(line);
		ss >> fn >> ln >> p >> c;
		strToUpper(fn);
		strToUpper(ln);
		registry temp(fn, ln, p, c);
		BSTree.insert(temp);
	}
	contactFile.close();
	contactFile.open(filename.c_str());
	while (getline(contactFile, line))
	{
		istringstream ss(line);
		ss >> fn >> ln >> p >> c;
		strToUpper(fn);
		strToUpper(ln);
		registry temp(fn, ln, p, c);
		AVLTree.insert(temp);
	}
	contactFile.close();
}

void searchContact(string searchfor, vector<registry> arr, AvlTree<registry>& AVLTree, BinarySearchTree<registry>& BSTree, registry notFound) { // search for given name
	registry src;
	int n_loop = 100;
	src.fullName = searchfor;
	string name = searchfor.substr(0, searchfor.find(' '));
	capitalize(name);
	cout << endl << "Searching for " << name << "\n======================================\n";

	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < n_loop; i++)
	{
		if (BSTree.find(src).fullName == notFound.fullName)
		{
			cout << "This contact does not exist in BST!!!\n" << endl;
			return;
		}
	}
	auto end = std::chrono::system_clock::now();
	auto timeBST = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "The search in BST took " << timeBST.count()/n_loop << " Nanoseconds" << endl;

	auto start2 = std::chrono::system_clock::now();
	for (int i = 0; i < n_loop; i++)
	{
		if (AVLTree.find(src).fullName == notFound.fullName)
		{
			cout << "This contact does not exist in AVL!!!\n" << endl;
			return;
		}
	}
	auto end2 = std::chrono::system_clock::now();
	auto timeAVL = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
	cout << "The search in AVL took " << timeAVL.count()/n_loop << " Nanoseconds" << endl;

	auto start3 = std::chrono::system_clock::now();
	for (int i = 0; i < n_loop; i++)
	{
		binarySearch(arr, 0, arr.size() - 1, src);
	}
	auto end3 = std::chrono::system_clock::now();
	auto timeVec = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3);
	cout << "Binary Search Time: " << timeVec.count()/n_loop << " Nanoseconds" << endl;

	cout << "\nSpeedUps in search" << endl << "======================================" << endl;
	cout << "(BST / AVL) SpeedUp  = " << float(timeBST.count()) / timeAVL.count() << endl;
	cout << "(Binary Search / AVL) SpeedUp  = " << float(timeVec.count()) / timeAVL.count() << endl;
	cout << "(Binary Search / BST) SpeedUp  = " << float(timeVec.count()) / timeBST.count() << endl;
}

template <class Comparable>
int QuicksortPartition(vector<Comparable>& A, int lo, int hi)
{
	int ci = (int)(0.5 * (lo + hi) + 0.5);
	int pivotIndex = ci;
	Comparable pivot = A[pivotIndex];

	int i = lo;
	int j = hi;
	while (true)
	{
		while (A[i] <= pivot && i < pivotIndex) i++;
		while (A[j] >= pivot && j > pivotIndex) j--;
		if (i == pivotIndex && j == pivotIndex)
			return pivotIndex;

		Comparable tmp = A[i];
		A[i] = A[j];
		A[j] = tmp;

		if (i == pivotIndex)
			pivotIndex = j;
		else if (j == pivotIndex)
			pivotIndex = i;
	}
}

template <class Comparable>
void Quicksort(vector<Comparable>& A, int lo, int hi)
{
	if (lo < hi)
	{
		int p = QuicksortPartition<Comparable>(A, lo, hi);
		if (p > 0) //p is unsigned, so prevent negative
			Quicksort<Comparable>(A, lo, p - 1);
		Quicksort<Comparable>(A, p + 1, hi);
	}
}

template <class Comparable>
void Quicksort(vector<Comparable>& A)
{
	if (A.size() <= 1)
		return; //Nothing to do
	Quicksort(A, 0, A.size() - 1);
}

/* Function to sort an array using insertion sort*/
template<class Comparable>
void insertionSort(vector<Comparable>& arr, int n)
{
	int i, j;
	Comparable key;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

template<class Comparable>
void merge(vector<Comparable>& arr, int start, int mid, int end)
{
	int start2 = mid + 1;

	// If the direct merge is already sorted 
	if (arr[mid] <= arr[start2]) {
		return;
	}

	// Two pointers to maintain start 
	// of both arrays to merge 
	while (start <= mid && start2 <= end) {

		// If element 1 is in right place 
		if (arr[start] <= arr[start2]) {
			start++;
		}
		else {
			Comparable value = arr[start2];
			int index = start2;

			// Shift all the elements between element 1 
			// element 2, right by 1. 
			while (index != start) {
				arr[index] = arr[index - 1];
				index--;
			}
			arr[start] = value;

			// Update all the pointers 
			start++;
			mid++;
			start2++;
		}
	}
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
template<class Comparable>
void mergeSort(vector<Comparable>& arr, int l, int r)
{
	if (l < r) {

		// Same as (l + r) / 2, but avoids overflow 
		// for large l and r 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort<Comparable>(arr, l, m);
		mergeSort<Comparable>(arr, m + 1, r);

		merge<Comparable>(arr, l, m, r);
	}
}


// To heapify a subtree rooted with node i which is 
// an index in arr[]. n is size of heap 
template<class Comparable>
void heapify(vector<Comparable>& arr, int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree 
		heapify<Comparable>(arr, n, largest);
	}
}

inline int leftChild(int i)
{
	return 2 * i + 1;
}

template <class Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
	int child;
	Comparable tmp;
	for (tmp=a[i] ; leftChild(i) < n; i = child )
	{
		child = leftChild(i);
		if ( child != n-1 && a[ child ] < a[ child+1 ] )
			child++;
		if ( a[child ] > tmp )
			a[i] = a[ child ];
		else
			break;
	}
	a[ i ] = tmp;
}

// main function to do heap sort 
template<class Comparable>
void heapSort(vector<Comparable>& arr, int n)
{
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--)
		percDown<Comparable>(arr, i, n);

	// One by one extract an element from heap 
	for (int i = n - 1; i > 0; i--)
	{
		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
		percDown<Comparable>(arr, 0, i);
	}
}

void makeVectors(string filename, vector<registry>& v1, vector<registry>& v2, vector<registry>& v3, vector<registry>& v4) {
	ifstream file;
	file.open(filename.c_str());
	string line, fn, ln, p, c;
	while (getline(file, line))
	{
		istringstream ss(line);
		ss >> fn >> ln >> p >> c;
		strToUpper(fn);
		strToUpper(ln);
		registry temp(fn, ln, p, c);
		v1.push_back(temp);
		v2.push_back(temp);
		v3.push_back(temp);
		v4.push_back(temp);
	}
	file.close();
}

vector<long long int> sortVectors(vector<registry>& v1, vector<registry>& v2, vector<registry>& v3, vector<registry>& v4) {
	vector<long long int> times;
	cout << endl << "Sorting the vector copies" << endl;
	cout << "======================================" << endl;

	auto start = std::chrono::system_clock::now();
	Quicksort(v1);
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "Quick Sort Time: " << elapsed.count() << " Nanoseconds" << endl;
	times.push_back(elapsed.count());

	start = std::chrono::system_clock::now();
	insertionSort<registry>(v2, v2.size());
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "Insertion Sort Time: " << elapsed.count() << " Nanoseconds" << endl;
	times.push_back(elapsed.count());

	start = std::chrono::system_clock::now();
	mergeSort<registry>(v3, 0, v3.size() - 1);
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "Merge Sort Time: " << elapsed.count() << " Nanoseconds" << endl;
	times.push_back(elapsed.count());

	start = std::chrono::system_clock::now();
	heapSort<registry>(v4, v4.size());
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "Heap Sort Time: " << elapsed.count() << " Nanoseconds" << endl;
	times.push_back(elapsed.count());
	return times;
}

int main()
{
	string filename, name;
	vector<registry> v1, v2, v3, v4;
	registry ITEM_NOT_FOUND("na", "na", "na", "na");
	AvlTree<registry> avl(ITEM_NOT_FOUND);
	BinarySearchTree<registry> bst(ITEM_NOT_FOUND);
	cout << "Please enter the contact file name:" << endl;
	cin >> filename;
	makeVectors(filename, v1, v2, v3, v4);
	createTrees(filename, avl, bst);
	cout << "Please enter the word to be queried:" << endl;
	cin.ignore();
	getline(cin, name);
	strToUpper(name);
	vector<long long int> times = sortVectors(v1, v2, v3, v4);
	searchContact(name, v1, avl, bst, ITEM_NOT_FOUND);
	cout << endl << "SpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl;
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << float(times[1]) / times[0] << endl;
	cout << "(Merge Sort / Quick Sort) SpeedUp = " << float(times[2]) / times[0] << endl;
	cout << "(Heap Sort / Quick Sort) SpeedUp = " << float(times[3]) / times[0] << endl;
	//avl.drawTree();
	//bst.drawTree();
	/*
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << endl;
	}*/

	return 0;
}
