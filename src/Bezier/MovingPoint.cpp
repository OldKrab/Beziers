#include "MovingPoint.h"

#include <SFML/Graphics/CircleShape.hpp>

void MovingPoint::Update(float dt)
{
	Position += Speed * dt;
	if (Position.x > _window->getSize().x)
	{
		Position.x = _window->getSize().x;
		Speed.x *= -1;
	}
	if (Position.x < 0)
	{
		Position.x = 0;
		Speed.x *= -1;
	}
	if (Position.y > _window->getSize().y)
	{
		Position.y = _window->getSize().y;
		Speed.y *= -1;
	}
	if (Position.y < 0)
	{
		Position.y = 0;
		Speed.y *= -1;
	}
}

void MovingPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::CircleShape shape(2);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(Position);
	target.draw(shape);
}
