#include "BezierCurve.h"

sf::Vector2f BezierCurve::GetValue(float t) const
{
	std::vector<sf::Vector2f> curPoints = _points;
	while (curPoints.size() > 1)
	{
		std::vector<sf::Vector2f> nextPoints;
		nextPoints.reserve(curPoints.size() - 1);
		for (size_t i = 0; i < curPoints.size() - 1; i++)
			nextPoints.push_back({ curPoints[i] + (curPoints[i + 1] - curPoints[i]) * t });
		curPoints = std::move(nextPoints);
	}
	return curPoints[0];
}

BezierCurve::BezierCurve(std::vector<sf::Vector2f> points) : _points(std::move(points))
{
}

