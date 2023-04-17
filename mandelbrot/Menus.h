#include <string>
#include <iostream>

class Menus
{
private:

public:
	Menus();
	~Menus();

	static void mainMenu();
	static void instructionsMenu();
	static void mandelbrotMenu();
	static void settingsMenu(short int&, bool&, std::string&, std::string&);
};