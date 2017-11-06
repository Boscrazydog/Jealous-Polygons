#include "avatar.h"
#include "glvector.h"
#include <cmath>


const double MOVEAMT = .5;

avatar::avatar() {
	health = 100;
	xdim = ydim = radius = 0;
}

avatar::avatar(double x, double y) {
	health = 1000;
	radius = 10;
	xdim = x;
	ydim = y;
	body.change(radius, 40, glpoint(xdim / 2, ydim / 12), 0);
	setaim(xdim/2, ydim);
	center = body.getcenter();
}

void avatar::setaim(double mouseX, double mouseY) {
	glpoint p(mouseX, mouseY);
	glvector v(center, p);
	v = v.norm() * radius;
	glpoint np = center + v;
	std::vector<glpoint> pv;
	pv.push_back(center);
	pv.push_back(np);
	aim = pv;
}

void avatar::move_up() {
	if (center.pty() <= (ydim - radius)) {
		body.changecenter(glpoint(center.ptx(), center.pty() + MOVEAMT));
		center = glpoint(center.ptx(), center.pty() + MOVEAMT);
	}
}

void avatar::move_up_right() {
	if (center.ptx() <= xdim - radius && center.pty() <= ydim - radius) {
		double xmove = (MOVEAMT / sqrt(2));
		double ymove = (MOVEAMT / sqrt(2));
		body.changecenter(glpoint(center.ptx() + xmove, center.pty() + ymove));
		center = glpoint(center.ptx() + xmove, center.pty() + ymove);
	}
	else if (center.ptx() <= xdim - radius) {
		move_right();
	}
	else if (center.pty() <= ydim - radius) {
		move_up();
	}
}

void avatar::move_right() {
	if (center.ptx() <= xdim - radius) {
		body.changecenter(glpoint(center.ptx() + MOVEAMT, center.pty()));
		center = glpoint(center.ptx() + MOVEAMT, center.pty());
	}
}

void avatar::move_down_right() {
	if (center.ptx() <= xdim - radius && center.pty() >= radius) {
		double xmove = (MOVEAMT / sqrt(2));
		double ymove = (MOVEAMT / sqrt(2));
		body.changecenter(glpoint(center.ptx() + xmove, center.pty() - ymove));
		center = glpoint(center.ptx() + xmove, center.pty() - ymove);
	}
	else if (center.ptx() <= xdim - radius) {
		move_right();
	}
	else if (center.pty() >= radius) {
		move_down();
	}
}

void avatar::move_down() {
	if (center.pty() >= radius) {
		body.changecenter(glpoint(center.ptx(), center.pty() - MOVEAMT));
		center = glpoint(center.ptx(), center.pty() - MOVEAMT);
	}
}

void avatar::move_down_left() {
	if (center.ptx() >= radius && center.pty() >= radius) {
		double xmove = (MOVEAMT / sqrt(2));
		double ymove = (MOVEAMT / sqrt(2));
		body.changecenter(glpoint(center.ptx() - xmove, center.pty() - ymove));
		center = glpoint(center.ptx() - xmove, center.pty() - ymove);
	}
	else if (center.ptx() >= radius) {
		move_left();
	}
	else if (center.pty() >= radius) {
		move_down();
	}
}

void avatar::move_left() {
	if (center.ptx() >= radius) {
		body.changecenter(glpoint(center.ptx() - MOVEAMT, center.pty()));
		center = glpoint(center.ptx() - MOVEAMT, center.pty());
	}
}

void avatar::move_up_left() {
	if (center.ptx() >= radius && center.pty() <= ydim - radius) {
		double xmove = (MOVEAMT / sqrt(2));
		double ymove = (MOVEAMT / sqrt(2));
		body.changecenter(glpoint(center.ptx() - xmove, center.pty() + ymove));
		center = glpoint(center.ptx() - xmove, center.pty() + ymove);
	}
	else if (center.ptx() >= radius) {
		move_left();
	}
	else if (center.pty() <= ydim - radius) {
		move_up();
	}
}

bullet avatar::shoot() {
	std::vector<glpoint> v = aim.getpline();
	return bullet(v[1], aim,xdim,ydim);
}

void avatar::draw() {
	glColor3f(1 - (health / 1000.00),(health / 1000.00), 0.0);
	body.drawf();
	glColor3f(0.0f, 0.0f, 0.0f);
	aim.draw();
	body.draw();
}

glpoint avatar::getcenter() {
	return center;
}

int avatar::gethealth() {
	return (health / 10);
}

void avatar::sethealth(int i) {
	health = i;
}

void avatar::takedam(int dam) {
	health += -dam;
}

bool avatar::alive() {
	if (health > 0) return true;
	else return false;
}