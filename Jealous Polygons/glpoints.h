#ifndef glpoints_h
#define glpoints_h
#include "globalgl.h"
#include "Utils.h"

class glvector;

class glpoint {
	friend class glvector;
public:
	bool operator==(glpoint);
	bool operator!=(glpoint);
	glpoint operator+(glvector);
	glvector operator-(glpoint);
	glpoint();
	glpoint(GLdouble, GLdouble);
	glpoint(GLdouble, GLdouble, GLdouble);
	GLdouble ptx();
	GLdouble pty();
	GLdouble ptz();
	void ptxyz(GLdouble&, GLdouble&, GLdouble&);

	void change(double, double);
	void change(double, double, double);
	void draw();

private:
	GLdouble x, y, z;
};

#endif