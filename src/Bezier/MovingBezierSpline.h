#pragma once
#include <list>

#include "BezierCurve.h"

class MovingBezierSpline :public sf::Drawable
{
public:
	void Update(float dt);

	void AddBezier(sf::Vector2f point, sf::Vector2f controlPoint);

	void AddRandomBezier(sf::IntRect range);

	bool IsEnded() const { return _curProgress > 1.f - 1e-3f; }

	sf::Vector2f GetCurrentPosition() const { return _curPosition; }

	void SetSpeed(float speed) { _speedProgress = speed; }

	void SetColor(sf::Color color) { _color = color; }

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float _length = 1000, _curLength = 0;
	sf::Color _color = sf::Color::White;
	float _speedProgress = 0.8f;
	float _speed = 0;
	sf::Vector2f _curPosition;
	float _curProgress = 1.f;
	std::unique_ptr<BezierCurve> _curCurve;
	std::vector<sf::Vertex> _drawVertexes;
};
