#ifndef npc_H
#define npc_H

#include "glpolyline.h"
#include "glpolygon.h"
#include "avatar.h"
#include "bullet.h"

class triangle {
public:
	triangle();
	triangle(glpoint);

	void move(avatar&);
	void draw();
	void deactivate();
	bool detectbullet(bullet&);
	void detectcollision(avatar&);

	glpoint getcenter();

	bool isactive();

private:
	bool active;
	int health;
	polygon shape;
	double radius, angle;

};

class square {
public:
	square();
	square(glpoint&,glpoint&);

	glpoint getcenter();
	glpoint getdes();

	void setdestination(glpoint&);
	void move();
	bool detectbullet(bullet&);
	void detectcollision(avatar&);
	void draw();
	void deactivate();
	
	bool isactive();

private:
	bool active; 
	int health;
	glpoint center;
	glpoint destination;
	polygon shape;
	double radius;
};

class connection {
public:
	connection();
	connection(square&, square&);
	connection(glpoint&, glpoint&);

	void draw();

	bool isactive();
	
	void deactivate();

	void detectcollision(avatar&);
private:
	glpoint p1, p2;
	polyline line;
	bool active;
};

class pentagon {
public:
	pentagon();
	pentagon(glpoint&, avatar&);

	void move();
	void reflect(int);
	void draw();

	bool detectbullet(bullet&);
	void detectcollision(avatar&);

	void deactivate();

	bool isactive();
	glpoint getcenter();

private:
	bool active;
	glvector trajectory;
	int health;
	polygon shape;
	double angle;
	glpoint center;

};

#endif

class hexagon {
public:
	hexagon();
	hexagon(glpoint, double, double);

	void move(avatar&);
	void draw(avatar&);
	void setshoot();

	bool detectbullet(bullet&);
	void detectcollision(avatar&);
	void detectbulletcollision(avatar&);

	void deactivate();
	void deactivatebullet();

	glpoint getcenter();
	bullet getbullet();
	bool isactive();
private:
	void move_up(double);
	void move_up_right(double);
	void move_right(double);
	void move_down_right(double);
	void move_down(double);
	void move_down_left(double);
	void move_left(double);
	void move_up_left(double);

	void shoot(avatar&);

	bool active;
	int health;
	polygon shape;
	glpoint center;
	int shoottime;
	bool shooting;
	double xdim, ydim;
	bullet hexbullet;
	int movetime;
	int movetype;
};

class prime {
public:
	prime();
	prime(glpoint, int, int);

	void recenter();
	void transform(avatar&);
	void activate();
	void act(avatar&);
	void draw(avatar&);
	

	bool detectbullets(bullet&);
	void detectcollision(avatar&);

	void reflect(int);

	void shoot(avatar&);

	bool isactive();


private:
	polygon shape;
	polygon barrier;
	int health;
	bool active;
	glpoint center;
	glpoint ocenter;
	int state;
	double angle;
	connection con[4];
	int xdim, ydim;
	glvector trajectory;
	bullet bullets[6];
	int shoottime;
	int time;
	bool shootmode;
	bool recentermode;
};