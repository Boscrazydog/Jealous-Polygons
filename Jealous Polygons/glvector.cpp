#include "glvector.h"
#include <cmath>


glpoint glvector::operator+(glpoint p) {
	return((*this).add(p));
}

glvector glvector::operator+(glvector v) {
	return((*this).add(v));
}

double glvector::operator*(glvector v) {
	return ((*this).dot(v));
}

glvector glvector::operator*(double n) {
	return (scale(n));
}

bool glvector::operator==(glvector v) {
	if (v.x == x && v.y == y && v.z == z || -v.x == x && -v.y == y && -v.z == z)
		return true;
	else return false;
}
glvector glvector::operator-(glvector v) {
	return((*this).subtract(v));
}

glvector::glvector() {
	x = y = z = 0;
}

glvector::glvector(glpoint a, glpoint b) {
	x = b.ptx() - a.ptx();
	y = b.pty() - a.pty();
	z = b.ptz() - a.ptz();
}

glvector::glvector(double a, double b) {
	x = a;
	y = b;
	z = 0;
}

glvector::glvector(double a, double b, double c) {
	x = a;
	y = b;
	z = c;
}

double glvector::dot(glvector v) {
	return(x * v.x + y * v.y + z * v.z);
}

glvector glvector::cross(glvector v) {
	return (glvector(y * v.z - z * v.y, z * v.x  - x * v.z, x * v.y  - y * v.x ));
}
glvector glvector::add(glvector v) {
	return (glvector(x + v.x, y + v.y, z + v.z ));
}
glpoint glvector::add(glpoint p) {
	return(glpoint(p.ptx() + x, p.pty() + y, p.ptz() + z));
}
glvector glvector::subtract(glvector v) {
	return (glvector(x - v.x, y - v.y, z - v.z ));
}
glvector glvector::perp() {
	return (glvector(-y, x));
}

glvector glvector::norm() {
	double a = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	glvector v = *this;
	return(v.scale(1 / a));
}

glvector glvector::scale(double n) {
	glvector v(x*n, y*n, z*n);
	return v;
}

double glvector::length() {
	return (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
}

glpoint glvector::getmid(glpoint p) {
	glvector tmp = scale(.5);
	return (tmp + p);
}

