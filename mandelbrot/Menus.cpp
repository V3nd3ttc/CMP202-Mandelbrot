#include "Menus.h"


Menus::Menus()
{
}

Menus::~Menus()
{
}

void Menus::mainMenu() {
	std::cout << "=========================================================" << std::endl;
	std::cout << "  ___  ___        _         ___  ___                    " << std::endl;
	std::cout << "  |  \\/  |       (_)        |  \\/  |                    " << std::endl;
	std::cout << "  | .  . |  __ _  _  _ __   | .  . |  ___  _ __   _   _ " << std::endl;
	std::cout << "  | |\\/| | / _` || || '_ \\  | |\\/| | / _ \\| '_ \\ | | | |" << std::endl;
	std::cout << "  | |  | || (_| || || | | | | |  | ||  __/| | | || |_| |" << std::endl;
	std::cout << "  \\_|  |_/ \\__,_||_||_| |_| \\_|  |_/ \\___||_| |_| \\__,_|" << std::endl;
	std::cout << "                                                        " << std::endl;
	std::cout << "=========================================================" << std::endl;
	std::cout << "1. Run" << std::endl;
	std::cout << "2. Settings" << std::endl;
	std::cout << "3. Instructions" << std::endl;
	std::cout << "Q. Quit" << std::endl;
	std::cout << "=========================================================" << std::endl;
}
void Menus::mandelbrotMenu() {
	std::cout << "=======================================================" << std::endl;
	std::cout << "  ___  ___                _      _ _               _   " << std::endl;
	std::cout << "  |  \\/  |               | |    | | |             | |  " << std::endl;
	std::cout << "  | .  . | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ " << std::endl;
	std::cout << "  | |\\/| |/ _` | '_ \\ / _` |/ _ \\ | '_ \\| '__/ _ \\| __|" << std::endl;
	std::cout << "  | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ " << std::endl;
	std::cout << "  \\_|  |_/\\__,_|_| |_|\\__,_|\\___|_|_.__/|_|  \\___/ \\__|" << std::endl;
	std::cout << "                                                       " << std::endl;
	std::cout << "=======================================================" << std::endl;
	std::cout << "1. Run Mandelbrot" << std::endl;
	std::cout << "ESC. Close the Window" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "B. Back" << std::endl;
	std::cout << "Q. Quit" << std::endl;
	std::cout << "=========================================================" << std::endl;
}

void Menus::instructionsMenu() {
	std::cout << "=========================================================" << std::endl;
	std::cout << " _____          _                   _   _                 " << std::endl;
	std::cout << "|_   _|        | |                 | | (_)                " << std::endl;
	std::cout << "  | | _ __  ___| |_ _ __ _   _  ___| |_ _  ___  _ __  ___ " << std::endl;
	std::cout << "  | || '_ \\/ __| __| '__| | | |/ __| __| |/ _ \\| '_ \\/ __|" << std::endl;
	std::cout << " _| || | | \\__ \\ |_| |  | |_| | (__| |_| | (_) | | | \__ \\" << std::endl;
	std::cout << " \\___/_| |_|___/\\__|_|   \\__,_|\\___|\\__|_|\\___/|_| |_|___/" << std::endl;
	std::cout << "                                                        " << std::endl;
	std::cout << "=========================================================" << std::endl;
	std::cout << "Move UP - UP ARROW" << std::endl;
	std::cout << "Move DOWN - DOWN ARROW" << std::endl;
	std::cout << "Move LEFT - LEFT ARROW" << std::endl;
	std::cout << "Move RIGHT - RIGHT ARROW" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "Save render - Space" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "Zoom In - Z" << std::endl;
	std::cout << "Zoom Out - X" << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "B. Back" << std::endl;
	std::cout << "Q. Quit" << std::endl;
	std::cout << "=========================================================" << std::endl;
}

void Menus::settingsMenu(short int& formatChoice, bool& timeChoice, std::string& filename, std::string& extension) {
	std::cout << "===============================================" << std::endl;
	std::cout << "   _____        _    _    _                    " << std::endl;
	std::cout << "  /  ___|      | |  | |  (_)                   " << std::endl;
	std::cout << "  \\ `--.   ___ | |_ | |_  _  _ __    __ _  ___ " << std::endl;
	std::cout << "   `--. \\ / _ \\| __|| __|| || '_ \\  / _` |/ __|" << std::endl;
	std::cout << "  /\\__/ /|  __/| |_ | |_ | || | | || (_| |\\__ \\" << std::endl;
	std::cout << "  \\____/  \\___| \\__| \\__||_||_| |_| \\__, ||___/" << std::endl;
	std::cout << "                                     __/ |     " << std::endl;
	std::cout << "                                    |___/      " << std::endl;
	std::cout << "                                               " << std::endl;
	std::cout << "===============================================" << std::endl;
	std::cout << "F. Change which format to use for saved image" << std::endl;
	switch (formatChoice)
	{
	case 0:
		std::cout << "|tga|, png, bmp, jpg " << std::endl;
		break;
	case 1:
		std::cout << "tga, |png|, bmp, jpg " << std::endl;
		break;
	case 2:
		std::cout << "tga, png, |bmp|, jpg " << std::endl;
		break;
	case 3:
		std::cout << "tga, png, bmp, |jpg| " << std::endl;
		break;
	default:
		std::cout << "Error during format change" << std::endl;
		break;
	}
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "N. Change filename for saved image" << std::endl;
	std::cout << "Filename: " << filename + extension << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	if (timeChoice) {
		std::cout << "C. Display render time in console: yes" << std::endl;
	}
	else {
		std::cout << "C. Display render time in console: no" << std::endl;
	}
	
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "R. Reset to default" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "B. Back" << std::endl;
	std::cout << "Q. Quit" << std::endl;
	std::cout << "================================================" << std::endl;
}