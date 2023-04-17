#ifndef MANDELBROTTASK_H
#define MANDELBROTTASK_H

#include <string>
#include <array>
#include "task.h"
#include "definitions.h"
#include <SFML/Graphics.hpp>


// Task that prints that calculates mandelbrot.
class mandelbrotTask : public Task
{
private:
	double& realLeft_;
	double& realRight_;
	double& imaginaryTop_;
	double& imaginaryBottom_;
	double& offsetX_;
	double& offsetY_;
	double& zoom_;
	int yLine_;
	std::array<std::array<sf::Color, WIDTH>, HEIGHT>& xandy_;
	std::array<sf::Color, 16> colours = {
		sf::Color(66, 30, 15),
		sf::Color(25, 7, 26),
		sf::Color(9, 1, 47),
		sf::Color(4, 4, 73),
		sf::Color(0, 7, 100),
		sf::Color(12, 44, 138),
		sf::Color(24, 82, 177),
		sf::Color(57, 125, 209),
		sf::Color(134, 181, 229),
		sf::Color(211, 236, 248),
		sf::Color(241, 233, 191),
		sf::Color(248, 201, 95),
		sf::Color(255, 170, 0),
		sf::Color(204, 128, 0),
		sf::Color(153, 87, 0),
		sf::Color(106, 52, 3)
	};

public:
	mandelbrotTask(double& realLeft, double& realRight, double& imaginaryTop, double& imaginaryBottom, double& offsetX, double& offsetY, double& zoom, int& yLine, std::array<std::array<sf::Color, WIDTH>, HEIGHT>& xandy)
		: realLeft_(realLeft), realRight_(realRight), imaginaryTop_(imaginaryTop), imaginaryBottom_(imaginaryBottom), offsetX_(offsetX), offsetY_(offsetY), zoom_(zoom), yLine_(yLine), xandy_(xandy)
	{
	}

	void run();
};
#endif