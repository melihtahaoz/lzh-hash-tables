//#pragma once
#ifndef hashanddict_H_
#define hashanddict_H_
#include <string>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
template <class HashedObj>
class HashTable
{
	//friend class Dictionary;
public:
	explicit HashTable(const HashedObj& notFound, int size = 4096) :
		arrayvec(nextPrime(size)), currentSize(0)
	{};
	const HashTable(const HashTable& rhs) : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), arrayvec(rhs.arrayvec), currentSize(rhs.currentSize) {
		//makeEmpty();
	}

	const HashedObj& find(const HashedObj& x) const {//find the hash tabe object , if not found return ITEM_NOT_FOUND
		int currentPos = findPos(x);
		if (isActive(currentPos))
			return arrayvec[currentPos].element;
		return   ITEM_NOT_FOUND;
	}

	void insert(const HashedObj& x) {//insert the hash table object
		// Insert x as active
		int currentPos = findPos(x);
		if (isActive(currentPos))
			return;
		arrayvec[currentPos] = HashEntry(x, ACTIVE);

	}
	void remove(const HashedObj& x) { //remove the hash table object
		int currentPos = findPos(x);
		if (isActive(currentPos))
			arrayvec[currentPos].info = DELETED;
	}

	const HashTable& operator=(const HashTable& rhs) {//the eqaul symbol make a shallow copy of rhs object 
		(*this) = rhs;
	};
	int nextPrime(int n)
	{
		if (n % 2 == 0)
			n++;
		for (; !isPrime(n); n += 2)
			;
		return n;
	}
	bool isPrime(int n)
	{
		if (n == 2 || n == 3)
			return true;
		if (n == 1 || n % 2 == 0)
			return false;
		for (int i = 3; i * i <= n; i += 2)
			if (n % i == 0)
				return false;
		return true;
	}

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;

		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY) : element(e), info(i) { } //constructor of hashEntry object
	};

	vector<HashEntry> arrayvec; //this vector will keep the data of HashEntry object
	int currentSize;//size of hash table
	const HashedObj ITEM_NOT_FOUND;

	bool isActive(int currentPos) const {// Return true if currentPos exists and is active
		return arrayvec[currentPos].info == ACTIVE;
	}

	int makehash(const  HashedObj& k, int size) const {//hash the object in the hash table, it will use in findPos function
		string newstr = k.keyss;
		if (newstr.length() == 1)
			return (unsigned char)(newstr[0]);
		else
			return 256;
	}

	int findPos(const HashedObj& x) const {//return position of the object
		int currentPos = makehash(x, arrayvec.size());

		while (arrayvec[currentPos].info != EMPTY && arrayvec[currentPos].element != x)
		{
			currentPos++;  // add the difference
			if (currentPos >= arrayvec.size())  // perform the mod if it isnecessary
				currentPos -= arrayvec.size();
		}

		return currentPos;
	}
	//bool operator !=(const ) {}//this not worked so i overload the oprerand inside the dictionary
};

class Dictionary {
public:
	Dictionary() { //default constructor for dictionary class
		keyss = "";
		code = 0;
	}
	Dictionary(string key1, int code1) {//constructor for dictionary class
		keyss = key1;
		code = code1;
	}
	bool operator ==(const Dictionary& r) const { //check whehter the right hand side value equal to lhs value. If their keys are equal return true
		if ((*this).keyss == r.keyss)
			return true;
		else
			return false;
	}
	bool operator !=(const Dictionary& r)const {//check whehter the right hand side value equal to lhs value. If their keys are not equal return true. 
		//The overload will use inside the Findpos dunction 
		//if ((*this).keyss == r.keyss)//	return false;//else//	return true;
		return !((*this) == r);
	}
	//string getkey() {//	return keyss;//}//int getcode() {//	return code;//}
//private:
	string keyss;
	int code;
};
#endif 