#include "bullet.h"


bullet::bullet() {
	active = false;
	xdim = ydim = 0;
}

bullet::bullet(glpoint p, polyline l, double x,double y) {
	xdim = x;
	ydim = y;
	position = p;
	std::vector<glpoint> v = l.getpline();
	trajectory = glvector(v[0], v[1]);
	trajectory = trajectory.norm();
	active = true;
}

bullet::bullet(glpoint p, glvector v, double x, double y) {
	xdim = x;
	ydim = y;
	position = p;
	trajectory = v;
	trajectory = trajectory.norm();
	active = true;
}


bool bullet::isactive() {
	return active;
}

glpoint bullet::getposition() {
	return position;
}

void bullet::deactivate() {
	active = false;
}

void bullet::move() {
	double moveamt = 2; // changes speed
	position = position + trajectory * moveamt;
	if (position.ptx() > xdim || position.ptx() < 0 || position.pty() > ydim || position.pty() < 0)
		active = false;
}

void bullet::draw() {
	if(active)
		position.draw();
}