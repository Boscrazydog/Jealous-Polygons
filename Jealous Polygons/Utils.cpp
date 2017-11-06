#include "globalgl.h"
#include "Utils.h"
#include <fstream>
#include <ctime>

using namespace std;

void setWorldWin(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
}

void setViewPort(GLint left, GLint right, GLint bottom, GLint top) {
	glViewport(left, bottom, right - left, top - bottom);
}

void printstring(std::string s) {
	int i = 0;
	while (i < s.length()) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		i++;
	}
}

#if defined(WIN32)
void delay(int ms) {
	Sleep(ms);
}
#else
void delay(int ms) {
	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = 1000000 * (ms % 1000);
	nanosleep(&ts, NULL);
}
#endif