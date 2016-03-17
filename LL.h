/*
Caroline Pattillo (cbp53)
Assignment 0
*/


#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <new>


using namespace std;

#ifndef LL_H
#define LL_H

//************************** Node Class ************************************************

template <class T>
class Node
{
public:
	string key; //Stores the coefficient in polynomial  
	Node<T> *next;//Points to next linked list item
	Node<T> *prev;//Points to previous item in linked list

	//Default constructor 
	//Default parameter for next 
	//Sets info to a T data type and next to ptr
	Node(string = "$$$$$$$", Node<T> * nextptr = NULL, Node<T> * prevptr = NULL);

};

//*********************** LL Class **************************************************************

template <class T>
class LL
{

private:

	Node<T> *sentinel;

	int count; //number of items in linked list 

	//Copies Linked Lists
	//Uses Insert_rear method to build new linked list
	void copyList(const LL<T> & listtoCopy);



public:

	//Default Construtor
	//Sets head, tail to NULL and count to 0
	LL();

	//Copy Constructor, calls copylist
	LL(const LL<T> &otherLL);

	//Destructor, destroys dynaimcally created memory (Nodes)
	//Calls the clear method
	~LL();

	//Adds a new Node to the end of the Linked List
	//Updates new list count
	void Insert_rear(string);

	//Adds a new Node to the front of the Linked List
	//Updates new list count
	void Insert_front(T);

	//Deletes the last Node in the Linked List
	//Removes one from count
	void erase_rear();

	//Deletes all the Nodes in the Linked List
	void clear();

	//Returns the number of elements in the Linked List 
	int size() const;

	//Returns the capacity of the Linked List 
	int cap() const;

	//Returns reference of Object in position ndx of linked list 
	T& at(int ndx);

	//Returns Degree at positon index
	T& atD(int ndx);

	//Overloads the [] operator, returns the T object reference in positon ndx of linked list
	T& operator[](int ndx);

	//Returns reference of Object in position ndx of linked list
	//cannot modify T object
	T& at(int ndx) const;

	//Overloads the [] operator
	//returns the T object reference in positon ndx of linked list
	//Cannot modify T object
	T& operator [] (int ndx) const;

	//Overloading Assignment operator 
	//Returns the LL object 
	const LL<T>& operator=(const LL<T> &);

	//Insert value in index
	void Insert(int index, T val);

	//Erase node in the linked list
	void erase(int index);

	//Erase Front
	void erase_front();

	//Returns value in front node
	T& front() const;

	//Returns value in rear node
	T& back() const;

	//prints LL
	void print();


	//get Sentinel pointer
	Node<T> * getSent() const;

	//Checks to see if something is in the list
	bool inList(const string& val);

	//Erases a value
	void eraseVal(const string& val);
	
	//Is there stuff 
	bool isEmpty();
};



//******************Implementation for Node Class***************************

//Default Constructor 
//Sets info to T object
//Sets next to ptr
template <class T>
Node<T>::Node(string val, Node<T> * nextptr, Node<T> * prevptr)
{
	key = val;
	next = nextptr;
	prev = prevptr;
}

//*****************Implementation for LL class*******************

//Default Constructor
//Sets count to 0
//Sets head and tail to NULL
template <class T>
LL<T>::LL()
{
	sentinel = new Node<T>("zero", sentinel, sentinel);

	count = 0;

}//End Default

//CopyConstructor
//Calls copylist
template <class T>
LL<T>::LL(const LL<T> &otherLL)
{
	sentinel = new Node<T>("$$$", sentinel, sentinel);

	count = 0;

	copyList(otherLL);
}//End Copy Constructor


//Copies the items in one linked list to another linked list
//Creates new linked list using push-back function 
template <class T>
void LL<T>::copyList(const LL<T> & listToCopy)
{
	count = 0;
	this->clear();
	//Creates otherCurrent to traverse the Linked List
	Node<T> *otherCurrent = listToCopy.sentinel->next;

	while (otherCurrent != listToCopy.sentinel)
	{
		Insert_rear(otherCurrent->key);

		otherCurrent = otherCurrent->next;
	}

}//End CopyList

//Destructor 
//Calls function clear
template<class T>
LL<T>::~LL()
{
	//cout << "Entering destructor" << endl;
	clear();
	//cout << "Exiting destructor" << endl;
}//End Destructor


//Adds new Node to end of list
//Updates count
template<class T>
void LL<T>::Insert_rear(string val)
{
	try{

		Node<T> *addMe = new Node<T>(val); //New Node to be added to the LL

		//If head points to NULL, list empty head points to addMe
		if (size() == 0)
		{
			Insert_front(val);
		}
		else if (size() == 1)
		{

			addMe->next = sentinel;
			addMe->prev = sentinel->next;
			sentinel->next->next = addMe;
			sentinel->prev = addMe;
			count++;
		}
		else if (size() >1)
		{
			//Node current used to traverse LL
			Node<T> *current = sentinel->next;


			//Finding last element in LL
			while (current->next != sentinel)
			{
				current = current->next;
			}

			addMe->next = sentinel;
			addMe->prev = current;
			current->next = addMe;
			sentinel->prev = addMe;
			count++;
		}

	}

	//Catching error if could not create memory
	catch (bad_alloc)
	{
		cout << "Could not dynamically create memory" << endl;
		exit(1);
	}


}//End Insert Rear


//Adds item to front of LL
template<class T>
void LL<T>::Insert_front(T val)
{
	try{

		Node<T>*addMe = new Node<T>(val);

		if (size() == 0)
		{
			addMe->next = sentinel;
			addMe->prev = sentinel;
			sentinel->next = addMe;
			sentinel->prev = addMe;

		}
		else if (size() >= 1)
		{
			addMe->prev = sentinel;
			addMe->next = sentinel->next;
			sentinel->next = addMe;
			sentinel->next->prev = addMe;
			//InsertList(sentinel, sentinel->next, addMe);

		}

		count++;
	}

	//Catching error if could not create memory
	catch (bad_alloc)
	{
		cout << "Could not dynamically create memory" << endl;
		exit(1);
	}

}//End Insert_front


//Removes Last Element of LL
//Updates count
template <class T>
void LL<T>::erase_rear()
{
	//If there are elements in the LL
	if (size() != 0)
	{
		Node<T>*current = sentinel->next;//create Node to traverse LL

		//Finding last element of LL
		while (current->next != sentinel)
		{

			current = current->next;
		}

		current->prev->next = sentinel;
		sentinel->prev = current->prev;
		delete current;

		count--;//deincrement count 
	}

} //End erase_rear


//Returns size of LL
template<class T>
int LL<T>::size() const
{
	return count;
}//End Size

//Clears the LL and destorys dynamically created memory 
template <class T>
void LL<T>::clear()
{
	//cout << "Entered member function LL::clear()" << endl;

	//If the head is pointing to NULL
	if (sentinel->next = sentinel)
	{
		//cout << "\tList is already empty, nothing to do here.\n";
		//cout << "List is pointing to itself\n";
	}
	else
	{
		Node<T> *current = sentinel->next;//Creates a Node to traverse LL
		int deleteCount = 0; //counts items deleted from List

		//Traverses LL and deletes elements
		while (current != sentinel)
		{
			current = current->next;
			erase_front();
			deleteCount++;
			//count--;
		}

		//sentinel->next = sentinel;
		//sentinel->prev = sentinel;

		//	cout << "\t" << deleteCount << " nodes were deallocated and removed from the list.\n";
	}

	count = 0;
	//cout << "Exiting member function LL::clear()" << endl;
}//End Clear 

//Returns T element at position ndx of LL
template<class T>
T& LL<T>::at(int ndx)
{
	//Holds the error message
	string error = "";

	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{

			Node<T> *current = sentinel->next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->key);
		}
	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//end at


//Overload [] operator
//Return element T in position ndx
template<class T>
T& LL<T>::operator[](int ndx)
{
	string error = ""; //error message
	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{
			Node<T> *current = sentinel->next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->key);
		}

	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//End [] overload

//Return element T in position ndx
//cannot modify element T
template<class T>
T& LL<T>::at(int ndx) const
{
	//Holds the error message
	string error = "";

	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{

			Node<T> *current = sentinel->next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->key);
		}
	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//end at

//Overload [] operator
//Return Element in positio ndx
//Cannot modify element T
template<class T>
T& LL<T>::operator[](int ndx) const
{

	string error = ""; //error message
	try{

		if ((ndx <0) || (ndx > size()))
		{
			error = "Error, index value not valid";
			throw error;
		}
		else
		{
			Node<T> *current = sentinel - .next;
			int tempC = 0;

			while (tempC != ndx)
			{
				current = current->next;
				tempC++;
			}

			return (current->key);
		}

	}

	catch (string error)
	{
		cout << "Index out of bounds error at index:" << ndx << endl;
		throw error;
	}

}//End overload [] operator 

//Overload assignment operator 
template <class T>
const LL<T>& LL<T>::operator=(const LL<T> &rhsObj)
{
	//test to ensure that the left hand side argument and the right hand argument
	//are not the same object

	if (this != &rhsObj)
	{
		this->clear();

		sentinel->next = sentinel;
		sentinel->prev = sentinel;
		count = 0;

		//Calling copyList
		copyList(rhsObj);
	}

	return *this;
}// End Assignment overload assignment operator 


//Inserts a Node in a certain index
//Capacity and number elements incerases by 1
template <class T>
void LL<T>::Insert(int ndx, T key)
{
	try{

		Node<T> * addMe = new Node<T>(key);

		if (ndx == 0)
		{
			Insert_front(key);
		}
		else
		{
			Node<T> *current = sentinel->next;
			int counter = 1;

			while ((current != sentinel) && (counter != ndx))
			{
				current = current->next;
				counter++;
			}

			addMe->next = current;
			addMe->prev = current->prev;
			current->prev = addMe;
			current->prev->next = addMe;

			count++;
		}

	}

	//Catching error if could not create new memory 
	catch (bad_alloc)
	{
		cout << "Could not dynamically create memory" << endl;
		exit(1);
	}

}


//Erase Node a certain index
//Capacity and number of elements decreases by 1
template <class T>
void LL<T>::erase(int index)
{
	Node<T> *current = sentinel->next;

	if (size() != 0)
	{
		return;
	}
	else if (index == 0)
	{
		erase_front();
	}
	else
	{
		int counter = 1;

		while (current->next != sentinel && counter != index)
		{
			current = current->next;
			counter++;
		}

		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		count--;
	}
}

//Erasing front Node
//Capacity and number of elements decreases by 1
template <class T>
void LL<T>::erase_front()
{
	if (size() >= 1)
	{
		Node<T> *current = sentinel->next;

		sentinel->next = current->next;
		current->next->prev = sentinel;
	}

}

//Cap method: returns size of LL
template <class T>
int LL<T>::cap() const
{
	return count;
}

//Printing coef and degree of each element
template<class T>
void LL<T>::print()
{
	Node<T> *current = sentinel->next;

	while (current != sentinel)
	{
		cout << "Printing element in list "<<(current->key) <<endl;
		current = current->next;
	}

}

template<class T>
bool LL<T>::inList(const string& val)
{ 
	Node<T> *current = sentinel->next;
	if (!isEmpty())
	{

		while (current != sentinel)
		{
			if (current->key == val)
			{
				return true;
			}
			else{

				current = current->next;
			}
		}
	}

	return false; 
}

//Remove specific value in list 
template<class T>
void LL<T>::eraseVal(const string& val)
{
	Node<T> *current = sentinel->next;
	bool flag = true;

	if (!isEmpty())
	{
		while (current != sentinel && flag)
		{
			if (current->key == val)
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
				flag = true;
			}
			else
			{
				current = current->next;
			}
		}
	}
}

template<class T> 
bool LL<T>::isEmpty()
{
	if (size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif