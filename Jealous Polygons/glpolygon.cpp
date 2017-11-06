#include "glpolygon.h"

polygon::polygon() {
	radius = 0;
	angle = 0;
	sides = 0;
	center = glpoint();
}

polygon::polygon(double r, int s, glpoint c, double a) {
	sides = s;
	radius = r;
	center = c;
	angle = a;
	getcoords();
}

void polygon::changesides(int i) {
	sides = i;
	polygonpts.clear();
	getcoords();
}

void polygon::changeradius(double d) {
	radius = d;
	polygonpts.clear();
	getcoords();
}

void polygon::changecenter(glpoint p) {
	center = p;
	polygonpts.clear();
	getcoords();
}

void polygon::changeangle(double d) {
	angle = d;
	polygonpts.clear();
	getcoords();
}

void polygon::change(double r, int s, glpoint c, double a) {
	sides = s;
	radius = r;
	angle = a;
	center = c;
	polygonpts.clear();
	getcoords();
}

std::vector <glpoint> polygon::getpolygon() {
	return polygonpts;
}

void polygon::draw() {
	glBegin(GL_LINE_LOOP);
	for (std::vector<glpoint>::iterator it = polygonpts.begin(); it != polygonpts.end(); it++) {
		glVertex2d((*it).ptx(), (*it).pty());
	}
	glEnd();
}

void polygon::drawf() {
	glBegin(GL_POLYGON);
	for (std::vector<glpoint>::iterator it = polygonpts.begin(); it != polygonpts.end(); it++) {
		glVertex2d((*it).ptx(), (*it).pty());
	}
	glEnd();
}

glpoint polygon::getcenter() {
	return center;
}


void polygon::getcoords() {
	double pi = 3.14159265359;
	int i;
	double x, y;
	for (i = 0; i < sides; i++) {
		x = radius* cos(angle) + center.ptx();
		y = radius* sin(angle) + center.pty();
		polygonpts.push_back(glpoint(x, y));
		angle += 2 * pi / sides;
	}
}