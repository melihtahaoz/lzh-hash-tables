#define _VARIADIC_MAX 10//i need more function parameter in this homework


#include <iostream>
#include <fstream>
#include "hashanddict.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std;

string decomp(HashTable<Dictionary>& comphashtable,int prev, int& currenthashidx,int currnum,string prevstr, string *arr) {//this is the complex algorithm part
	string notfound;//empty string				
	string currstr = arr[currnum];
	string printprev=arr[prev];
	prevstr = arr[prev];
	if (arr[currnum] == notfound)//if current number is not inside the array,this means the current index of array is empty 
		prevstr += prevstr[0];//if the node of the array empty, insert the first char of the elements to at the end of the element
	else
		prevstr +=currstr[0];//if the current number is inside the array create new code for the dicitonary
	comphashtable.insert(Dictionary(prevstr, currenthashidx));//insert Dictionary object into the hash table
	arr[currenthashidx] = prevstr;//insert the current hash table codes inside the array 
	currenthashidx++;
	return comphashtable.find(Dictionary(printprev, currnum)).keyss;//find the initial keys inside the dicitionary
}

int main()
{
	string infilename= "compout.txt",outfilename="decompout.txt";
	ifstream inFile;
	ofstream outFile;
	inFile.open(infilename.c_str());
	
	if (inFile.is_open()) {//if file can open
		outFile.open(outfilename.c_str());
		//char ch;
		Dictionary compdict;
		HashTable<Dictionary> comphashtable(compdict, 4096);
		vector <int> allnums;
		string line;
		int nums;
		while(inFile >>nums){
			if (nums > 4096)//the codes cannot be greater than 4096
				return 0;
			allnums.push_back(nums);
		}
		string keysarray[4096];
		for (int codesofascii = 0; codesofascii <= 255; codesofascii++) {//inser all ascii codes inside the hash table and the array
			string str(1, char(codesofascii)); //convert ascii codes to string
			Dictionary newdict(str, codesofascii);
			keysarray[codesofascii] = char(codesofascii);
			comphashtable.insert(newdict);
		}
		//do not forget if check for the comprass is empty
		int currenthashidx = 256;

		int prevnum = allnums[0];
		//outFile << char(prevnum);
		string pstr = string(1, char(prevnum));
	//	string prevstr ;
		//comphashtable.insert(Dictionary(prevstr, 256));
		int currentnum=0;
		//string currstr;//= pstr+ pstr;
		for (int k = 1; k <= allnums.size(); k++)
		{
			if(k != allnums.size())//for taking last element do not update the currentnum
				currentnum = allnums[k];
			outFile<<decomp(comphashtable, prevnum, currenthashidx, currentnum, pstr, keysarray);//write the keyss into the decompout file
			prevnum = currentnum;//update the previous code
			pstr = keysarray[prevnum];//update the previous keys
		}

		outFile.close();
		inFile.close();
	}

	return 0;

}
