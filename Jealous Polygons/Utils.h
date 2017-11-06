#ifndef DESUTILS_H
#define DESUTILS_H
#include <string>

extern void setWorldWin(GLdouble left, GLdouble right,
	GLdouble bottom, GLdouble top);

extern void setViewPort(GLint left, GLint right, GLint bottom, GLint top);

void printstring(std::string);

void delay(int);
#endif