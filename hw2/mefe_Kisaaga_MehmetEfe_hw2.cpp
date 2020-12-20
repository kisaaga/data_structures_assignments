// cs300-hw2        Mehmet Efe Kisaaga          25255
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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

	friend ostream& operator << (ostream& os, const registry& rhs);
};

ostream& operator << (ostream& os, const registry& rhs)
{
	os << rhs.fullName << " " << rhs.phoneNumber << " " << rhs.city;
	return os;
}

bool createTrees(AvlTree<registry>& AVLTree, BinarySearchTree<registry>& BSTree) // read file and upload trees
{
	string filename;
	ifstream contactFile;
	cout << "Please enter the contact filename: ";
	cout << endl;
	cin >> filename;
	contactFile.open(filename.c_str());
	if (contactFile.fail())
	{
		return false;
	}
	else
	{
		cout << "Loading the phonebook into a BST\n" << endl;
		string line, fn, ln, p, c;
		auto start = std::chrono::system_clock::now();
		while (getline(contactFile, line))
		{
			istringstream ss(line);
			ss >> fn >> ln >> p >> c;
			strToUpper(fn);
			strToUpper(ln);
			registry temp(fn, ln, p, c);
			BSTree.insert(temp);
		}
		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		cout << "Phonebook creation in BST took " << elapsed.count() << " milliseconds" << '\n';
		cout << endl;
		if (BSTree.AVL())
		{
			cout << "The tree is balanced\n";
		}
		else
		{
			cout << "The tree is not balanced\n" << endl;
		}
		BSTree.getHeight();
		contactFile.close();
		contactFile.open(filename.c_str());
		if (contactFile.fail())
		{
			return false;
		}
		else
		{
			cout << "Loading the phonebook into a AVL\n" << endl;
			auto start = std::chrono::system_clock::now();
			while (getline(contactFile, line))
			{
				istringstream ss(line);
				ss >> fn >> ln >> p >> c;
				strToUpper(fn);
				strToUpper(ln);
				registry temp(fn, ln, p, c);
				AVLTree.insert(temp);
			}
			auto end = std::chrono::system_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			cout << "Phonebook creation in AVL took " << elapsed.count() << " milliseconds" << '\n';
			cout << endl;
			if (AVLTree.AVL())
			{
				cout << "The tree is balanced\n";
			}
			else
			{
				cout << "The tree is not balanced\n" << endl;
			}
			AVLTree.getHeight();
			contactFile.close();
			return true;
		}
	}
}

void searchContact(AvlTree<registry> AVLTree, BinarySearchTree<registry> BSTree, registry notFound) { // search for given name
	string searchfor;
	cout << "Searching an item in the phonebook(BST) ...\n====================\nSearch for a contact : ";
	cin.ignore();
	getline(cin, searchfor);
	strToUpper(searchfor);
	registry src;
	src.fullName = searchfor;
	cout << "Phonebook : Searching for: (" << searchfor << ")\n====================================\n\n";
	auto start = std::chrono::system_clock::now();
	if (BSTree.find(src).fullName == notFound.fullName)
	{
		cout << "This contact does not exist!!!\n" << endl;
	}
	while (BSTree.find(src).fullName != notFound.fullName)
	{
		cout << BSTree.find(src) << endl << endl;
		BSTree.remove(src);
	}
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Searching an item in the phonebook (AVL) ...\n\nPhone book : Section (" << searchfor << ")\n====================================\n\n";
	start = std::chrono::system_clock::now();
	if (AVLTree.find(src).fullName == notFound.fullName)
	{
		cout << "This contact does not exist!!!\n" << endl;
	}
	while (AVLTree.find(src).fullName != notFound.fullName)
	{
		cout << AVLTree.find(src) << endl << endl;
		AVLTree.remove(src);
	}
	end = std::chrono::system_clock::now();
	auto elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "The search in BST took " << elapsed.count() << " milliseconds..." << endl << '\n';
	std::cout << "The search in AVL took " << elapsed2.count() << " milliseconds..." << endl << '\n';
}

void addContact(AvlTree<registry> & AVLTree, BinarySearchTree<registry> & BSTree, registry notFound) // add the contact with taken informations
{
	string name, tel, city;
	cout << "Adding an item to the phonebook (BST) ..." << endl;
	cout << "====================" << endl;
	cout << "Enter the information of the contact to be added:\n";
	cout << "Name: ";
	cin.ignore();
	getline(cin, name);
	cout << endl;
	strToUpper(name);

	cout << "Tel: ";
	cin >> tel;
	cout << endl;

	cout << "City: ";
	cin >> city;
	cout << endl;
	capitalize(city);

	registry temp(name.substr(0, name.find(" ")), name.substr(name.find(" ")+1), tel, city);
	if (BSTree.find(temp).fullName == notFound.fullName)
	{
		auto start = std::chrono::system_clock::now();
		BSTree.insert(temp);
		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		cout << "Contact has been added successfully to the BST\n\n";

		cout << "Adding an item to the phonebook (AVL) ..." << endl;
		cout << "====================" << endl;
		auto start2 = std::chrono::system_clock::now();
		AVLTree.insert(temp);
		auto end2 = std::chrono::system_clock::now();
		auto elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);
		cout << "Contact has been added successfully to the AVL\n" << endl;

		std::cout << "Adding a contact to the Binary Tree took " << elapsed.count() << " nanoseconds..." << endl;
		std::cout << "Adding a contact to the AVL tree took " << elapsed2.count() << " nanoseconds..." << endl << '\n';
	}
	else
	{
		cout << "This contact already exists!!!\n";
	}

}

void deleteContact(AvlTree<registry>& AVLTree, BinarySearchTree<registry>& BSTree, registry notFound) // delete the contact with given full name
{
	string name, tel, city;
	cout << "Deleting an item to the phonebook (BST) ..." << endl;
	cout << "====================" << endl;
	cout << "Enter the fullname of the contact to be deleted:\n";
	cin.ignore();
	getline(cin, name);
	cout << endl;
	strToUpper(name);

	registry temp;
	temp.fullName = name;
	if (BSTree.find(temp).fullName != notFound.fullName)
	{
		auto start = std::chrono::system_clock::now();
		BSTree.remove(temp);
		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		
		start = std::chrono::system_clock::now();
		AVLTree.remove(temp);
		end = std::chrono::system_clock::now();
		auto elapsed2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
		cout << "Deleted succesfully...\n" << endl;

		std::cout << "Deletion from Binary Tree took " << elapsed.count() << " nanoseconds..." << endl;
		std::cout << "Deletion from AVL Tree took " << elapsed2.count() << " nanoseconds..." << endl << '\n';
	}
	else
	{
		cout << "This contact does not exist!!!\n";
	}
}

void saveToFile(const AvlTree<registry> & AVLTree, const BinarySearchTree<registry> & BSTree) // print all trees to the files in inorder and preorder traversals
{
	cout << "Saving the phonebook to a file (In-Order)...\n";
	cout << "====================\n";
	auto start = std::chrono::system_clock::now();
	BSTree.printTreeInorder();
	AVLTree.printTreeInorder();
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "Saving the phonebook took " << elapsed.count() << " nanoseconds...\n" << endl;


	cout << "Saving the phonebook to a file (Pre-Order)...\n";
	cout << "====================\n";
	start = std::chrono::system_clock::now();
	BSTree.printTreePreorder();
	AVLTree.printTreePreorder();
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "Saving the phonebook took " << elapsed.count() << " nanoseconds...\n" << endl;
}

void draw(const AvlTree<registry>& AVLTree, const BinarySearchTree<registry>& BSTree) // draw the trees pretty
{
	cout << "Drawing the phonebook to a file (BST)...\n";
	cout << "====================\n";
	auto start = std::chrono::system_clock::now();
	BSTree.drawTree();
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "Drawing the phonebook took " << elapsed.count() << " nanoseconds...\n" << endl;

	cout << "Drawing the phonebook to a file (AVL)...\n";
	cout << "====================\n";
	start = std::chrono::system_clock::now();
	AVLTree.drawTree();
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	cout << "Drawing the phonebook took " << elapsed.count() << " nanoseconds...\n" << endl;
}

int main()
{
	registry notFound("na", "na", "na", "na");
	AvlTree<registry> AVLTree(notFound);
	BinarySearchTree<registry> BSTree(notFound);
	if (!createTrees(AVLTree, BSTree))
	{
		cout << "Incorrect filename!\n";
	}
	else
	{
		while (true)
		{
			cout << endl;
			cout << "Choose which action to perform from 1 to 6:\n"
				<< "1 - Search a phonebook contact\n"
				<< "2 - Adding a phonebook contact\n"
				<< "3 - Deleting a phonebook contact\n"
				<< "4 - Print the phonebook to a file(inorder)\n    Print the phonebook to a file(preorder)\n"
				<< "5 - Draw the phonebook as a tree to a file\n"
				<< "6 - Press 6 to exit\n";
			cout << endl;

			int option;
			cin >> option;
			cout << endl;
			switch (option)
			{
			case 1:
				searchContact(AVLTree, BSTree, notFound);
				break;
			case 2:
				addContact(AVLTree, BSTree, notFound);
				break;
			case 3:
				deleteContact(AVLTree, BSTree, notFound);
				break;
			case 4:
				saveToFile(AVLTree, BSTree);
				break;
			case 5:
				draw(AVLTree, BSTree);
				break;
			case 6:
				cout << "Exiting... " << endl;
				system("pause");
				exit(0);
			default:
				cout << "INVALID OPTION!" << endl;
				break;
			}
		}
	}

	return 0;
}
