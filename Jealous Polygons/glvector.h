#ifndef glvector_h
#define glvector_h

#include "globalgl.h"
#include "Utils.h"
#include "glpoints.h"

class glvector {
public:
	glpoint operator+(glpoint);
	glvector operator+(glvector);
	double operator*(glvector);
	glvector operator*(double);
	bool operator==(glvector);
	glvector operator-(glvector);
	glvector();
	glvector(glpoint, glpoint);
	glvector(double, double);
	glvector(double, double, double);
	double dot(glvector);
	glvector cross(glvector);
	glvector add(glvector);
	glpoint add(glpoint);
	glvector subtract(glvector);
	glvector perp();
	glvector scale(double);
	glvector norm();
	double length();
	glpoint getmid(glpoint);

private:
	double x, y, z;
	
};



#endif
