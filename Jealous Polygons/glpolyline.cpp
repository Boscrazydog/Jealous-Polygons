#include "glpolyline.h"


polyline::polyline() {
	
}

polyline::polyline(std::vector<glpoint> p) {
	pline = p;
}

void polyline::addpt(glpoint p) {
	pline.push_back(p);
}

void polyline::addpt(double x, double y) {
	glpoint p(x, y);
	pline.push_back(p);
}

void polyline::addpt(double x, double y, double z) {
	glpoint p(x, y,z);
	pline.push_back(p);
}

void polyline::erase() {
	pline.clear();
}
void polyline::draw() {
	glBegin(GL_LINE_STRIP);
	for (std::vector<glpoint>::iterator it = pline.begin(); it != pline.end(); it++) {
		glVertex2d((*it).ptx(), (*it).pty());
	}
	glEnd();
}


std::vector<glpoint> polyline::getpline() {
	return pline;
}