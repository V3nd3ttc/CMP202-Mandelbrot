#include "task.h"
#include "definitions.h"
#include <array>
#include <SFML/Graphics.hpp>

class spriteTask : public Task
{
private:
	std::array<std::array<sf::Color, WIDTH>, HEIGHT>& xandy_;
	sf::Image& render_;

public:
	spriteTask(std::array<std::array<sf::Color, WIDTH>, HEIGHT>& xandy, sf::Image& render)
		: xandy_(xandy), render_(render)
	{
	}

	void run();
};

