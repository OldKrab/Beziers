#include "BezierCurve.h"

#include "sfLine.h"

sf::Vector2f BezierCurve::GetValue(float t) const
{
	std::vector<sf::Vector2f> curPoints(_points.size());
	std::transform(_points.begin(), _points.end(),
		curPoints.begin(), [](auto p) {return p.Position; });
	//curPoints.push_back(_points[0].Position);
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

BezierCurve::BezierCurve(const std::vector<MovingPoint>& points): _points(points)
{
}

void BezierCurve::AddPoint(const MovingPoint& point, int index)
{
	_points.emplace(_points.begin() + index, point);
}

void BezierCurve::Update(float dt)
{
	for (auto&& point : _points)
		point.Update(dt);
}

void BezierCurve::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto prevPoint = GetValue(0);
	for (int i = 1; i <= _drawPointCount; i++)
	{
		float t = static_cast<float>(i) / _drawPointCount;
		auto curPoint = GetValue(t);
		sfLine line(prevPoint, curPoint, Color, 5);
		target.draw(line);
		prevPoint = curPoint;
	}
	if (ShowPoints)
		for (auto&& p : _points)
			target.draw(p);
}
