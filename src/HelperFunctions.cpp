#include "HelperFunctions.h"

#include <iostream>

namespace HelperFunctions
{
	sf::Vector2f GetRandomPoint(sf::IntRect range)
	{
		auto point = sf::Vector2f();
		point.x = static_cast<float>(range.left + rand() % range.width);
		point.y = static_cast<float>(range.top + rand() % range.height);
		return point;
	}

	float GetLength(const sf::Vector2f& v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}
}
