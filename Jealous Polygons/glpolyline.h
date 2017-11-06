#ifndef glpolyline_h
#define glpolyline_h

#include "globalgl.h"
#include "Utils.h"
#include "glpoints.h"

#include <vector>

class polyline {
public:
	polyline();
	polyline(std::vector<glpoint>);
	void addpt(glpoint);
	void addpt(double, double);
	void addpt(double, double, double);
	void erase();

	void draw();
	std::vector <glpoint> getpline();
	
private:
	std::vector<glpoint> pline;
};
#endif 