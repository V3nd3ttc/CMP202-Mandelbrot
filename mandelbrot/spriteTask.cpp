#include "spriteTask.h"

void spriteTask::run() {
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			render_.setPixel(x, y, xandy_[y][x]);
		}
	}
}