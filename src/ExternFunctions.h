/*
 * ExternFunctions.h
 *
 *  Created on: Mar 25, 2016
 *      Author: nina
 */
#include <libssh/libssh.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef EXTERNFUNCTIONS_H_
#define EXTERNFUNCTIONS_H_

class ExternFunctions {
public:
	ExternFunctions();
	virtual ~ExternFunctions();
	int verify_knownhost(ssh_session session);
	int show_remote_files(ssh_session session);
};

#endif /* EXTERNFUNCTIONS_H_ */
