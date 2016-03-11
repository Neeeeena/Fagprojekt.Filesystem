//============================================================================
// Name        : FilesystemDummy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Filesystem.h"
#include <libssh/libsshpp.hpp>
#include <libssh/libssh.h>
using namespace std;

int main() {
	Filesystem* myFileSystem = new Filesystem();
	myFileSystem->Insert("/","File1.txt",8);
	cout <<  myFileSystem->Lookup("/","File1.txt") << "\n";
	myFileSystem->Remove("/","File1.txt");
	cout <<  myFileSystem->Lookup("/","File1.txt") << "\n";
	  ssh_session my_ssh_session;
	  int rc;
	  my_ssh_session = ssh_new();
	  if (my_ssh_session == NULL)
	    exit(-1);
	  ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "localhost");
	  rc = ssh_connect(my_ssh_session);
	  if (rc != SSH_OK)
	  {
	    fprintf(stderr, "Error connecting to localhost: %s\n",
	            ssh_get_error(my_ssh_session));
	    exit(-1);
	  }
	  ssh_disconnect(my_ssh_session);
	  ssh_free(my_ssh_session);

	return 0;

}
