#pragma once
#include "task.h"
#include "definitions.h"
#include <string>
class writeTGA : public Task
{
private:
	std::string filename_;
	std::array<std::array<uint32_t, WIDTH>, HEIGHT>& xandy;
public:
	writeTGA(std::string filename, std::array<std::array<uint32_t, WIDTH>, HEIGHT>& xandy)
		: filename_(filename),xandy(xandy)
	{
	}

	void run();
};

