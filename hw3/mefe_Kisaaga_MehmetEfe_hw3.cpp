// Mehmet Efe Kisaaga		25255		CS 300 - Homework 3

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "HashTable.h"

using namespace std;

int placeProducts(string filename, HashTable<Product>& products) { // read file and place products seperatly
	ifstream fs;
	string prd, line;
	int total_lines = 0;
	fs.open(filename.c_str());
	while (getline(fs, line))
	{
		istringstream ss(line);
		while (ss >> prd)
		{
			Product temp;
			temp.name = prd;
			temp.count = 1;
			products.insert(temp);
		}
		total_lines++;
	}
	return total_lines;
}

void calculateSupportValues(HashTable<Product>& products, int total, double sv) { // calculate support values and at the end store only the ones which have support value is higher than the threshold
	for (int i = 0; i < products.getLists().size(); i++)
	{
		List<Product>& currList = products.getLists()[i];
		ListItr<Product> currProd = currList.first();
		while (!currProd.isPastEnd())
		{
			Product& prod = currProd.retrieve();
			prod.s_value = double(prod.count) / total;
			Product temp = prod;
			currProd.advance();
			if (temp.s_value < sv)
			{
				products.remove(temp);
			}
		}
	}
}

void printHash(HashTable<Product>& products) { // in order to print and see the hash table
	for (int i = 0; i < products.getLists().size(); i++)
	{
		List<Product> currList = products.getLists()[i];
		ListItr<Product> currProd = currList.first();
		cout << i;

		while (!currProd.isPastEnd())
		{
			Product prod = currProd.retrieve();
			cout << " --> " << prod.name << "-" << prod.count << "-" << prod.s_value;
			currProd.advance();
		}
		cout << endl;
	}
	cout << endl;
}

void makePairs(HashTable<Product>& table, string filename, int total, double sv) { // make pairs and store the ones which have support value higher than the threshold
	vector<Product> temp;
	for (int i = 0; i < table.getLists().size(); i++)
	{
		List<Product>& currList = table.getLists()[i];
		ListItr<Product> currProd = currList.first();
		while (!currProd.isPastEnd())
		{
			Product prod = currProd.retrieve();
			temp.push_back(prod);
			currProd.advance();
		}
	}
	ifstream fs;
	string line;
	fs.open(filename.c_str());
	for (int n = 0; n < temp.size(); n++)
	{
		for (int m = n + 1; m < temp.size(); m++)
		{
			string newPair = temp[n].name + "," + temp[m].name;
			Product toAdd;
			toAdd.name = newPair;
			toAdd.count = 0;
			while (getline(fs, line))
			{
				if (line.find(temp[n].name) != string::npos && line.find(temp[m].name) != string::npos)
				{
					toAdd.count = toAdd.count + 1;
				}
			}
			toAdd.s_value = double(toAdd.count) / total;
			fs.clear();
			fs.seekg(0);
			if (toAdd.s_value >= sv)
			{
				table.insert(toAdd);
			}
		}
	}
}

vector<pair<Product, Product>> extractRules(HashTable<Product> products) { // form rules - not including calculation of confidence values
	vector<pair<Product, Product>> toReturn;
	for (int i = 0; i < products.getLists().size(); i++)
	{
		List<Product> currList = products.getLists()[i];
		ListItr<Product> currProd = currList.first();
		while (!currProd.isPastEnd())
		{
			Product prod = currProd.retrieve();
			for (int j = 0; j < products.getLists().size(); j++)
			{
				List<Product> currList2 = products.getLists()[j];
				ListItr<Product> currProd2 = currList2.first();
				while (!currProd2.isPastEnd())
				{
					Product prod2 = currProd2.retrieve();
					if (prod.name.find(",") == string::npos) // if it is not a pair
					{
						if (prod2.name.find(prod.name) == string::npos) // if there is not a same product
						{
							pair<Product, Product> temp;
							temp.first = prod;
							temp.second = prod2;
							toReturn.push_back(temp);
						}
					}
					else
					{
						string pr1, pr2;
						pr1 = prod.name.substr(0, prod.name.find(","));
						pr2 = prod.name.substr(prod.name.find(",") + 1);

						if (prod2.name.find(pr1) == string::npos && prod2.name.find(pr2) == string::npos)
						{
							pair<Product, Product> temp;
							temp.first = prod;
							temp.second = prod2;
							toReturn.push_back(temp);
						}
					}
					currProd2.advance();
				}
			}
			currProd.advance();
		}
	}
	return toReturn;
}

string doublePre(double value) // in order to format doubles
{
	string str = to_string(value);
	int dotInd = str.find(".");
	str = str.substr(0, dotInd + 3);
	return str;
}

void printRules(vector<pair<Product, Product>> rules, string filename, double cv, int total) { // take rules and depend on their confidence values print them to a file
	ifstream fs;
	ofstream os;
	os.open("results.txt");
	string line;
	int total_rules = 0;
	for (int i = 0; i < rules.size(); i++)
	{
		Product p1 = rules[i].first;
		Product p2 = rules[i].second;
		string products = p1.name + "," + p2.name;
		istringstream ss(products);
		vector<string> p_names;
		string p;
		int count = 0;
		while (getline(ss, p, ','))
		{
			p_names.push_back(p);
		}
		fs.open(filename.c_str());
		while (getline(fs, line))
		{
			bool matches = true;
			for (int m = 0; m < p_names.size(); m++)
			{
				if (line.find(p_names[m]) == string::npos)
				{
					matches = false;
				}
			}
			if (matches)
			{
				count++;
			}
		}
		fs.close();
		double curr_sv = double(count) / total;
		double curr_cv = curr_sv / p1.s_value; // calculation of confidence value
		if (curr_cv >= cv)
		{
			total_rules++;
			os << p1.name << ";" << p2.name << ";" << doublePre(curr_cv) << "\n";
		}
	}
	os.close();
	if (total_rules == 0)
	{
		cout << "There is no rule for the given support and confidence values." << endl;
	}
	else
	{
		cout << total_rules << " rules are written to results.txt" << endl;
	}
}

int main()
{
	Product notFound;
	notFound.name = "NF";

	HashTable<Product> myTable(notFound);
	string filename;
	double sv_threshold, cv_threshold;
	cout << "Please enter the transaction file name: ";
	cin >> filename;
	ifstream fs;
	fs.open(filename.c_str());
	if (fs.fail())
	{
		cout << "Invalid fail name!!!\n";
	}
	else
	{
		fs.close();
		cout << "Please enter support and confidence values between 0 and 1: ";
		cin >> sv_threshold >> cv_threshold;

		int total_transactions = placeProducts(filename, myTable);

		calculateSupportValues(myTable, total_transactions, sv_threshold);

		makePairs(myTable, filename, total_transactions, sv_threshold);

		vector<pair<Product, Product>> rules = extractRules(myTable);
		printRules(rules, filename, cv_threshold, total_transactions);
	}
	return 0;
}