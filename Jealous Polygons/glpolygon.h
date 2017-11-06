#ifndef glpolygon_h
#define glpolygon_h
#include <cmath>
#include "glpoints.h"
#include <vector>

class polygon {
public:
	polygon();
	polygon(double, int, glpoint, double);

	void changesides(int);
	void changeradius(double);
	void changecenter(glpoint);
	void changeangle(double);
	void change(double, int, glpoint, double);

	void draw();
	void drawf();

	std::vector <glpoint> getpolygon();
	glpoint getcenter();


private:

	void getcoords();
	int sides;
	double radius, angle;
	glpoint center;
	std::vector<glpoint> polygonpts;

};



#endif
