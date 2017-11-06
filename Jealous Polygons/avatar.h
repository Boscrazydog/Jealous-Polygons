#ifndef avatar_H
#define avatar_H

#include "glpolyline.h"
#include "glpolygon.h"
#include "bullet.h"

class avatar {
public:
	avatar();
	avatar(double, double);

	void setaim(double,double);

	void move_up();
	void move_up_right();
	void move_right();
	void move_down_right();
	void move_down();
	void move_down_left();
	void move_left();
	void move_up_left();

	bullet shoot();

	void draw();

	glpoint getcenter();
	int gethealth();
	void sethealth(int);

	void takedam(int);
	bool alive();

private:
	int health;
	polyline aim;
	polygon body;
	glpoint center;
	double xdim, ydim;
	double radius;
};

#endif
