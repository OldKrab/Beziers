#pragma once
#include <SFML/Graphics.hpp>
#include "MovingPoint.h"

class BezierCurve:public sf::Drawable
{
public:
	sf::Vector2f GetValue(float t) const;

	explicit BezierCurve(const std::vector<MovingPoint>& points);

	void AddPoint(const MovingPoint& point, int index);

	void Update(float dt);

	bool ShowPoints = false;
	sf::Color Color = sf::Color::Cyan;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<MovingPoint> _points;
	int _drawPointCount = 300;
};


