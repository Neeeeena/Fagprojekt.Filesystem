//============================================================================
// Name        : FilesystemDummy.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Filesystem.h"
#include <libssh/libssh.h>
#include "ExternFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include "Password.h"
using namespace std;

int main()
{
  ssh_session my_ssh_session;
  int rc;
  string password;
  ExternFunctions* externs = new ExternFunctions();
  Password* getpass = new Password();
  // Open session and set options
  my_ssh_session = ssh_new();
  if (my_ssh_session == NULL)
    exit(-1);
  ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "s144477@login.gbar.dtu.dk");
  // Connect to server
  rc = ssh_connect(my_ssh_session);
  if (rc != SSH_OK)
  {
    fprintf(stderr, "Error connecting to localhost: %s\n",
            ssh_get_error(my_ssh_session));
    ssh_free(my_ssh_session);
    exit(-1);
  }
  // Verify the server's identity
  // For the source code of verify_knowhost(), check previous example
  if (externs->verify_knownhost(my_ssh_session) < 0)
  {
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
    exit(-1);
  }
  // Authenticate ourselves
  password = getpass->getpass("Password: ",true);
  const char * c = password.c_str();
  rc = ssh_userauth_password(my_ssh_session, NULL, c);
  if (rc != SSH_AUTH_SUCCESS)
  {
    fprintf(stderr, "Error authenticating with password: %s\n",
            ssh_get_error(my_ssh_session));
    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);
    exit(-1);
  }
  externs -> show_remote_files(my_ssh_session);
  ssh_disconnect(my_ssh_session);
  ssh_free(my_ssh_session);
}

