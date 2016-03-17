/*
Caroline Pattillo 
Dictionary Project 
*/


#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "LL.h"
#include "hash.h"

using namespace std;

void loadDictionaryData(vector<string> &a, int &numWordsChecked, int &mispelledWords, int &lineNumber, int &numCollisions, int &sizeTable, string = "", string = "", string = "", bool thirdArugment =false);

void summaryReport(vector<string> &a, int numWordsChecked, int mispelledWords, int lineNumber, int numCollisions, int sizeTable, ostream& os = cout);

int main(int argc, char *argv[])
{

	try
	{

		int numWordsChecked = 0; //Total number of words checked 
		int mispelledWords = 0;  //Total number of mispelled words
		int lineNumber = 0;		//Line number of mispelled words
		int numberCollisions = 0; //Number of collisions in the hashed table
		int sizeOfTable = 0; //The size of table 
		
		vector<string> a;

		string badArgMessage = "";

		//Checks to make command line has an argument 
		if (argc < 2)
		{
			badArgMessage = "There is no argument for the file";
			throw badArgMessage;
		}
		else
		{

			string inputDataFileName(argv[1]);//Declaring first command argument as a string (Dictionary)

				cout << "There are 2 argument" << endl;
				string textCheckingFile(argv[2]); //Declaring the second command argument as a string (personal text file)
				//cout << "Printing out File" << textCheckingFile << endl;
				
				bool thirdArgument = false; 

				if (argc == 4)
				{
					cout << "we have 3 arguments" << endl;
					string personalDictionary(argv[3]);
					thirdArgument = true;
					loadDictionaryData(a, numWordsChecked, mispelledWords, lineNumber, numberCollisions, sizeOfTable, inputDataFileName, textCheckingFile, personalDictionary, thirdArgument);
				}
			//string to store name and path of output file
			string outputFileName = "";

			//output file stream object
			std::ofstream outFile;

			//this statement makes the input file name and the output file name exactly the same
			outputFileName = inputDataFileName;

			//this statement adds an extension to the output file name so it is no longer 
			//exactly the same as the input file
			outputFileName += ".log";

			//cout << "The name of the file is: " << inputDataFileName << endl;//printing out file name 
			if (!thirdArgument)
			{
				string tempString = ""; 

				loadDictionaryData(a, numWordsChecked, mispelledWords, lineNumber, numberCollisions, sizeOfTable, inputDataFileName, textCheckingFile,  tempString, thirdArgument);//calling method to load data into MineRecord vector vMr
			}
			/********** Priniting Out Summary Report *********/

			summaryReport(a, numWordsChecked, mispelledWords, lineNumber, numberCollisions, sizeOfTable); 

			
			//************* File stuff*************
			//open the output data file
			outFile.open(outputFileName.c_str());

			//test to make sure the file opened successfully
			if (!outFile)
			{
				//output file failed to open
				string errMessage = "Inside function main()\nThe file named: ";
				errMessage += outputFileName;
				errMessage += " failed to open, cannot call the report function :-(";

				throw errMessage;
			}
			else
			{
				//call the report function and have the output go to a file
				//cout << "Calling function to send report to a file, output file name is:\n";
				//cout << outputFileName << endl;
				summaryReport(a, numWordsChecked, mispelledWords, lineNumber, numberCollisions, sizeOfTable, outFile);

				//cout << "Output to file is complete.\n";

				outFile.close();
			}

		}
	}

	catch (string errorMessage)
	{
		cout << errorMessage << endl;
	}

	system("pause"); //keeps window open
	return 0;
}

//Populating MineRecord vector with data from the data file. 
void loadDictionaryData(vector<string> &a, int &numWordsChecked, int &mispelledWords, int &lineNumber, int &numCollisions, int &sizeTable, string mFileName, string ptextFile,string personalDictionary, bool thirdArgument)
{
	try
	{
		int recordCount = 0;
		int recordsAccordingToFile = 0;
		string commentsToIgnore = "";
		string oneLine = "";
		string fileOpenError = "";
		ifstream inFile(mFileName.c_str()); //opening file
		ifstream textFile(ptextFile.c_str()); //open personal file 

		if (!inFile && !textFile)
		{
			inFile.close();
			textFile.close();
			fileOpenError = "Input file containing mine data: ";
			fileOpenError += mFileName;
			fileOpenError += " failed to open.";
			throw fileOpenError;
		}
		else
		{
			string nameText = ""; 
			string tFind = "";
			string find = "";
			int delimeter = 0;
			int number = 0; 
			string temp = "";

			HashTable table; 
			getline(inFile, find);

			while (getline(inFile, find))
			{
				delimeter = find.find("/");
				temp = find.substr(0, delimeter);
				//cout << temp << endl;
				//number++;
				table.insert(temp);
			}


			if (thirdArgument)
			{
				string PersonalWords = "";
				string wordPersonal = ""; 
				
				int inPersonalDic = 0; 

				ifstream PDictionary(personalDictionary.c_str());

				if (!PDictionary)
				{
					PDictionary.close();
					fileOpenError = "Input file containing the personal dictionary ";
					fileOpenError += personalDictionary;
					fileOpenError += " failed to open.";
					throw fileOpenError;
				}
				else
				{
					while (getline(PDictionary, PersonalWords))
					{
						std::stringstream names(PersonalWords);
						inPersonalDic++;

						while (names >> wordPersonal)
						{
							if (!(table.contains(wordPersonal)))
							{
								table.insert(wordPersonal);
							}
						}

					}
				}
			}

			numCollisions = table.numCollisions(); 
			sizeTable = table.TS();

			while (getline(textFile, tFind))
			{
				std::stringstream iss(tFind);

				lineNumber++;
				while (iss >> nameText)
				{
					//cout << "This the line from the file: " << nameText << endl;
					numWordsChecked++; 

					if (table.contains(nameText))
					{
						//cout << "The table contained the following: " << nameText << endl;
					}
					else 
					{
						nameText[0] = nameText[0] + 32; 
						if (table.contains(nameText))
						{
							//cout << "Contains, but had to convert to lowercase: " <<nameText<< endl;
						}
						else{

							//cout << "Not in the hash table" << endl;
							string linN;
							ostringstream convert;
							convert<< lineNumber; 
							linN = convert.str();
							mispelledWords++;
							nameText[0] -= 32;
							string temp = "Mispelled Word: " + nameText + " " + "Line number: " + linN +"\n"; 
							a.push_back(temp);
						}
					}
				}
			}


			cout << endl;

			inFile.close();
			textFile.close();
		}

	}

	catch (string sErr)
	{
		cout << "error in loadMineData function\n";
		cout << sErr << endl;

		//throw sErr; //do not rethrow for P1
	}


} //END function loadDictionaryData


void summaryReport(vector<string> &a, int numWordsChecked, int mispelledWords, int lineNumber, int numCollisions, int sizeTable, ostream& os) 
{
	os << "***********Printing Summary Report" << endl;
	os << "The total number of words checked in text file is: "<< numWordsChecked << endl;
	os << "The total number of mispelled words is: " << mispelledWords << endl;
	os << "The number of collisions in the hash table is: " << numCollisions<< endl;
	os << "The table size is: " << sizeTable << endl; 

	for (int i = 0; i < a.size(); i++)
	{
		os << a.at(i); 
	}

}



