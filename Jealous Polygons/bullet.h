#ifndef bullet_H
#define bullet_H

#include "glpolyline.h"
#include "glvector.h"

class bullet {
	friend class avatar;
public:
	bullet();
	bullet(glpoint, polyline,double,double);
	bullet(glpoint, glvector, double, double);

	void changetrajectory(glvector); //for ricochet possibilities
	
	glpoint getposition();

	bool isactive();

	void deactivate();
	void move();
	void draw();

private:
	glpoint position;
	glvector trajectory;
	bool active;
	double xdim;
	double ydim;
};

#endif