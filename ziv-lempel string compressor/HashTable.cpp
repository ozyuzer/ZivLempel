/*The class code is taken from CS300 lecture slides and modified according to usage*/
#include "HashTable.h"
using namespace std;

template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound, int size)
	: ITEM_NOT_FOUND( notFound ), table(size), currentSize(0) {}

template <class HashedObj>
int HashTable<HashedObj>::size_of()
{		
	return table.size();
}

template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const
{
	int p = hashf(x,table.size()); // current position

	while( table[p].info != EMPTY && table[p].element != x ) {
		p += 1;  // linear probing.
	}

	if( p >= table.size()){            // perform the mod
		p = p - table.size();                // if necessary
	}
	
	return p;
}

template <class HashedObj>
void HashTable<HashedObj>::makeEmpty()
{
	for(int i=0; i<table.size(); i++)
	{
		table[i].info = EMPTY;
	}
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
	return table[currentPos].info == ACTIVE;
}

template<class HashedObj>
int HashTable<HashedObj>::ret_position(const HashedObj &x)
{
	return findPos(x);
}

		
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
	int currentPos = findPos(x);

	if( isActive(currentPos))
		table[currentPos].info = DELETED;
}

template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) const
{
	
	int currentPos = findPos(x);

	if (isActive( currentPos )) 
		return table[currentPos].element; 
 
	return ITEM_NOT_FOUND;

}

template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x )
{
	// Insert x as active
	int currentPos = findPos(x);

	if(isActive(currentPos))
		return;

	table[currentPos] = HashEntry(x,ACTIVE);

	//enlarge the hash table if necessary 
	if( ++currentSize >= table.size()/2)
	{
		rehash();
	}
}


template <class HashedObj>
void HashTable<HashedObj>::rehash()
{
	std::vector<HashEntry> oldArray = table;

	// Create new double-sized, empty table
	table.resize(( 2 * oldArray.size() ));

	for( int j = 0; j < table.size(); j++ )
		table[j].info = EMPTY;

	// Copy table over
	currentSize = 0;
	for( int i = 0; i < oldArray.size(); i++ )
	{
		if( oldArray[i].info == ACTIVE)
			insert( oldArray[i].element );
	}
}


int hashf(const node & key,int tableSize)
{
	int p = key.code;

	if(p>= tableSize)
		p = p % tableSize;
	return p;
}

bool operator !=(const node& rhs, const node& lhs){
	return ((rhs.key != lhs.key));
}