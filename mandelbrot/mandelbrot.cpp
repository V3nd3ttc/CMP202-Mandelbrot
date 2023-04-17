// Mandelbrot set example
// Adam Sampson <a.sampson@abertay.ac.uk>



//MAKE CHANGES TO ITERATIONS OPTIONS
//OPTIONS COLOUR

#include <chrono>
#include <array>
#include <conio.h>
#include <string>
#include <condition_variable>
#include "task.h"
#include "farm.h"
#include "mandelbrotTask.h"
#include "spriteTask.h"
#include "definitions.h"
#include "Menus.h"
#include <SFML/Graphics.hpp>

std::array<std::array<sf::Color, WIDTH>, HEIGHT> xandy;

// Import things we need from the standard library
using std::chrono::duration_cast;
using std::chrono::milliseconds;

// Define the alias "the_clock" for the clock type we're going to use.
typedef std::chrono::steady_clock the_clock;

std::mutex display_lock;
std::condition_variable display_cv;
std::mutex time_lock;
std::condition_variable time_cv;
bool done = false;
bool doneTime = false;


void time(int* time_taken) {
	std::unique_lock<std::mutex>lock(time_lock);
	while (!doneTime) {
		time_cv.wait(lock);
		if (doneTime) {
			break;
		}
		system("CLS");
		Menus::mandelbrotMenu();
		std::cout << "Computing the Mandelbrot set took " << *time_taken << " ms." << std::endl;
	}
	std::cout << "Time thread exited" << std::endl;
}

void runMandelbrot(double& realLeft, double& realRight, double& imaginaryTop, double& imaginaryBottom, double& offsetX, double& offsetY, double& zoom, std::string& toSave, bool& timeChoice) {
	std::unique_lock<std::mutex>lock(display_lock);
	int time_taken = 0;
	std::thread timeThread([&] {
		time(&time_taken);
		});
	while (!done) {
		display_cv.wait(lock);
		if (done) {
			break;
		}
		Farm f;

		sf::Image render;
		render.create(WIDTH, HEIGHT, sf::Color(0, 0, 0));
		sf::Sprite sprite;
		sf::Texture texture;
		bool coordinateChange = false;
		for (int i = 0; i < HEIGHT; i++)
		{
			f.add_task(new mandelbrotTask(realLeft, realRight, imaginaryTop, imaginaryBottom, offsetX, offsetY, zoom, i, xandy));
		}
		f.add_task(new spriteTask(xandy, render));
		//Start Timing
		the_clock::time_point start = the_clock::now();
		f.run();
		//Stop timing
		the_clock::time_point end = the_clock::now();
		coordinateChange = false;

		// Compute the difference between the two times in milliseconds
		time_taken = duration_cast<milliseconds>(end - start).count();
		if (timeChoice) {
			time_cv.notify_one();
		}
		f.run();

		sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");
		if (!texture.loadFromImage(render))
		{
			std::cout << "Error loading texture" << std::endl;
		}

		sprite.setTexture(texture);
		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(sprite);

		// end the current frame
		window.display();

		while (window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					system("CLS");
					Menus::mainMenu();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
					case sf::Keyboard::Q:
						window.close();
						std::cout << "Window closed. Press 'Q' again to Exit program. 'B' to go back to menu or '1' to run again" << std::endl;
						break;
					case sf::Keyboard::Escape:
						window.close();
						std::cout << "Window closed. Press 'Q' to Exit program. 'B' to go back to menu or '1' to run again" << std::endl;
						break;
					case sf::Keyboard::Left:
						coordinateChange = true;
						offsetX -= 0.1 * realRight;
						break;
					case sf::Keyboard::Right:
						coordinateChange = true;
						offsetX += 0.1 * realRight;
						break;
					case sf::Keyboard::Up:
						coordinateChange = true;
						offsetY += 0.1 * imaginaryTop;
						break;
					case sf::Keyboard::Down:
						coordinateChange = true;
						offsetY -= 0.1 * imaginaryTop;
						break;
					case sf::Keyboard::Z:
						coordinateChange = true;
						realLeft /= zoom;
						realRight /= zoom;
						imaginaryTop /= zoom;
						imaginaryBottom /= zoom;
						break;
					case sf::Keyboard::X:
						coordinateChange = true;
						realLeft *= zoom;
						realRight *= zoom;
						imaginaryTop *= zoom;
						imaginaryBottom *= zoom;
						break;
					case sf::Keyboard::Space:
						if (render.saveToFile(toSave)) {
							std::cout << "Succesfull saved: " << toSave << std::endl;
						}
						else {
							std::cout << "Failed save" << std::endl;
						}
					default:
						coordinateChange = false;
						break;
					}
					break;
				default:
					break;
				}
			}

			if (coordinateChange == true) {
				for (int i = 0; i < HEIGHT; i++)
				{
					f.add_task(new mandelbrotTask(realLeft, realRight, imaginaryTop, imaginaryBottom, offsetX, offsetY, zoom, i, xandy));
				}
				f.add_task(new spriteTask(xandy, render));
				//Start Timing
				start = the_clock::now();
				f.run();
				//Stop Timing
				end = the_clock::now();
				// Compute the difference between the two times in milliseconds
				time_taken = duration_cast<milliseconds>(end - start).count();
				if (timeChoice) {
					time_cv.notify_one();
				}
				coordinateChange = false;
				if (!texture.loadFromImage(render))
				{
					std::cout << "Error loading texture" << std::endl;
				}
				sprite.setTexture(texture);
			}

			// clear the window with black color
			window.clear(sf::Color::Black);

			// draw everything here...
			window.draw(sprite);

			// end the current frame
			window.display();
		}
	}
	doneTime = true;
	time_cv.notify_one();
	timeThread.join();
	std::cout << "Mandelbrot thread exited" << std::endl;
}

int main(int argc, char *argv[])
{
	char menuChoice = ' ';
	bool inMain = true;
	bool inMandelbrot = false;
	bool inSettings = false;
	bool inInstructions = false;


	short int formatChoice = 0;
	bool timeChoice = true;
	Menus::mainMenu();

	double realLeft = -2; //x0
	double realRight = 2; //x1
	double imaginaryTop = 1.25; //y0
	double imaginaryBottom = -1.25; //y1
	double offsetX = 0.0;
	double offsetY = 0.0;
	double zoom = 1.1;

	std::string filename = "output";
	std::string extension = ".tga";
	std::string toSave = filename + extension;
	std::thread mandelbrotThread([&] {
		runMandelbrot(realLeft, realRight, imaginaryTop, imaginaryBottom, offsetX, offsetY, zoom, toSave, timeChoice);
		});

	while (menuChoice != 'q') { //Runs until user presses Q to quit
		menuChoice = tolower(_getch()); //Gets user input
		switch (menuChoice) {
			case '1':
				if (inMain || inMandelbrot) {
					system("CLS");
					Menus::mandelbrotMenu();
					inMandelbrot = true;
					display_cv.notify_one();
					break;
				}
				break;
			case '2':
				if (inMain) { //Runs settings menu if in main menu
					system("CLS");
					Menus::settingsMenu(formatChoice, timeChoice, filename, extension); //Displays settins menu
					inMain = false;
					inSettings = true;
					break;
				}
				break;
			case '3':
				if (inMain) { //Runs settings menu if in main menu
					system("CLS");
					Menus::instructionsMenu(); //Displays settins menu
					inMain = false;
					inInstructions = true;
					break;
				}
				break;
			case 'b':
				if (inSettings) { //BACK FROM SETTINGS MENU
					system("CLS");
					Menus::mainMenu();
					inMain = true;
					inSettings = false;
					break;
				} else if (inInstructions) { //BACK FROM INSTRUCTIONS MENU
					system("CLS");
					Menus::mainMenu();
					inMain = true;
					inInstructions = false;
					break;
				}
				else if (inMandelbrot) { //BACK FROM MANDELBROT MENU
					system("CLS");
					Menus::mainMenu();
					inMain = true;
					inMandelbrot = false;
					break;
				}
				break;
			case 'c':
				if (inSettings) { //BACK FROM SETTINGS MENU
					timeChoice = !timeChoice;
					system("CLS");
					Menus::settingsMenu(formatChoice, timeChoice, filename, extension); //Displays settins menu
					break;
				}
				break;
			case 'f':
				if (inSettings) {
					if (formatChoice == 3) {
						formatChoice = 0;
					}
					else {
						formatChoice++;
					}
					switch (formatChoice)
					{
					case 0:
						extension = ".tga";
						break;
					case 1:
						extension = ".png";
						break;
					case 2:
						extension = ".bmp";
						break;
					case 3:
						extension = ".jpg";
						break;
					default:
						std::cout << "Error during format change" << std::endl;
						break;
					}
					toSave = filename + extension;
					system("CLS");
					Menus::settingsMenu(formatChoice, timeChoice, filename, extension); //Displays settins menu
					break;
				}
				break;
			case 'n':
				if (inSettings) {
					std::cout << "Enter new filename: ";
					std::cin >> filename;
					toSave = filename + extension;
					system("CLS");
					Menus::settingsMenu(formatChoice, timeChoice, filename, extension); //Displays settins menu
					break;
				}
				break;
			case 'r':
				if (inSettings) {
					filename = "output";
					extension = ".tga";
					toSave = filename + extension;
					formatChoice = 0;
					timeChoice = false;
					system("CLS");
					Menus::settingsMenu(formatChoice, timeChoice, filename, extension); //Displays settins menu
					break;
				}
				break;
			case 'q':
				std::cout << "Exit Successful" << std::endl;
				break;
			default:
				std::cout << "Wrong input" << std::endl;
				break;
		}
	}
	done = true;
	display_cv.notify_one();
	mandelbrotThread.join();
	return 0;
}
