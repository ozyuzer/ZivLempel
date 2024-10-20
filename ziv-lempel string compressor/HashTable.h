#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
//#include "pair_key.h"

using namespace std;

struct node{
	string key;
	int code;

	node(string _key,int _code): // constructor for ease of use
		key(_key),code(_code){}

	node() : key(""), code(-1) {} // default constructor
};

template <class HashedObj>
class HashTable
{
	public:
		explicit HashTable( const HashedObj & notFound, int size);
		HashTable(const HashTable & rhs) : 
			ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND ), table(rhs.table), currentSize(rhs.currentSize) {}

		const HashedObj & find( const HashedObj & x ) const;

		void makeEmpty();
		void insert(const HashedObj & x);
		void remove(const HashedObj & x);
		int size_of(); //returns the size of the table 
		int ret_position(const HashedObj & x ); //returns the position

		const HashTable & operator=(const HashTable & rhs);

		enum EntryType {ACTIVE, EMPTY, DELETED};
	private:
		struct HashEntry
		{
			HashedObj element;
			EntryType info;

			HashEntry(const HashedObj & e = HashedObj( ), EntryType i = EMPTY)
			: element(e), info(i) { }
		};
            
		vector<HashEntry> table; //std::vector<HashEntry> table;
        int currentSize;
        const HashedObj ITEM_NOT_FOUND;

        bool isActive(int currentPos) const;
		int findPos(const HashedObj & x) const;
        void rehash();
};

int hashf(const pair_key & key,int tableSize);


#include "hashTable.cpp"
#endif
