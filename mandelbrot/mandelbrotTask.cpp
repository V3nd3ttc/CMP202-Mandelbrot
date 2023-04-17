#include "mandelbrotTask.h"
#include <complex>
#include <iostream>

void mandelbrotTask::run() {
	for (int x = 0; x < WIDTH; ++x)
	{
		double realX = realLeft_+ (x * (realRight_ - realLeft_) / WIDTH) + offsetX_;
		double imaginaryY = imaginaryTop_ + (yLine_ * (imaginaryBottom_ - imaginaryTop_) / HEIGHT) + offsetY_;
		std::complex<double> c(realX, imaginaryY);

		// Start off z at (0, 0).
		std::complex<double> z(0.0, 0.0);

		int iterations = 0;
		while (abs(z) < 2.0 && iterations < MAX_ITERATIONS)
		{
			z = (z * z) + c;
			++iterations;
		}
		if (iterations < MAX_ITERATIONS && iterations > 0) {
			int pick = iterations % 16;
			xandy_[yLine_][x] = colours[pick];
		}
		else {
			xandy_[yLine_][x] = sf::Color::Black;
		}
	}
	yLine_++;
}