#include "globalgl.h"
#include "Utils.h"
#include "avatar.h"
#include "npc.h"
#include<time.h>
#include "glmenu.h"

using namespace std;

const int XDIM = 1920;
const int YDIM = 1080;

bool KEYS[256] = { false };


//Spawn Limits
const int NUMBLT = 10;
const int NUMTRI = 10;
const int NUMSQR = 4;
const int NUMPENT = 5;
const int NUMHEX = 6;

// Moving parts
glpoint SPAWN;
glpoint MOUSECOORD(XDIM/2, YDIM);
bullet BULLETS[NUMBLT];
triangle TRIANGLE[NUMTRI]; 
square SQUARE[NUMSQR];
connection CONNECTION[NUMSQR];
pentagon PENTAGON[NUMPENT];
hexagon HEXAGON[NUMHEX];
prime PRIME(glpoint(XDIM / 2, YDIM / 2), XDIM, YDIM);


//OTHER 
const double NPCRAD = 30; //radius of npcs
char STATE = 'm';  //States: m = menu, l = level menu, c = controls, 0 = endless mode, 1-5 = respective rounds, v = win, d = lose
int GPOINTS = 0;

menu MENU(glpoint(XDIM / 2,YDIM/2),"Full", "Level Select", "Endless", "Controls", "Exit");
menu LEVELM(glpoint(XDIM/2,YDIM/2),"The Peasantri", "The Tetrad", "Peppy Pentagons", "Six-Sided-Snipers", "Polygon Prime");

bool FULL = false;
bool GM = false;

avatar AVATAR(XDIM, YDIM);


int COUNT = 0;
int SPAWNS = 100;

//Destinations for squares
glpoint SDES[8] = { glpoint(NPCRAD, NPCRAD), glpoint(XDIM / 2, NPCRAD), glpoint(XDIM - NPCRAD, NPCRAD),glpoint(NPCRAD, YDIM / 2), glpoint(XDIM - NPCRAD, YDIM / 2),glpoint(NPCRAD, YDIM - NPCRAD),glpoint(XDIM / 2, YDIM - NPCRAD), glpoint(XDIM - NPCRAD, YDIM - NPCRAD) };


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


void KeyboardActions() {
	if (KEYS['w'] && KEYS['d']) AVATAR.move_up_right();
	else if (KEYS['w'] && KEYS['a'])  AVATAR.move_up_left();
	else if (KEYS['s'] && KEYS['d'])  AVATAR.move_down_right();
	else if (KEYS['s'] && KEYS['a'])  AVATAR.move_down_left();
	else if (KEYS['w'])  AVATAR.move_up();
	else if (KEYS['d'])  AVATAR.move_right();
	else if (KEYS['s'])  AVATAR.move_down();
	else if (KEYS['a'])  AVATAR.move_left();
}

void printinfo() {
	glRasterPos2d(XDIM / 120, 35 * YDIM / 36);
	string s = to_string(AVATAR.gethealth());
	printstring("Health:");
	printstring(s);
	glRasterPos2d(XDIM / 120, 34 * YDIM / 36);
	s = to_string(GPOINTS);
	printstring("Points:");
	printstring(s);
	if (STATE !='0') {
		s = to_string(SPAWNS);
		glRasterPos2d(XDIM / 120, 33 * YDIM / 36);
		printstring("Enemy spawns:");
		printstring(s);
	}
	if (GM) {
		glRasterPos2d(XDIM / 120, 32 * YDIM / 36);
		printstring("GM");
	}
}

void printvictoryscreen() {
	glRasterPos2d(15*XDIM / 36, 27*YDIM / 36);
	string s = to_string(GPOINTS);
	printstring("VICTORY!");
	glRasterPos2d(29 * XDIM / 72, 26 * YDIM / 36);
	printstring("Final Score:");
	printstring(s);
	glRasterPos2d(14 * XDIM / 36, 9 * YDIM / 36);
	printstring("Press 'm' to return to menu.");
}

void printdefeatscreen() {
	glRasterPos2d(15.5 * XDIM / 36, 27 * YDIM / 36);
	string s = to_string(GPOINTS);
	printstring("Defeat");
	glRasterPos2d(29 * XDIM / 72, 26 * YDIM / 36);
	printstring("Final Score:");
	printstring(s);
	glRasterPos2d(14 * XDIM / 36, 9 * YDIM / 36);
	printstring("Press 'm' to return to menu.");
}

void printcontrolscreen() {
	glColor3f(0.0f, 0.0f, 0.0f);
	// <<<<<<<<<<<<<<<<<<<<<< WASD >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	glRasterPos2d(9 * XDIM / 36, 12 * YDIM / 36);
	printstring("Movement");
	polygon sqr(30, 4, glpoint(9 * XDIM / 36, 9 * YDIM / 36), .78539816339); // pi / 4
	sqr.draw();
	glRasterPos2d(8.85 * XDIM / 36, 8.80 * YDIM / 36);
	printstring("A");
	sqr.changecenter(glpoint(10 * XDIM / 36, 9 * YDIM / 36));
	sqr.draw();
	glRasterPos2d(9.90 * XDIM / 36, 8.80 * YDIM / 36);
	printstring("S");
	sqr.changecenter(glpoint(11 * XDIM / 36, 9 * YDIM / 36));
	sqr.draw();
	glRasterPos2d(10.85 * XDIM / 36, 8.80 * YDIM / 36);
	printstring("D");
	sqr.changecenter(glpoint(10 * XDIM / 36, 10.75 * YDIM / 36));
	sqr.draw();
	glRasterPos2d(9.80 * XDIM / 36, 10.40 * YDIM / 36);
	printstring("W");
	sqr.changecenter(glpoint(16* XDIM / 36, 9 * YDIM / 36));
	sqr.draw();
	glRasterPos2d(15.85 * XDIM / 36, 8.75 * YDIM / 36);
	printstring("G");
	glRasterPos2d(15 * XDIM / 36, 11 * YDIM / 36);
	printstring("God Mode");
	sqr.changecenter(glpoint(21.5 * XDIM / 36, 9 * YDIM / 36));
	sqr.draw();
	glRasterPos2d(21.3 * XDIM / 36, 8.75 * YDIM / 36);
	printstring("M");
	glRasterPos2d(20.85 * XDIM / 36, 12 * YDIM / 36);
	printstring("Return");
	glRasterPos2d(20.65 * XDIM / 36, 11 * YDIM / 36);
	printstring("To Menu");
	polyline mouse;
	mouse.addpt(glpoint(14 * XDIM / 36, 33 * YDIM / 36));
	mouse.addpt(glpoint(14 * XDIM / 36, 23 * YDIM / 36));
	mouse.addpt(glpoint(18 * XDIM / 36, 23 * YDIM / 36));
	mouse.addpt(glpoint(18 * XDIM / 36, 33 * YDIM / 36));
	mouse.addpt(glpoint(16 * XDIM / 36, 33 * YDIM / 36));
	mouse.addpt(glpoint(16 * XDIM / 36, 31 * YDIM / 36));
	mouse.addpt(glpoint(18 * XDIM / 36, 31 * YDIM / 36));
	mouse.addpt(glpoint(14 * XDIM / 36, 31 * YDIM / 36));
	mouse.addpt(glpoint(14 * XDIM / 36, 33 * YDIM / 36));
	mouse.addpt(glpoint(16 * XDIM / 36, 33 * YDIM / 36));
	mouse.draw();
	glRasterPos2d(15.35 * XDIM / 36, 29 * YDIM / 36);
	printstring("Mouse");
	glRasterPos2d(14.75 * XDIM / 36, 26 * YDIM / 36);
	printstring("Move cursor");
	glRasterPos2d(15.25 * XDIM / 36, 25 * YDIM / 36);
	printstring("to aim");
	polyline lmp;
	lmp.addpt(glpoint(13 * XDIM / 36, 32 * YDIM / 36));
	lmp.addpt(glpoint(15 * XDIM / 36, 32 * YDIM / 36));
	lmp.draw();
	glRasterPos2d(11.25 * XDIM / 36, 32 * YDIM / 36);
	printstring("Click to");
	glRasterPos2d(11.5 * XDIM / 36, 31 * YDIM / 36);
	printstring("shoot");

}

void changeround(int n) {
	int i;
	switch (n) {
	case 0: STATE = '0'; SPAWNS = 0; COUNT = 0; AVATAR.sethealth(1000);
		GPOINTS = 0;
		for (i = 0; i < NUMTRI; i++) TRIANGLE[i].deactivate();
		for (i = 0; i < NUMSQR; i++) SQUARE[i].deactivate();
		for (i = 0; i < NUMSQR; i++) CONNECTION[i].deactivate();
		for (i = 0; i < NUMPENT; i++) PENTAGON[i].deactivate();
		for (i = 0; i < NUMHEX; i++) HEXAGON[i].deactivate(); break;
	case 1: STATE = '1'; SPAWNS = 100; COUNT = 0; AVATAR.sethealth(1000);
		GPOINTS = 0;
		for (i = 0; i < NUMTRI; i++) TRIANGLE[i].deactivate(); break;
	case 2: STATE = '2'; SPAWNS = 100; COUNT = 0;  AVATAR.sethealth(1000);
		if (!FULL) GPOINTS = 0;
		for (i = 0; i < NUMTRI; i++) TRIANGLE[i].deactivate(); 
		for (i = 0; i < NUMSQR; i++) SQUARE[i].deactivate(); 
		for (i = 0; i < NUMSQR; i++) CONNECTION[i].deactivate(); break;
	case 3: STATE = '3'; SPAWNS = 100; COUNT = 0;  AVATAR.sethealth(1000);
		if (!FULL) GPOINTS = 0;
		for (i = 0; i < NUMTRI; i++) TRIANGLE[i].deactivate();
		for (i = 0; i < NUMSQR; i++) SQUARE[i].deactivate();
		for (i = 0; i < NUMSQR; i++) CONNECTION[i].deactivate();
		for (i = 0; i < NUMPENT; i++) PENTAGON[i].deactivate(); break;
	case 4:	STATE = '4'; SPAWNS = 50; COUNT = 0;  AVATAR.sethealth(1000);
		if (!FULL) GPOINTS = 0;
		for (i = 0; i < NUMTRI; i++) TRIANGLE[i].deactivate();
		for (i = 0; i < NUMSQR; i++) SQUARE[i].deactivate();
		for (i = 0; i < NUMSQR; i++) CONNECTION[i].deactivate();
		for (i = 0; i < NUMPENT; i++) PENTAGON[i].deactivate();
		for (i = 0; i < NUMHEX; i++) HEXAGON[i].deactivate(); break;
	case 5: STATE = '5'; SPAWNS = 0; COUNT = 0;  AVATAR.sethealth(1000);
		if (!FULL) GPOINTS = 0;
		for (i = 0; i < NUMSQR; i++) CONNECTION[i].deactivate();
		PRIME.activate(); break;
	}
}

void movespawn() {
	double x, y;
	if (rand() % 2) {
		x = rand() % XDIM;
		if (rand() % 2)
			y = NPCRAD;
		else y = YDIM - NPCRAD;
	}
	else {
		y = rand() % YDIM;
		if (rand() % 2)
			x = NPCRAD;
		else x = XDIM - NPCRAD;
	}
	SPAWN = glpoint(x, y);

}

void handlebullets() {
	int i;
	for (i = 0; i < NUMBLT; i++) {
		if (BULLETS[i].isactive())
			BULLETS[i].draw();
	}
	for (i = 0; i < NUMBLT; i++) {
		if (BULLETS[i].isactive())
			BULLETS[i].move();
	}
}
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Triangle stuff >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void handletriangles(int max) {
	int i,j;
	for (i = 0; i < max && i < NUMTRI; i++) { //detects bullet collision
		if (TRIANGLE[i].isactive())
			for (j = 0; j < NUMBLT; j++) {
				if (BULLETS[j].isactive()) {
					if(TRIANGLE[i].detectbullet(BULLETS[j]))
						GPOINTS +=30;
				}
			}
	}
	for (i = 0; i < max && i < NUMTRI; i++) {  //detects collision with polygon
		if (TRIANGLE[i].isactive()) {
			TRIANGLE[i].detectcollision(AVATAR);
		}
	}
	for(i = 0; i < max && i < NUMTRI; i++) {  //draws triangles
		if (TRIANGLE[i].isactive())
			TRIANGLE[i].draw();
	}
	for (i = 0; i < max && i < NUMTRI; i++) { //moves for next draw
		if (TRIANGLE[i].isactive())
			TRIANGLE[i].move(AVATAR);
	}
}
bool checktriangleremaining() {
	int i;
	for (i = 0; i < NUMTRI; i++) {
		if (TRIANGLE[i].isactive())
			return true;
	}
	return false;
}

void spawntriangle(int max) {
	int i = 0;
	while (i < NUMTRI && i<max) {
		if (TRIANGLE[i].isactive())
			i++;
		else break;
	}
	if (i < NUMTRI && i < max) {
		TRIANGLE[i] = triangle(SPAWN);
		SPAWNS--;
	}
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Square Stuff >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void spawnsquare() {
	int i = 0;
	while (i < NUMSQR) {
		if (SQUARE[i].isactive())
			i++;
		else break;
	}
	if (i < NUMSQR) {
		int r = rand() % 8;
		while (true) {
			if (SDES[r] != SQUARE[0].getdes() && SDES[r] != SQUARE[1].getdes() && SDES[r] != SQUARE[2].getdes() && SDES[r] != SQUARE[3].getdes()) {  // checks for occupied destinations
				break;
			}
			else {
				r++;
				if (r == 8)
					r = 0;
			};
		}
		SQUARE[i] = square(SPAWN, SDES[r]);
		SPAWNS--;
	}
}

void handlesquares() {
	int i, j;
	for (i = 0; i < NUMSQR; i++) { //detects bullet collision
		if (SQUARE[i].isactive())
			for (j = 0; j < NUMBLT; j++) {
				if (BULLETS[j].isactive()) {
					if(SQUARE[i].detectbullet(BULLETS[j]))
						GPOINTS += 40;
				}
			}
	}
	for (i = 0; i < NUMTRI; i++) {  //detects collision with polygon
		if (SQUARE[i].isactive()) {
			SQUARE[i].detectcollision(AVATAR);
		}
	}
	for (i = 0; i < NUMSQR; i++) {  //draws squares
		if (SQUARE[i].isactive())
			SQUARE[i].draw();
	}
	for (i = 0;i < NUMSQR; i++) { //moves for next draw
		if (SQUARE[i].isactive())
			SQUARE[i].move();
	}
}

bool checksquareremaining() {
	int i;
	for (i = 0; i < NUMSQR; i++) {
		if (SQUARE[i].isactive())
			return true;
	}
	return false;
}


void changesquaredestinations() {
int i = 0;
	for (i = 0; i < NUMSQR; i++) {
		int r = rand() % 8;
		while (true) {
			if (SDES[r] != SQUARE[0].getdes() && SDES[r] != SQUARE[1].getdes() && SDES[r] != SQUARE[2].getdes() && SDES[r] != SQUARE[3].getdes()) {  // checks for occupied destinations
				break;
			}
			else {
				r++;
				if (r == 8)
					r = 0;
			};
		}
		SQUARE[i].setdestination(SDES[r]);
	}
}


void handleconnections() {
	int i, j;
	for (i = 0; i < NUMSQR; i++) {
		CONNECTION[i].deactivate();
	}
	for (i = 0; i < NUMSQR; i++) {
		if (SQUARE[i].isactive()) {
			j = i + 1;
			while (j != i) {
				if (j >= NUMSQR) j = 0;
				if (SQUARE[j].isactive()) {
					CONNECTION[i] = connection(SQUARE[i], SQUARE[j]);
					break;
				}
				else {
					j++;
				}
			}
		}
	}
	
	for (i = 0; i < NUMSQR; i++) {
		if (CONNECTION[i].isactive())
			CONNECTION[i].draw();
	}
	for (i = 0; i < NUMSQR; i++) {
		if (CONNECTION[i].isactive())
			CONNECTION[i].detectcollision(AVATAR);
	}
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Pentagon Stuff >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void spawnpentagon(int max) {
	int i = 0;
	while (i < NUMPENT && i<max) {
		if (PENTAGON[i].isactive())
			i++;
		else break;
	}
	if (i < NUMPENT && i < max) {
		PENTAGON[i] = pentagon(SPAWN, AVATAR);
		SPAWNS--;
	}
}

void handlepentagons(int n) {
	int i, j;
	for (i = 0; i < n && i < NUMPENT; i++) { //detects bullet collision
		if (PENTAGON[i].isactive())
			for (j = 0; j < NUMBLT; j++) {
				if (BULLETS[j].isactive()) {
					if(PENTAGON[i].detectbullet(BULLETS[j]))
						GPOINTS += 50;
				}
			}
	}
	for (i = 0; i < n && i < NUMPENT; i++) {  //detects collision with polygon
		if (PENTAGON[i].isactive()) {
			PENTAGON[i].detectcollision(AVATAR);
		}
	}
	for (i = 0; i < n && i < NUMPENT; i++) {  //draws polygon
		if (PENTAGON[i].isactive())
			PENTAGON[i].draw();
	}
	for (i = 0; i < n && i < NUMPENT; i++) { // determines if reflection is needed
		if (PENTAGON[i].isactive()) {
			glpoint p = PENTAGON[i].getcenter();
			if (p.ptx() < 0 || p.ptx() > XDIM || p.pty() < 0 || p.pty() > YDIM) // in case reflect fails
				PENTAGON[i].deactivate();
			if (p.pty() > YDIM - NPCRAD) {  //checks if at top border
				PENTAGON[i].reflect(1);
			}
			if (p.ptx() > XDIM - NPCRAD) { //checks if at right border
				PENTAGON[i].reflect(2);
			}
			if (p.pty() < NPCRAD) { //checks if at bottom border
				PENTAGON[i].reflect(3);
			}
			if (p.ptx() < NPCRAD) { //checks if at left border
				PENTAGON[i].reflect(4);
			}
		}
	}
	for (i = 0; i < n && i < NUMTRI; i++) { //moves for next draw
		if (PENTAGON[i].isactive())
			PENTAGON[i].move();
	}
}

bool checkpentagonremaining() {
	int i;
	for (i = 0; i < NUMPENT; i++) {
		if (PENTAGON[i].isactive())
			return true;
	}
	return false;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< hexagon stuff >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void spawnhexagon(int max) {
	int i = 0;
	while (i < NUMHEX && i<max) {
		if (HEXAGON[i].isactive())
			i++;
		else break;
	}
	if (i < NUMHEX && i < max) {
		HEXAGON[i] = hexagon(SPAWN, XDIM, YDIM);
		SPAWNS--;
	}
}

void handlehexagons(int n) {
	int i, j;
	for (i = 0; i < n && i < NUMHEX; i++) { //detects bullet collision
		if (HEXAGON[i].isactive())
			for (j = 0; j < NUMBLT; j++) {
				if (BULLETS[j].isactive()) {
					if(HEXAGON[i].detectbullet(BULLETS[j]))
						GPOINTS += 60;
				}
			}
	}
	for (i = 0; i < n && i < NUMHEX; i++) {  //detects collision with polygon
		if (HEXAGON[i].isactive()) {
			HEXAGON[i].detectcollision(AVATAR);
		}
	}
	for (i = 0; i < n && i < NUMHEX; i++) {  //draws polygon
		if (HEXAGON[i].isactive())
			HEXAGON[i].draw(AVATAR);
	}
	for (i = 0; i < n && i < NUMHEX; i++) { //detects collision with hexagon bullet
		if (HEXAGON[i].isactive() && HEXAGON[i].getbullet().isactive()) {
			HEXAGON[i].detectbulletcollision(AVATAR);
		}
	}
	for (i = 0; i < n && i < NUMTRI; i++) { //moves for next draw
		if (HEXAGON[i].isactive())
			HEXAGON[i].move(AVATAR);
	}
	if (COUNT % 1500 == 0) {
		for (i = 0; i < n && i < NUMHEX; i++) {
			HEXAGON[i].setshoot();
		}
	}
}

bool checkhexagonremaining() {
	int i;
	for (i = 0; i < NUMHEX; i++) {
		if (HEXAGON[i].isactive())
			return true;
	}
	return false;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Polygon Prime Stuff >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void handleprime() {
	int i;
	for (i = 0; i < NUMBLT; i++) {
		if (BULLETS[i].isactive()) {
			if(PRIME.detectbullets(BULLETS[i]))
				GPOINTS +=10;
		}
	}
	PRIME.detectcollision(AVATAR);
	PRIME.draw(AVATAR);
	if (COUNT < 9500)
	PRIME.act(AVATAR);
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< GLSTUFF >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	setWorldWin(0.0, XDIM, 0.0, YDIM);
	glClear(GL_COLOR_BUFFER_BIT);
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY) {
	if (theKey == 27) exit(1);
	else if (theKey == 13) {
		if (STATE == 'm') {
			int i = MENU.select();
			switch (i) {
			case 0: changeround(1); FULL = true; break;
			case 1: STATE = 'l'; break;
			case 2: changeround(0); break;
			case 3: STATE = 'c'; break;
			case 4: exit(0);
			default: break;
			}
		}
		else if (STATE == 'l') {
			int i = LEVELM.select();
			switch (i) {
			case 0: changeround(1); FULL = false; break;
			case 1: changeround(2); FULL = false; break;
			case 2: changeround(3); FULL = false; break;
			case 3: changeround(4); FULL = false; break;
			case 4: changeround(5); FULL = false; break;
			default: break;
			}
		}
	}
	else if (theKey == 'm')
		STATE = 'm'; 
	else if (theKey == 'g') {
		if (GM) GM = false;
		else GM = true;
	}
	else KEYS[theKey] = true;
	glutPostRedisplay();
}

void myUpKeyboard(unsigned char theKey, int mouseX, int mouseY) {
	if (STATE != 'm' || STATE != 'l' || STATE != 'c') {
		KEYS[theKey] = false;
		glutPostRedisplay();
	}
}


void myMouse(int button, int state, int mouseX, int mouseY) {
	if (STATE != 'm' || STATE != 'l' || STATE != 'c') {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			int i = 0;
			while (i < NUMBLT) {
				if (BULLETS[i].isactive())
					i++;
				else break;
			}
			if (i < NUMBLT)
				BULLETS[i] = AVATAR.shoot();
		}
	}
}

void myIdle() {
	if (STATE != 'm' || STATE != 'l' || STATE != 'c')
		glutPostRedisplay();
	delay(1);
}

void myPassiveMotion(int mouseX, int mouseY) {
	if (STATE != 'm' || STATE != 'l' || STATE != 'c') {
		MOUSECOORD = glpoint(mouseX, YDIM - mouseY);
		glutPostRedisplay();
	}
}
void myMotion(int mouseX, int mouseY) {
	if (STATE != 'm' || STATE != 'l' || STATE != 'c') {
		MOUSECOORD = glpoint(mouseX, YDIM - mouseY);
		glutPostRedisplay();
	}
}

void Sinput(int key, int x, int y) {
	if (STATE == 'm')
		switch (key) {
		case GLUT_KEY_UP: MENU.moveup(); glutPostRedisplay(); break;
		case GLUT_KEY_DOWN: MENU.movedown(); glutPostRedisplay(); break;
		}
	else if (STATE == 'l') {
		switch (key) {
		case GLUT_KEY_UP: LEVELM.moveup(); glutPostRedisplay(); break;
		case GLUT_KEY_DOWN: LEVELM.movedown(); glutPostRedisplay(); break;
		}
	}
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	if (STATE == 'm') {
		MENU.display();
	}
	else if (STATE == 'l') {
		LEVELM.display();
	}
	else if (STATE == 'c') {
		printcontrolscreen();
	}
	else if (STATE == '0') {
		if ((!GM)&&AVATAR.gethealth() <= 0)
			STATE = 'd';
		if (COUNT > 10000)
			COUNT = 0;
		printinfo();
		COUNT++;
		movespawn();
		KeyboardActions();
		AVATAR.setaim(MOUSECOORD.ptx(), MOUSECOORD.pty());
		AVATAR.draw();
		handlebullets();
		if (COUNT % 250 == 0)
			spawntriangle(NUMTRI);
		handletriangles(NUMTRI);
		if (COUNT % 2500 == 0)
			spawnsquare();
		handlesquares();
		if (COUNT % 10000 == 0)
			changesquaredestinations();
		handleconnections();
		if (COUNT % 1000 == 0)
			spawnpentagon(NUMPENT);
		handlepentagons(NUMPENT);
		if (COUNT % 1250 == 0)
			spawnhexagon(NUMHEX);
		handlehexagons(NUMHEX);
	}
	else if (STATE == '1') {
		if ((!GM) && AVATAR.gethealth() <= 0)
			STATE = 'd';
		if (COUNT > 10000)
			COUNT = 0;
		printinfo();
		movespawn();
		KeyboardActions();
		AVATAR.setaim(MOUSECOORD.ptx(), MOUSECOORD.pty());
		AVATAR.draw();
		handlebullets();
		if (SPAWNS > 0 && COUNT % 250 == 0)
			spawntriangle(NUMTRI); 
		handletriangles(NUMTRI);
		if (SPAWNS > 0 || checktriangleremaining());
		else {
			if (FULL)
				changeround(2);
			else STATE = 'v';
		}
	}
	else if (STATE == '2') {
		if ((!GM) && AVATAR.gethealth() <= 0)
			STATE = 'd';
		if (COUNT > 10000)
			COUNT = 0;
		printinfo();
		COUNT++;
		movespawn();
		KeyboardActions();
		AVATAR.setaim(MOUSECOORD.ptx(), MOUSECOORD.pty());
		AVATAR.draw();
		handlebullets();
		if (SPAWNS > 0 && COUNT % 250 == 0)
			spawntriangle(NUMTRI);
		handletriangles(NUMTRI);
		if (SPAWNS > 0 && COUNT % 2500 == 0)
			spawnsquare();
		handlesquares();
		if (COUNT % 10000 == 0)
			changesquaredestinations();
		handleconnections();
		if (SPAWNS > 0 || checktriangleremaining() || checksquareremaining());
		else {
			if (FULL) changeround(3);
			else STATE = 'v';
		}
	}
	else if (STATE == '3') {
		if ((!GM) && AVATAR.gethealth() <= 0)
			STATE = 'd';
		if (COUNT > 10000)
			COUNT = 0;
		printinfo();
		COUNT++;
		movespawn();
		KeyboardActions();
		AVATAR.setaim(MOUSECOORD.ptx(), MOUSECOORD.pty());
		AVATAR.draw();
		handlebullets();
		if (SPAWNS > 0 && COUNT % 250 == 0)
		spawntriangle(5);
		handletriangles(5);
		if (SPAWNS > 0 && COUNT % 2500 == 0)
			spawnsquare();
		handlesquares();
		if (COUNT % 10000 == 0)
			changesquaredestinations();
		handleconnections();
		if (SPAWNS > 0 && COUNT % 1000 == 0)
			spawnpentagon(NUMPENT);
		handlepentagons(NUMPENT);
		if (SPAWNS > 0 || checktriangleremaining() || checksquareremaining() || checkpentagonremaining());
		else {
			if (FULL) changeround(4);
			else STATE = 'v';
		}
	}
	else if (STATE == '4') {
		if ((!GM) && AVATAR.gethealth() <= 0)
			STATE = 'd';
		if (COUNT > 10000)
			COUNT = 0;
		printinfo();
		COUNT++;
		movespawn();
		KeyboardActions();
		AVATAR.setaim(MOUSECOORD.ptx(), MOUSECOORD.pty());
		AVATAR.draw();
		handlebullets();
		if (SPAWNS > 0 && COUNT % 2500 == 0)
			spawnsquare();
		handlesquares();
		if (COUNT % 10000 == 0)
			changesquaredestinations();
		handleconnections(); 
		if (SPAWNS > 0 && COUNT % 1000 == 0)
			spawnpentagon(NUMPENT);
		handlepentagons(NUMPENT);
		if (SPAWNS > 0 && COUNT % 1250 == 0)
			spawnhexagon(NUMHEX);
		handlehexagons(NUMHEX);
		if (SPAWNS > 0 || checksquareremaining() || checkpentagonremaining() || checkhexagonremaining());
		else {
			if (FULL) changeround(5);
			else STATE = 'v';
		}
			
	}
	else if (STATE == '5') {
		if ((!GM) && AVATAR.gethealth() <= 0)
			STATE = 'd';
		if (COUNT >= 10000) {
			COUNT = 0;
		}
		if (COUNT == 0) {
			PRIME.transform(AVATAR);
		}
		printinfo();
		COUNT++;
		KeyboardActions();
		handleprime();
		AVATAR.setaim(MOUSECOORD.ptx(), MOUSECOORD.pty());
		AVATAR.draw();
		handlebullets();
		if (PRIME.isactive());
		else {
			STATE = 'v';
			GPOINTS += 5000;
		}
	}
	else if (STATE == 'v') {
		printvictoryscreen();
	}
	else if (STATE == 'd')
		printdefeatscreen();
	glFlush();
}


int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(XDIM, YDIM);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Jealous Polygons");
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myUpKeyboard);
	glutMouseFunc(myMouse);
	glutPassiveMotionFunc(myPassiveMotion);
	glutMotionFunc(myMotion);
	glutIdleFunc(myIdle);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(Sinput);
	glutFullScreen();
	myInit();
	glutMainLoop();
}