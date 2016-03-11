/*
 * Filesystem.cpp
 *
 *  Created on: 09/03/2016
 *      Author: Nina
 */
#include <string>
#include <iostream>
#include <map>
#include "Filesystem.h"



using namespace std;

Filesystem::Filesystem() {
	// TODO Auto-generated constructor stub

}

Filesystem::~Filesystem() {
	// TODO Auto-generated destructor stub
}

int Filesystem::Lookup(string tree,string filename){
	auto it = files.find(tree+filename);
	if(it!=files.end()){
		return it->second;
	}
	else return -1;
}

string Filesystem::Insert(string tree, string filename, int size){
	files.insert(pair<string,int>(tree+filename,size));
	return tree+filename;
}

std::string Filesystem::Remove(string tree, string filename){
	auto it = files.find(tree+filename);
	if(it!=files.end()){
		files.erase(it);
		return tree+filename;
	}
	return "";

}
