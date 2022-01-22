#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace HelperFunctions
{
	sf::Vector2f GetRandomPoint(sf::IntRect range);
	float GetLength(const sf::Vector2f& v);
	sf::Vector2f GetNormal(const sf::Vector2f& v);
	float Dot(const sf::Vector2f& v, const sf::Vector2f& u);
	int CalcFactorial(int n);
	sf::Color GetGradientRgbColor(float t);
	sf::Color GetGradientColor(float t);
}

