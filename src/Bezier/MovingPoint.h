#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class MovingPoint :public sf::Drawable
{

public:
	void Update(float dt);

	explicit MovingPoint(sf::RenderWindow* window)
		: _window(window)
	{
	}

	sf::Vector2f Position, Speed = { 110, 230 };
	sf::Color Color = sf::Color::Cyan;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RenderWindow* _window;
};
