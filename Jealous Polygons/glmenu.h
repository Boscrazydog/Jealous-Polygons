#ifndef glmenu_h
#define glmenu_h



#include <string>
#include <vector>
#include "glpoints.h"

class menu {
public:
	menu();
	menu(glpoint,std::string, std::string);
	menu(glpoint,std::string, std::string, std::string);
	menu(glpoint,std::string, std::string, std::string,std::string);
	menu(glpoint,std::string, std::string, std::string, std::string, std::string);

	void display();
	void moveup();
	void movedown();
	int select();

private:
	std::string options[5];  
	glpoint center;
	int optnum, copt,slen;
	void displaytext();
	void displayselection();
	void getslen();
};

#endif