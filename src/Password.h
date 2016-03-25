/*
 * Password.h
 *
 *  Created on: Mar 25, 2016
 *      Author: nina
 */
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#ifndef PASSWORD_H_
#define PASSWORD_H_

class Password {
public:
	Password();
	virtual ~Password();
	std::string getpass(const char*, bool);
	int getch();
};

#endif /* PASSWORD_H_ */
