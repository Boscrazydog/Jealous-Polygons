#include "glpoints.h"
#include "glvector.h"
#include <cmath>

glpoint glpoint::operator+ (glvector v) {
	return (v.add(*this));
}
glvector glpoint::operator- (glpoint p) {
	return (glvector(*this, p));
}

bool glpoint::operator==(glpoint p) {
	if (x == p.ptx() && y == p.pty() && z == p.ptz())
		return true;
	else return false;
}

bool glpoint::operator!=(glpoint p) {
	if (x != p.ptx() || y != p.pty() || z != p.ptz())
		return true;
	else return false;
}
glpoint::glpoint() {
	x = 0;
	y = 0;
	z = 0;
}

glpoint::glpoint(GLdouble a, GLdouble b) {
	x = a;
	y = b;
	z = 0;
}
glpoint::glpoint(GLdouble a, GLdouble b,GLdouble c) {
	x = a;
	y = b;
	z = c;
}

GLdouble glpoint::ptx() {
	return x;
}

GLdouble glpoint::pty() {
	return y;
}

GLdouble glpoint::ptz() {
	return z;
}

void glpoint::ptxyz(GLdouble& xx, GLdouble& yy, GLdouble& zz) {
	xx = x;
	yy = y;
	zz = z;
}

void glpoint::change(double xa, double ya) {
	x = xa;
	y = ya;
}

void glpoint::change(double xa, double ya,double za) {
	x = xa;
	y = ya;
	z = za;
}

void glpoint::draw() {
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}




