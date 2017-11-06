#include "npc.h"
#include "glvector.h"
#include <cmath>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TRIANGLE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
triangle::triangle() {
	active = false;
	health = 100; // change health
	radius = 30;
	angle = 0;
}

triangle::triangle(glpoint p) {
	active = true;
	health = 100; // change health
	radius = 30;
	angle = 0;
	shape = polygon(radius, 3, p, angle);
}

void triangle::move(avatar& a) {
	double moveamt = .40; //change speed
	double pi = 3.14159265359;
	glvector v(shape.getcenter(), a.getcenter());
	v = v.norm() * moveamt;
	shape.changecenter(shape.getcenter() + v);
	if (angle >= 2 * pi)
		angle = 0;
	else angle += pi / 500; //change rotation speed
	shape.changeangle(angle);
}

void triangle::draw() {
	glColor3f(1 - (health / 100.00), (health / 100.00), 0.0);
	shape.drawf();
	glColor3f(0.0f, 0.0f, 0.0f);
}

void triangle::deactivate() {
	active = false;
}

glpoint triangle::getcenter() {
	return (shape.getcenter());
}

bool triangle::detectbullet(bullet& b) { 
	glvector v(b.getposition(), shape.getcenter());
	if (v.length() <= radius) {
		health += -50; //change damage
		b.deactivate();
		if (health <= 0) {
			active = false;
			return true;
		}
	}
	return false;
}

void triangle::detectcollision(avatar& a) {
	glvector v(a.getcenter(), shape.getcenter());
	if (v.length() <= 30 * .75) { //To account for noncircular nature of triangles
		a.takedam(100);  //Change for triangle damage
		active = false;
	}
}

bool triangle::isactive() {
	return active;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<SQUARE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

square::square() {
	active = false;
	health = 100;
	radius = 0;
}

square::square(glpoint& c, glpoint& d) {
	double pi = 3.14159265359;
	active = true;
	health = 100;
	radius = 30;
	destination = d;
	shape = polygon(radius, 4, c, pi/4);
	center = shape.getcenter();
}

glpoint square::getcenter() {
	return center;
}

glpoint square::getdes() {
	return destination;
}

void square::setdestination(glpoint& p) {
	destination = p;
}

void square::move() {
		glvector v = center - destination;
		v = v.norm() * .3; //change speed;
		glpoint np = center + v;
		shape.changecenter(np);
		center = np;
}

bool square::detectbullet(bullet & b) {
	glvector v(b.getposition(), center);
	if (v.length() <= radius) {
		health += -20; //change damage
		b.deactivate();
		if (health <= 0) {
			active = false;
			return true;
		}
	}
	return false;
}

void square::detectcollision(avatar& a) {
	glvector v(a.getcenter(), shape.getcenter());
	if (v.length() <= 30 * .75) {
		a.takedam(100);  //Change damage
		active = false;
	}
}

void square::draw() {
	glColor3f(1 - (health / 100.00), (health / 100.00), 0.0);
	shape.drawf();
	glColor3f(0.0f, 0.0f, 0.0f);
}
void square::deactivate() {
	active = false;
}
bool square::isactive() {
	return active;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Connection >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

connection::connection() {
	active = false;
}

connection::connection(square & s1, square & s2) {
	p1 = s1.getcenter();
	p2 = s2.getcenter();
	polyline p;
	p.addpt(p1);
	p.addpt(p2);
	line = p;
	active = true;
}

connection::connection(glpoint& pa1, glpoint& pa2) {
	p1 = pa1;
	p2 = pa2;
	polyline p;
	p.addpt(p1);
	p.addpt(p2);
	line = p;
	active = true;
}

void connection::draw() {
	glColor3f(1.0f, 0.0f, 0.0f);
	line.draw();
	glColor3f(0.0f, 0.0f, 0.0f);
}

void connection::deactivate() {
	active = false;
}

bool connection::isactive() {
	return active;
}

void connection::detectcollision(avatar & a) {
	glvector v1 = p2 - p1;
	glvector v2 = p2 - a.getcenter();
	double l2 = pow(v1.length(),2);
	double t = max(0, min(1, v1 * v2 / l2));
	glpoint proj = p2 + v1 * t;
	glvector v3 = a.getcenter() - proj;
	if (v3.length() <= 10)
		a.takedam(2);

}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< PENTAGON >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

pentagon::pentagon() {
	active = false;
	health = 0;
}

pentagon::pentagon(glpoint & p, avatar& a) {
	double pi = 3.14159265359;
	active = true;
	shape = polygon(30, 5, p, 0);
	angle = 0;
	health = 100;
	center = shape.getcenter();
	trajectory = glvector(center, a.getcenter());
	trajectory = trajectory.norm();
}

void pentagon::reflect(int i) { // 1 = top , 2 = right , 3 = bottom, 4 = left border
	glvector bperp; //border norm
	switch (i) {
	case 1: bperp = glvector(0, -1); break;
	case 2: bperp = glvector(-1, 0); break;
	case 3: bperp = glvector(0, 1); break;
	case 4: bperp = glvector(1, 0); break;
	}
	trajectory = trajectory -  bperp * (trajectory*bperp) * 2; 
}

void pentagon::move() {
	double moveamt = 1; //change speed
	double pi = 3.14159265359;
	glvector v = trajectory * moveamt;
	center = center + v;
	shape.changecenter(center);
	if (angle >= 2 * pi)
		angle = 0;
	else angle += pi / 500; //change rotation speed
	shape.changeangle(angle);
}

void pentagon::draw() {
	glColor3f(1 - (health / 100.00), (health / 100.00), 0.0);
	shape.drawf();
	glColor3f(0.0f, 0.0f, 0.0f);
}

bool pentagon::detectbullet(bullet& b) {
	glvector v(b.getposition(), shape.getcenter());
	if (v.length() <= 30) {
		health += -40; //change damage
		b.deactivate();
		if (health <= 0) {
			active = false;
			return true;
		}
	}
	return false;
}

void pentagon::detectcollision(avatar& a) {
	glvector v(a.getcenter(), center);
	if (v.length() <= 30) {
		a.takedam(100);  //Change for pentagon damage
		active = false;
	}
}

void pentagon::deactivate() {
	active = false;
}

bool pentagon::isactive() {
	return active;
}

glpoint pentagon::getcenter() {
	return center;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Hexagon >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

hexagon::hexagon() {
	active = false;
	health = 0;
	shooting = false;
	shoottime = 0;
	movetime = 0;
}

hexagon::hexagon(glpoint p, double x, double y) { 
	active = true;
	health = 100;
	shape = polygon(30, 6, p, 0);
	center = shape.getcenter();
	shooting = false;
	shoottime = 0;
	xdim = x;
	ydim = y;
	movetime = 0;
}

void hexagon::move(avatar& a) {
	double moveamt = .40; //change speed
	movetime++;
	if (shooting) {
		if (shoottime >= 500) { // change duration
			shoot(a);
			shoottime = 0;
			shooting = false;
		}
		else
			shoottime++;
	}
	else {
		if (movetime > 250) {
			movetime = 0;
			movetype = rand() % 8;
		}
		switch (movetype) {
		case 0: move_up(moveamt); break;
		case 1: move_up_right(moveamt); break;
		case 2: move_right(moveamt); break;
		case 3: move_down_right(moveamt); break;
		case 4: move_down(moveamt); break;
		case 5: move_down_left(moveamt); break;
		case 6: move_left(moveamt); break;
		case 7: move_up_left(moveamt); break;
		default:
			break;
		}
	}
	if (hexbullet.isactive()) {
		hexbullet.move();
	}
}

void hexagon::draw(avatar &a) {
	glColor3f(1 - (health / 100.00), (health / 100.00), 0.0);
	shape.drawf();
	glColor3f(0.0f, 0.0f, 0.0f);
	if (shooting) {
		std::vector<glpoint> p = shape.getpolygon();
		glBegin(GL_LINE_STRIP);
		glVertex2d(p[0].ptx(), p[0].pty());
		glVertex2d(p[3].ptx(), p[3].pty());
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex2d(p[1].ptx(), p[1].pty());
		glVertex2d(p[4].ptx(), p[4].pty());
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex2d(p[2].ptx(), p[2].pty());
		glVertex2d(p[5].ptx(), p[5].pty());
		glEnd();
		glColor3f(shoottime * 1.0 / 500,1-((500 - shoottime) * 1.0 / 500) / 500, 0);
		glBegin(GL_LINE_STRIP);
		glVertex2d(center.ptx(), center.pty());
		glVertex2d(a.getcenter().ptx(), a.getcenter().pty());
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	if (hexbullet.isactive())
		glColor3f(1.0f, 0.0f, 0.0f);
		hexbullet.draw();
		glColor3f(0.0f, 0.0f, 0.0f);
}

void hexagon::setshoot() {
	shooting = true;
}

void hexagon::shoot(avatar& a) {
	glvector v(center, a.getcenter());
	hexbullet = bullet(center, v, xdim, ydim);
}

bool hexagon::detectbullet(bullet& b) {
	glvector v(b.getposition(), shape.getcenter());
	if (v.length() <= 30) {
		health += -20; //change damage
		b.deactivate();
		if (health <= 0) {
			active = false;
			return true;
		}
	}
	return false;
}

void hexagon::detectcollision(avatar& a) {
	glvector v(a.getcenter(), center);
	if (v.length() <= 30) {
		a.takedam(100);  //Change for hexagon damage
		active = false;
	}
}

void hexagon::detectbulletcollision(avatar& a) {
	glvector v(hexbullet.getposition(), a.getcenter());
	if (v.length() <= 10) {
		a.takedam(100); //change damage
		hexbullet.deactivate();
	}
}

void hexagon::deactivate() {
	active = false;
}

void hexagon::deactivatebullet() {
	hexbullet.deactivate();
}

glpoint hexagon::getcenter() {
	return center;
}

bullet hexagon::getbullet() {
	return hexbullet;
}

bool hexagon::isactive() {
	return active;
}

void hexagon::move_up(double m) {
	if (center.pty() <= (ydim - 30)) {
		shape.changecenter(glpoint(center.ptx(), center.pty() + m));
		center = glpoint(center.ptx(), center.pty() + m);
	}
}

void hexagon::move_up_right(double m) {
	if (center.ptx() <= xdim - 30 && center.pty() <= ydim - 30) {
		double xmove = (m / sqrt(2));
		double ymove = (m / sqrt(2));
		shape.changecenter(glpoint(center.ptx() + xmove, center.pty() + ymove));
		center = glpoint(center.ptx() + xmove, center.pty() + ymove);
	}
	else if (center.ptx() <= xdim - 30) {
		move_right(m);
	}
	else if (center.pty() <= ydim - 30) {
		move_up(m);
	}
}

void hexagon::move_right(double m) {
	if (center.ptx() <= xdim - 30) {
		shape.changecenter(glpoint(center.ptx() + m, center.pty()));
		center = glpoint(center.ptx() + m, center.pty());
	}
}

void hexagon::move_down_right(double m) {
	if (center.ptx() <= xdim - 30 && center.pty() >= 30) {
		double xmove = (m / sqrt(2));
		double ymove = (m / sqrt(2));
		shape.changecenter(glpoint(center.ptx() + xmove, center.pty() - ymove));
		center = glpoint(center.ptx() + xmove, center.pty() - ymove);
	}
	else if (center.ptx() <= xdim - 30) {
		move_right(m);
	}
	else if (center.pty() >= 30) {
		move_down(m);
	}
}

void hexagon::move_down(double m) {
	if (center.pty() >= 30) {
		shape.changecenter(glpoint(center.ptx(), center.pty() - m));
		center = glpoint(center.ptx(), center.pty() - m);
	}
}

void hexagon::move_down_left(double m) {
	if (center.ptx() >= 30 && center.pty() >= 30) {
		double xmove = (m / sqrt(2));
		double ymove = (m / sqrt(2));
		shape.changecenter(glpoint(center.ptx() - xmove, center.pty() - ymove));
		center = glpoint(center.ptx() - xmove, center.pty() - ymove);
	}
	else if (center.ptx() >= 30) {
		move_left(m);
	}
	else if (center.pty() >= 30) {
		move_down(m);
	}
}

void hexagon::move_left(double m) {
	if (center.ptx() >= 30) {
		shape.changecenter(glpoint(center.ptx() - m, center.pty()));
		center = glpoint(center.ptx() - m, center.pty());
	}
}

void hexagon::move_up_left(double m) {
	if (center.ptx() >= 30 && center.pty() <= ydim - 30) {
		double xmove = (m / sqrt(2));
		double ymove = (m / sqrt(2));
		shape.changecenter(glpoint(center.ptx() - xmove, center.pty() + ymove));
		center = glpoint(center.ptx() - xmove, center.pty() + ymove);
	}
	else if (center.ptx() >= 30) {
		move_left(m);
	}
	else if (center.pty() <= ydim - 30) {
		move_up(m);
	}
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Polygon Prime >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

prime::prime() {
	active = false;
	health = 0;
	state = 0;
	angle = 0;
	time = 0;
	shootmode = false;
	shoottime = 0;
}

prime::prime(glpoint p, int x, int y) {
	state = 7;  //value is arbitrary
	shape = polygon(250, 3, p, 0); //three is arbitrary
	barrier = polygon(250, 60, p, 0);
	health = 10000;
	active = false;
	ocenter = p;
	center = p;
	angle = 0;
	xdim = x;
	ydim = y;
	time = 0;
	shootmode = false;
	shoottime = 0;
	recentermode = false;
}

void prime::recenter() {
	recentermode = true;
}

void prime::transform(avatar& a) {
	time = 0;
	int t = 0;
	do{
		t = (rand() % 4) + 3;
	} while (t == state);
	state = t;
	shape.changesides(state);
	if (state == 4)
		recenter();
	else if (state == 5)
		trajectory = glvector(center, a.getcenter()).norm();
	else if (state == 6)
		recenter();
}
void prime::activate() {
	(*this) = prime(ocenter, xdim,ydim);
	active = true;
}
void prime::act(avatar& a) {
	double pi = 3.14159265359;
	if (recentermode) {
		glvector v(center, ocenter);
		if (v.length() > .5)
			v = v.norm() * .5;
		center = center + v;
		shape.changecenter(center);
		barrier.changecenter(center);
		if (center == ocenter)
			recentermode = false;
	}
	if (state == 3) {
		double moveamt = .35; //change speed
		glvector v(center, a.getcenter());
		v = v.norm() * moveamt;
		center = center + v;
		shape.changecenter(center);
		barrier.changecenter(center);
		if (angle >= 2 * pi)
			angle = 0;
		else angle += pi / 500; //change rotation speed
		shape.changeangle(angle);
	}
	else if (state == 4) {
		int i;
		if (angle >= 2 * pi)
			angle = 0;
		else angle += pi / 2000; // change rotation speed
		shape.changeangle(angle);
		std::vector<glpoint> pv = shape.getpolygon();
		for (i = 0; i < 4; i++) {
			glvector v(center, pv[i]);
			v = v.norm() * 1000;
			glpoint tp = center + v;
			con[i] = connection(center, tp);
		}

	}
	else if (state == 5) {
		double moveamt = 1; //change speed
		glvector v = trajectory.norm() * moveamt;
		center = center + v;
		shape.changecenter(center);
		barrier.changecenter(center);
		if (angle >= 2 * pi)
			angle = 0;
		else angle += pi / 500; //change rotation speed
		shape.changeangle(angle);
		if (center.pty() > ydim - 250) {  //checks if at top border
			reflect(1);
		}
		if (center.ptx() > xdim - 250) { //checks if at right border
			reflect(2);
		}
		if (center.pty() < 250) { //checks if at bottom border
			reflect(3);
		}
		if (center.ptx() < 250) { //checks if at left border
			reflect(4);
		}
	}
	else if (state == 6) {
		int i;
		if (angle >= 2 * pi)
			angle = 0;
		else angle += pi / 500; //change rotation speed
		shape.changeangle(angle);
		for (i = 0; i < 6; i++) {
			if (bullets[i].isactive())
				bullets[i].move();
		}
		if (shootmode) {
			if (shoottime >= 500) { // change duration
				shoot(a);
				shoottime = 0;
				shootmode = false;
			}
			else
				shoottime++;
		}
		else {
			time++;
			if (time >= 500) {
				time = 0;
				shootmode = true;
			}
		}
	}
		
	
}

void prime::draw(avatar& a) {
	if (active) {
		glColor3f(1 - (health / 10000.00), (health / 10000.00), 0.0);
		shape.drawf();
		glColor3f(1.0f, 0.0f, 0.0f);
		barrier.draw();
		if (state == 4) {
			int i;
			for (i = 0; i < 4; i++) {
				if (con[i].isactive())
					con[i].draw();
			}
		}
		else if (state == 6) {
			int i;
			for (i = 0; i < 6; i++) {
				if (bullets[i].isactive())
					bullets[i].draw();
			}
			if (shootmode) {
				std::vector<glpoint> gv = shape.getpolygon();
				glColor3f(shoottime * 1.0 / 500, 1 - ((500 - shoottime) * 1.0 / 500) / 500, 0);
				for (i = 0; i < 6; i++) {
					glColor3f(shoottime * 1.0 / 500, 1 - ((500 - shoottime) * 1.0 / 500) / 500, 0);
					glBegin(GL_LINE_STRIP);
					glVertex2d(gv[i].ptx(), gv[i].pty());
					glVertex2d(a.getcenter().ptx(), a.getcenter().pty());
					glEnd();
				}
			}
		}
		glColor3f(0.0f, 0.0f, 0.0f);
	}
}

bool prime::detectbullets(bullet& b) {
	glvector v(b.getposition(), center);
	if (v.length() <= 250) {
		health += -20; //change damage
		b.deactivate();
		if (health <= 0)
			active = false;
		return true;
	}
	return false;
}

void prime::detectcollision(avatar& a) {
	glvector v(a.getcenter(), center);
	if (v.length() <= 250) {
		a.takedam(1);  //Change damage
	}
	if (state == 4) {
		int i;
		for (i = 0; i < 4; i++) {
			if(con[i].isactive())
				con[i].detectcollision(a);
		}
	}
	else if (state == 6) {
		int i;
		for (i = 0; i < 6; i++) {
			if (bullets[i].isactive()) {
				glvector v(bullets[i].getposition(), a.getcenter());
				if (v.length() <= 10) {
					a.takedam(100); //change damage
					bullets[i].deactivate();
				}
			}
		}
	}
}

void prime::reflect(int i) { // 1 = top , 2 = right , 3 = bottom, 4 = left border
	glvector bperp; //border norm
	switch (i) {
	case 1: bperp = glvector(0, -1); break;
	case 2: bperp = glvector(-1, 0); break;
	case 3: bperp = glvector(0, 1); break;
	case 4: bperp = glvector(1, 0); break;
	}
	trajectory = trajectory - bperp * (trajectory*bperp) * 2; 
}

void prime::shoot(avatar& a) {
	int i;
	std::vector<glpoint> gv = shape.getpolygon();
	for (i = 0; i < 6; i++) {
		glvector v(gv[i], a.getcenter());
		bullets[i] = bullet(gv[i], v, xdim, ydim);
	}
}

bool prime::isactive() {
	return active;
}