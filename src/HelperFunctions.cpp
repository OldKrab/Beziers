#include "HelperFunctions.h"

namespace HelperFunctions
{
	sf::Vector2f GetRandomPoint(sf::IntRect range)
	{
		auto point = sf::Vector2f();
		point.x = static_cast<float>(range.left + rand() % range.width);
		point.y = static_cast<float>(range.top + rand() % range.height);
		return point;
	}
}
