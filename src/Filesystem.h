/*
 * Filesystem.h
 *
 *  Created on: 09/03/2016
 *      Author: Nina
 */
#include <map>
using namespace std;
#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

class Filesystem {
private :
	//simple only saves datasize
	map<string,int> files;
public:
	Filesystem();
	virtual ~Filesystem();
	int Lookup(string, string);
	string Insert(string, string,int);
	string Remove(string,string);
};

#endif /* FILESYSTEM_H_ */
