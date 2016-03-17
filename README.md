# Dictionary-Spell-Checking-Project-
Implements a hash table to spell check a document 

HashTable class details:

I implemented my hash table using the chaining method. I have a HashTable class with an array of linked list (LL) strings.
created a private data member ptr, which is a pointer to a LL full of strings (LL<string>). The other private data members include:
table size, number of elements, an internal hash function, and the number of collisions. In my HashTable constructor I set the table
size to 47087 as the default parameter and then set ptr to point to a dynamic array filled with LL<string> values. The other public
functions include: insert value, remove value, bool contains key, and accessor methods for number of elements, table size, and
collisions. My internal hash function uses Horner’s rule and computes the summation of k[i] * 37^i.  In the insert value function, I
call the hash function and then mod that value by the table size to get an index for the array. I then call the linked list’s method
Insert_rear(key) to add a new node to the linked list. If the linked list at the index is not empty, I then add one to the collision
count because the more than one element hashed to the same index. To remove an element from the list, I pass in a key, hash the key
and mod by the table size to get an index. I then call the bool contains function to check if the value is in the list. If there is
key in the hash table, I call the function in my linked class that traverses the list and then deletes the node. My bool contains
function works by calling the hash function and moding by the table size to get an index. I then call the inList(key) function in my
LL class which traverses the list, compares keys and returns true if the element is in the linked list.
	
How to run the project: 

The first command line argument is the personal dictionary and the second argument is the spell checking text file. The third
argument is the personal dictionary file. In main I test if there are arguments and then get the file paths of these arguments from
the command line. If there is a third command argument, I call my loadDictionayData function with a bool value set to true and pass
the file path for the third argument. Else, I call the loadDictionaryData function with the bool value set to false and a null string
as the personal dictionary file path. In my loadDictionaryData functions, I open the files and then hash the values from the
dictionary into the hash table. If there is a personal dictionary, I open the file and then hash the values in this dictionary to the
hash table. If the hash table already contains a value from the dictionary file, I do not add repeats in the table. I then check each
word in the spell checking file with the values in the hash table. If a value does not exist in the hash table, I convert the word to
lowercase to account for uppercase words. If that word is still not in the hash table, I print out the misspelled word and line
number. I have a summary report function that prints the results to the screen and a log file. 


