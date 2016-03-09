//============================================================================
// Name        : FilesystemDummy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Filesystem.h"
using namespace std;

int main() {
	Filesystem* myFileSystem = new Filesystem();
	myFileSystem->Insert("/","File1.txt",8);
	cout <<  myFileSystem->Lookup("/","File1.txt") << "\n";
	myFileSystem->Remove("/","File1.txt");
	cout <<  myFileSystem->Lookup("/","File1.txt") << "\n";
	return 0;

}
