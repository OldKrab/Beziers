#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace HelperFunctions
{
	sf::Vector2f GetRandomPoint(sf::IntRect range);
	float GetLength(const sf::Vector2f& v);
	int CalcFactorial(int n);
}

