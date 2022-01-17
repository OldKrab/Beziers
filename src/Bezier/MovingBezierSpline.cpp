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

	_curPosition =  _curCurve->GetValue(_curProgress);
	_drawVertexes.push_back({ _curPosition ,_color });

	int cnt = _drawVertexes.size();

	static float dtSum = 0;
	dtSum += dt;
	if (dtSum*_decaySpeed > 1) {
		for (int i = 0; i < cnt; i++)
		{
			_drawVertexes[i].color.a = std::max(0, _drawVertexes[i].color.a - (sf::Uint8)(dtSum*_decaySpeed));
		}
		dtSum =0;
	}
	_drawVertexes.erase(std::remove_if(_drawVertexes.begin(), _drawVertexes.end(),
		[](sf::Vertex v) {return v.color.a == 0; }), _drawVertexes.end());
}

void MovingBezierSpline::AddBezier(sf::Vector2f point, sf::Vector2f controlPoint)
{
	if (_curCurve == nullptr)
	{
		_curCurve = std::make_unique<BezierCurve>(std::vector<sf::Vector2f>{ point, point, point, point });
		_curPosition = point;
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
	circle.setOrigin(r, r);
	circle.setFillColor(_color);
	target.draw(circle);
	/*for (auto&& p : points)
	{
		sf::CircleShape circle(2);
		circle.setPosition(p);
		target.draw(circle);
	}*/
}
