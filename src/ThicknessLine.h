#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>

class ThicknessLine
{
public:
	static void Draw(sf::RenderTarget& window, const std::vector<sf::Vertex>& vertexes, float thickness);

};
