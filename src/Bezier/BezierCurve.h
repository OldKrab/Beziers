#pragma once
#include <SFML/Graphics.hpp>
#include "MovingPoint.h"

class BezierCurve
{
public:
	explicit BezierCurve(std::vector<sf::Vector2f> points);

	sf::Vector2f GetValue(float t) const;

	const std::vector<sf::Vector2f>& GetPoints() const { return  _points; }

protected:
	std::vector<sf::Vector2f> _points;

};


