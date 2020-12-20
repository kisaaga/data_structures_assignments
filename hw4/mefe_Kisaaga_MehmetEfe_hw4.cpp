// Mehmet Efe Kisaaga    25255   CS 300 - Homework 4
//

#include <iostream>
#include <fstream>
#include <string>
#include "Heaps.h"

using namespace std;

double getMedian(int e, double& m, Heap<int>& l, Heap<int>& r) {
	if (l.GetCount() > r.GetCount()) { // if max heap includes more elements
		if (e < m) { // if alo requires to add left heap then balance the heaps
			r.Insert(l.ExtractTop());
			l.Insert(e);
		}
		else {
			r.Insert(e);
		}
		m = (l.GetTop() + r.GetTop())/double(2);
	}
	else if (l.GetCount() == r.GetCount()) { // if there is equal amount of elements
		if (e < m) {
			l.Insert(e);
			m = l.GetTop();
		}
		else {
			r.Insert(e);
			m = r.GetTop();
		}
	}
	else if (l.GetCount() < r.GetCount()) { // if min heap includes more elements
		if (e < m) {
			l.Insert(e);
		}
		else {
			l.Insert(r.ExtractTop());
			r.Insert(e);
		}
		m = (l.GetTop() + r.GetTop()) / double(2);
	}
	return m;
}

bool findMedian(string filename, double& median, Heap<int>* left, Heap<int>* right) {
	ifstream file;
	file.open(filename.c_str());
	if (file.fail()) // if there is no such file
	{
		return false;
	}
	else
	{
		string str;
		int num;
		while (file >> str) {
			num = stoi(str); // take number and convert it to integer
			median = getMedian(num, median, *left, *right);
		}
		return true;
	}
	file.close();
}

int main()
{
	string filename;
	double median = 0.0;
	Heap<int>* left = new MaxHeap<int>(-1);
	Heap<int>* right = new MinHeap<int>(-1);

	cout << "Please enter the next filename that contains integer stream: ";
	while (getline(cin, filename))
	{
		if (findMedian(filename, median, left, right))
		{
			cout << "median: " << median << endl;
		}
		else
			cout << "No such files exists!" << endl;

		cout << "Please enter the next filename that contains integer stream: ";
	}

	delete left;
	delete right;

	return 0;
}