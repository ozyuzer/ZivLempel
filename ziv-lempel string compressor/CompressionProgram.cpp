//
//  CompressionProgram.cpp
//  Ziv-Lempel String Compressor
//
//  Created by Alkim Ozyuzer on 01.12.2022.
//
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "HashTable.h"

using namespace std;

int main(){
	// Open the input and output files
	ifstream fin("compin.txt");
	ofstream fout("compout.txt");

	int TABLE_SIZE = 4096;
	node dummy("-100&",-100);

	// Create empty hashtable
	HashTable<node> hashtable(dummy,TABLE_SIZE);

	// Insert the first 256 entries into the hashtable
	for (int i = 0; i < 256; i++) {
		string str=""; //empty string to insert char
		str = char(i);

		node temp(str,i); // new temporary pair_key 
		hashtable.insert(temp); // insert the pair_key into the hashtable
	}

	// Read the input string character by character

	string str;
	char c;
	node comp("",-1); // dummy-empty node

	while (fin.get(c)){
		str += c;
	}

	while(str.length()>0){

		///////////////////////////

		int idx = 1;
		node current(str.substr(0,idx),0); //

		while( (hashtable.find(current) != dummy) && idx<str.length()){
			idx++;
			current.key = str.substr(0,idx);
		}
		int pos;
        if(idx > str.length()){ //if the prefix not in dict then add it to the dictionary
			if(hashtable.find(current) != dummy){
				node temp(str,0);
				pos = hashtable.ret_position(temp);
                comp = node(str, pos);
                str = "";
            }
            else{
				node temp(str.substr(0,idx-1),0);
				pos = hashtable.ret_position(temp);
                comp = node(str.substr(0,idx-1),pos);
                str = str.substr(idx-1);
            }
        }
        else{
            node temp(str.substr(0,idx-1),0);
			pos = hashtable.ret_position(temp);
            comp = node(str.substr(0,idx-1),pos);
            hashtable.insert(current);
            current.code = hashtable.ret_position(current);
            str = str.substr(idx-1);
        }
        fout << comp.code << " "; //write to the output file
		//////////////////////
	}

	// Close the files
	fin.close();
	fout.close();

	return 0;
}
