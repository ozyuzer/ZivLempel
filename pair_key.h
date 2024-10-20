#ifndef PAIR_KEY_H
#define PAIR_KEY_H

#include <iostream>
using namespace std;
//This class is for overloading the operators == and != in a more simplistic way

class pair_key
{
public:
	pair_key(string a, int b= 0);
	pair_key();

	string key;
	int code;
};

pair_key::pair_key(string a, int b)
{
	key = a;
	code = b;
}

pair_key::pair_key() {}

bool operator ==(const pair_key& rhs, const pair_key& lhs)
{
	return ((rhs.key == lhs.key));
}

bool operator !=(const pair_key& rhs, const pair_key& lhs)
{
	return ((rhs.key != lhs.key));
}

#endif
