#include "MovingBezierSpline.h"
#include <algorithm>
#include <iostream>

#include "HelperFunctions.h"

void MovingBezierSpline::Update(float dt)
{
	if (_curCurve == nullptr || IsEnded())
		return;

	_curProgress += _speedProgress * dt;
	if (IsEnded())
		return;

	auto pos = _curCurve->GetValue(_curProgress);
	auto delta = pos - _curPosition;
	auto dist = sqrt(delta.x * delta.x + delta.y * delta.y);
	_speed = dist / dt;
	std::cout << _speed << std::endl;
	_curPosition = _curCurve->GetValue(_curProgress);

	auto c = _color;
	c.a = std::clamp(int(_speed), 100, 255);
	_drawVertexes.push_back({ _curPosition ,c });

	if (_drawVertexes.size() > 50000)
		_drawVertexes.erase(_drawVertexes.begin());
}

void MovingBezierSpline::AddBezier(sf::Vector2f point, sf::Vector2f controlPoint)
{
	if (_curCurve == nullptr)
	{
		_curCurve = std::make_unique<BezierCurve>(std::vector<sf::Vector2f>{ point, point, point, point });
	}
	const auto& prevPoints = _curCurve->GetPoints();
	auto prevPoint = prevPoints[prevPoints.size() - 1];
	auto prevControlPoint = prevPoints[prevPoints.size() - 2];
	auto firstControlPoint = prevPoint + (prevPoint - prevControlPoint);
	_curCurve = std::make_unique<BezierCurve>(std::vector<sf::Vector2f>{ prevPoint, firstControlPoint, controlPoint, point });
	_curProgress = 0;
}

void MovingBezierSpline::AddRandomBezier(sf::IntRect range)
{
	AddBezier(_curPosition + HelperFunctions::GetRandomPoint(range), _curPosition + HelperFunctions::GetRandomPoint(range));
}

void MovingBezierSpline::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_drawVertexes.data(), _drawVertexes.size(), sf::LineStrip);
	const auto& points = _curCurve->GetPoints();
	for (auto&& p : points)
	{
		sf::CircleShape circle(2);
		circle.setPosition(p);
		target.draw(circle);
	}
}
