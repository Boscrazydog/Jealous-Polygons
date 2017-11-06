#include "glmenu.h"
#include "Utils.h"

menu::menu() {
	optnum = 0;
}

void menu::getslen() {
	int i;
	slen = 0;
	for (i = 0; i < optnum; i++) {
		if (slen <= options[i].length())
			slen = options[i].length();
	}
}

menu::menu(glpoint p,std::string a, std::string b) {
	optnum = 2;
	copt = 0;
	options[0] = a;
	options[1] = b;
	getslen();
	center = p;
}

menu::menu(glpoint p, std::string a, std::string b, std::string c) {
	optnum = 3;
	copt = 0;
	options[0] = a;
	options[1] = b;
	options[2] = c;
	getslen();
	center = p;
}

menu::menu(glpoint p, std::string a, std::string b, std::string c, std::string d) {
	optnum = 4;
	copt = 0;
	options[0] = a;
	options[1] = b;
	options[2] = c;
	options[3] = d;
	getslen();
	center = p;
}

menu::menu(glpoint p, std::string a, std::string b, std::string c, std::string d, std::string e) {
	optnum = 5;
	copt = 0;
	options[0] = a;
	options[1] = b;
	options[2] = c;
	options[3] = d;
	options[4] = e;
	getslen();
	center = p;
}


void menu::displaytext() {
	int i,r = center.pty() + (30 * optnum) - 40;
	for (i = 0; i < optnum; i++) {
		if (i == copt)
			glColor3f(0.0f, 0.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2d(center.ptx() - (slen * 8) + 10, r);
		printstring(options[i]);
		r += -60;
	}
	
}

void menu::displayselection() {
	if (copt == 0) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2d(center.ptx() - (slen * 8)+1, center.pty() + (30 * optnum) - 1);
		glVertex2d(center.ptx() - (slen * 8)+1, center.pty() + (30 * optnum) - 59);
		glVertex2d(center.ptx() + (slen * 8)-1, center.pty() + (30 * optnum) - 59);
		glVertex2d(center.ptx() + (slen * 8)-1, center.pty() + (30 * optnum) - 1);
		glEnd();

	}
	else if (copt == 1) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);		
		glVertex2d(center.ptx() - (slen * 8) + 1, center.pty() + (30 * optnum) - 61);
		glVertex2d(center.ptx() - (slen * 8) + 1, center.pty() + (30 * optnum) - 119);
		glVertex2d(center.ptx() + (slen * 8) - 1, center.pty() + (30 * optnum) - 119);
		glVertex2d(center.ptx() + (slen * 8) - 1, center.pty() + (30 * optnum) - 61);
		glEnd();
	}

	else if (copt == 2) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2d(center.ptx() - (slen * 8) + 1, center.pty() + (30 * optnum) - 121);
		glVertex2d(center.ptx() - (slen * 8) + 1, center.pty() + (30 * optnum) - 179);
		glVertex2d(center.ptx() + (slen * 8) - 1, center.pty() + (30 * optnum) - 179);
		glVertex2d(center.ptx() + (slen * 8) - 1, center.pty() + (30 * optnum) - 121);
		glEnd();
	}

	else if (copt == 3) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2d(center.ptx() - (slen * 8) + 1, center.pty() + (30 * optnum) - 181);
		glVertex2d(center.ptx() - (slen * 8) + 1, center.pty() + (30 * optnum) - 239);
		glVertex2d(center.ptx() + (slen * 8) - 1, center.pty() + (30 * optnum) - 239);
		glVertex2d(center.ptx() + (slen * 8) - 1, center.pty() + (30 * optnum) - 181);
		glEnd();
	}

	else if (copt == 4) {
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POLYGON);
		glVertex2d(center.ptx() - (slen * 8) + 1, center.pty() + (30 * optnum) - 241);
		glVertex2d(center.ptx() - (slen * 8) + 1, center.pty() + (30 * optnum) - 299);
		glVertex2d(center.ptx() + (slen * 8) - 1, center.pty() + (30 * optnum) - 299);
		glVertex2d(center.ptx() + (slen * 8) - 1, center.pty() + (30 * optnum) - 241);
		glEnd();
	}
}


void menu::display() {
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2d(center.ptx() - (slen * 8), center.pty() + (30 * optnum));
	glVertex2d(center.ptx() - (slen * 8), center.pty() - (30 * optnum));
	glVertex2d(center.ptx() + (slen * 8), center.pty() - (30 * optnum));
	glVertex2d(center.ptx() + (slen * 8), center.pty() + (30 * optnum));
	glEnd();
	displayselection();
	displaytext();
}

void menu::moveup() {
	if (copt == 0)
		copt = optnum-1;
	else
		copt--;
}

void menu::movedown() {
	if (copt == optnum-1)
		copt = 0;
	else
		copt++;
}

int menu::select() {
	return (copt);
}