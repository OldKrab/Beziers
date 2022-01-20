#pragma once
#include <SFML/Graphics.hpp>

class BezierCurve
{
public:
	explicit BezierCurve(std::vector<sf::Vector2f> points);

	sf::Vector2f GetValue(float t) const;

	std::vector<sf::Vector2f> Points;

};


