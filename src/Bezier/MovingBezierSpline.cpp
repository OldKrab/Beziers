#include "MovingBezierSpline.h"
#include <algorithm>
#include <iostream>
#include <queue>

#include "HelperFunctions.h"

void MovingBezierSpline::Update(float dt)
{
	if (_curCurve == nullptr || IsEnded())
		return;

	_curProgress += _speedProgress * dt;
	if (IsEnded())
		return;

	while (_curLength > _length && _drawVertexes.size() > 2){
		auto len = HelperFunctions::GetLength(_drawVertexes[1].position - _drawVertexes[0].position);
		_curLength -= len;
		_drawVertexes.erase(_drawVertexes.begin());
	}

	auto pos = _curCurve->GetValue(_curProgress);
	auto dist = HelperFunctions::GetLength(pos - _curPosition);
	_speed = dist / dt;
	_curPosition = pos;
	//std::cout << dist << ' ' << _curLength << std::endl;
	auto c = _color;
	c.a = std::clamp(int(_speed), 100, 255);
	_drawVertexes.push_back({ _curPosition ,c });

	int cnt = _drawVertexes.size();
	_curLength = 0;
	for(int i = 0; i < cnt; i++)
	{
		if(i > 0)
		{
			_curLength += HelperFunctions::GetLength(_drawVertexes[i].position - _drawVertexes[i-1].position);
		}
		int a = std::min(255, i * 255 / cnt + 80);
		_drawVertexes[i].color.a = a;
	}
}

void MovingBezierSpline::AddBezier(sf::Vector2f point, sf::Vector2f controlPoint)
{
	if (_curCurve == nullptr)
	{
		_curCurve = std::make_unique<BezierCurve>(std::vector<sf::Vector2f>{ point, point, point, point });
		return;
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

	float r = 0.0009f * target.getView().getSize().x;
	sf::CircleShape circle(r);
	circle.setPosition(_curPosition);
	circle.setOrigin(r, r );
	circle.setFillColor(_color);
	target.draw(circle);
	/*for (auto&& p : points)
	{
		sf::CircleShape circle(2);
		circle.setPosition(p);
		target.draw(circle);
	}*/
}
