//
//  DecompressionProgram.cpp
//  Ziv-Lempel String Decompressor
//
//  Created by Alkim Ozyuzer on 01.12.2022.
//
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "HashTable.h"

using namespace std;

void fillDict(node *d){ //the function maps ASCII characters into the vector.
	for(int i=0; i<256; i++){
		string str = "";
		str += char(i);
		d[i].key = str;
		d[i].code = i;
	}
}

int main() {
	// Open the input and output files
	ifstream fin("compout.txt");
	ofstream fout("decompout.txt");

	/*
	// Create empty hashtable
	HashTable<node> hashtable(notFound,TABLE_SIZE);

	// Insert the first 256 entries into the hashtable
	for (int i = 0; i < 256; i++) {
		string str=""; //empty string to insert char
		str = char(i);

		node temp(str,i); // new temporary pair_key 
		hashtable.insert(temp); // insert the pair_key into the hashtable
	}
	*/

	/*
  // Read the input codes one by one
  int code;
  fin >> code;
  string str = hashtable.GetString(code);
  fout << str;
  string prev_str = str;
  while (fin >> code) {
    if (code == hashtable.GetCode("")) {
      // The code is not in the hashtable, so create a new string by adding the previous string to itself
      str = prev_str + prev_str;
    } else {
      // The code is in the hashtable, so get the corresponding string
      str = hashtable.GetString(code);
    }
    fout << str;
    if (hashtable.GetCode("") != 4096) hashtable.Insert(prev_str + str[0], hashtable.GetCode(""));
    prev_str = str;
  }*/

	node dict[4096];
	node decompressed;

	fillDict(&dict[0]);

	string fileStr;
	string prefix , prev_prefix="";

	int prev_num=0;

	while(getline(fin,fileStr)){
		stringstream ss;
		ss<<fileStr;
		int code;
		while(ss>>code){
			if(dict[code].key != ""){ //if it is already in dictionary
				if(prev_prefix != ""){
					prefix = prev_prefix + dict[code].key[0];

					int m = 0;
					while(dict[m].key != ""){
						m++;
					}
					dict[m].key = prefix;
					dict[m].code = m;
				}

				decompressed = dict[code];
				fout << decompressed.key;

			}
			else{
				prefix = prev_prefix + prev_prefix[0];
				dict[code].key = prefix;
				dict[code].code = code;

				decompressed = dict[code];

				fout << decompressed.key; //write to the output file
				
			}

			prev_num = code;
			prev_prefix = dict[prev_num].key;
		}
	}

	// Close the files
	fin.close();
	fout.close();

	return 0;
}