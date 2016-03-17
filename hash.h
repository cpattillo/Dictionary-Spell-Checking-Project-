
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "LL.h"

#ifndef HASH_H
#define HASH_H


using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::istream;
using std::cin;

class HashTable{

private:

	int TableSize; //Table Size
	
	int numElements; //number of elements in table

	LL<string> * ptr; //pointer to the array

	size_t hash(const string& key); //internal hash function 

	int collisions;  //number of collisions in table
	
public:
	
	//Constructor 
	HashTable(int numbers = 47087);

	//Return number of elements
	int elements() { return numElements; }

	//Return Tablesize
	int TS() { return TableSize; }

	int numCollisions(){ return collisions; }

	//Insert into hash table 
	void insert(const string& key);

	//Remove something from the hash table
	void remove(const string& key);

	//Checks if hash table contains key
	bool contains(const string& key); 

	//Prints index of an element, for testing purposes 
	void printTest(const string& a);
};

//Default constructor with default parameter 
HashTable::HashTable(int cap)
{
	TableSize = cap;
	ptr = new LL<string>[TableSize];
	collisions = 0; 
	numElements = 0; 
}

//Insert key in table
void HashTable::insert(const string& name)
{ 
	int index = hash(name) % TableSize; 

	if (!(ptr[index].isEmpty()))
	{
		collisions++;
	}
	
	ptr[index].Insert_rear(name);
	numElements++; 
}

//Internal hashing function 
size_t HashTable::hash(const string& key)
{
	size_t hashVal = 0;

	for (char ch : key)
	{
		hashVal = 37 * hashVal + ch;
	}

	return hashVal;
}

//Checks if list contains a value
bool HashTable::contains(const string& value)
{
	int index = hash(value) % TableSize; 
	 
	if (ptr[index].inList(value))
	{
		return true;
	}
	else
	{
		return false; 
	}

}

//Remove function 
void HashTable::remove(const string& value)
{
	int index = hash(value) % TableSize;

	if (contains(value))
	{
		ptr[index].eraseVal(value);
		numElements--; 
	}
}

//Prints the index of a key in the table 
void HashTable::printTest(const string& a)
{
	int index = hash(a) % TableSize;
	cout << "The has index is: " << index << endl; 
}


#endif