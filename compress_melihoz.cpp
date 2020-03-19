#include <iostream>
#include <fstream>
#include "hashanddict.h"
#include <string>
using namespace std;

int main()
{
	string filename = "compin.txt";
	ifstream inFile;
	string outfilename = "compout.txt";
	ofstream outFile;
	inFile.open(filename.c_str());
	if (inFile.is_open()) {//if the file is open
		char ch;
		Dictionary compdict;
		HashTable<Dictionary> comphashtable(compdict, 4096);
		string allchars = "";//keep all chars in a string
		while (!inFile.eof()) //eof returns true if next character
		{
			inFile.get(ch); //get command reads next character //unless you are at the end of the file
			allchars += ch;
		}
		allchars = allchars.substr(0, allchars.length() - 1);//the loop above insert an element twice into the allchars string
		string str;
		for (int codesofascii = 0; codesofascii <= 255; codesofascii++) {//inser all ascii codes inside the hash table
			str = string(1,char(codesofascii)); //convert ascii to string
			Dictionary newdict(str, codesofascii);
			comphashtable.insert(newdict);//insert dictionary to inside the hash table
		}

		outFile.open(outfilename.c_str());
		int currenthashidx = 256;
		int substrlength = 2;//this is the initial size of the string which will insert to the hash table object called newdict 
		int updatedstrlenght = 1;//this is the size of the output string
		Dictionary notfounddic;//empty dictionay object for checking wheter the finded dictionary is empty or not
		for (int i = 0; i < allchars.length(); i++) {
			string substr = allchars.substr(0, substrlength);
			if (notfounddic == comphashtable.find(Dictionary(substr, currenthashidx))) {//if the item not found
				if (currenthashidx < 4096)
					comphashtable.insert(Dictionary(substr, currenthashidx));//after 4096 stop inserting dicitionary
				outFile << comphashtable.find(Dictionary(allchars.substr(0, updatedstrlenght), currenthashidx)).code << " ";
				allchars = allchars.substr(updatedstrlenght, allchars.length() - 1);//delete old used part of string
				substrlength = 2;//reinitialize the substrlength and updatedstrlenght beacuse new string will be search for inserting inside the dictionary
				updatedstrlenght = 1;
				currenthashidx++;
				i = 0;
			}
			else {//if item found
				substrlength++;
				updatedstrlenght++;
				//continue;
			}
		}
		outFile << comphashtable.find(Dictionary(allchars, currenthashidx)).code << "";
		inFile.close();//close the file
		outFile.close();//close the file
	}

	return 0;
}

