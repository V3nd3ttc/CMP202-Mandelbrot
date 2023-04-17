#include <fstream>
#include <iostream>

#include "writeTGA.h"
#include "mandelbrotTask.h"
#include "definitions.h"

void writeTGA::run() {
	std::ofstream outfile(filename_, std::ofstream::binary);

	uint8_t header[18] = {
		0, // no image ID
		0, // no colour map
		2, // uncompressed 24-bit image
		0, 0, 0, 0, 0, // empty colour map specification
		0, 0, // X origin
		0, 0, // Y origin
		WIDTH & 0xFF, (WIDTH >> 8) & 0xFF, // width
		HEIGHT & 0xFF, (HEIGHT >> 8) & 0xFF, // height
		24, // bits per pixel
		0, // image descriptor
	};
	outfile.write((const char*)header, 18);

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			uint8_t pixel[3] = {
				xandy[y][x] & 0xFF, // blue channel
				(xandy[y][x] >> 8) & 0xFF, // green channel
				(xandy[y][x] >> 16) & 0xFF, // red channel
			};
			outfile.write((const char*)pixel, 3);
		}
	}

	outfile.close();
	if (!outfile)
	{
		// An error has occurred at some point since we opened the file.
		std::cout << "Error writing to " << filename_ << std::endl;
		exit(1);
	}
}
