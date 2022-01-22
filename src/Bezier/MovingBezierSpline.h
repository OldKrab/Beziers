#pragma once
#include "BezierCurve.h"
#include "HelperFunctions.h"

class MovingBezierSpline :public sf::Drawable
{
public:
	void Update(float dt);

	void AddBezier(sf::Vector2f point, sf::Vector2f controlPoint);

	void AddRandomBezier(sf::IntRect range);

	bool IsEnded() const { return _curProgress > 1.f - 1e-3f; }

	sf::Vector2f GetCurrentPosition() const { return _curPosition; }

	void SetSpeed(float speed) { _speedProgress = speed; }

	void SetColor(float t) { _color = HelperFunctions::GetGradientRgbColor(t); _colorGradient = t;}

	void MovePosition(sf::Vector2f vec);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Color _color = sf::Color::White;
	float _colorGradient = 0;
	float _speedProgress = 0.8f, _decaySpeed = 255;
	sf::Vector2f _curPosition;
	float _curProgress = 1.f;
	float _thickness = 5;
	std::unique_ptr<BezierCurve> _curCurve;
	std::vector<sf::Vertex> _drawVertexes;
};
