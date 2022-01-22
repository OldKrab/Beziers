#include "ThicknessLine.h"
#include "HelperFunctions.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

void ThicknessLine::Draw(sf::RenderTarget& window, const std::vector<sf::Vertex>& vertexes, float thickness)
{
	if (vertexes.size() < 2)
		return;
	std::vector<sf::Vertex> triangles;
	triangles.reserve(vertexes.size() * 2);


	auto p0 = vertexes[0].position;
	auto p1 = vertexes[1].position;
	sf::Vector2f line = p1 - p0;
	sf::Vector2f normal = HelperFunctions::GetNormal({ -line.y, line.x });
	triangles.emplace_back(p0 - normal * thickness, vertexes[0].color);
	triangles.emplace_back(p0 + normal * thickness, vertexes[0].color);

	for (size_t i = 2; i < vertexes.size(); i++) {
		p0 = vertexes[i - 2].position;
		p1 = vertexes[i - 1].position;
		auto p2 = vertexes[i].position;
		line = p1 - p0;
		normal = HelperFunctions::GetNormal({ -line.y, line.x });
		sf::Vector2f tangent = HelperFunctions::GetNormal(HelperFunctions::GetNormal(p2 - p1) + HelperFunctions::GetNormal(p1 - p0));

		sf::Vector2f miter = sf::Vector2f(-tangent.y, tangent.x);
		float length = thickness * HelperFunctions::Dot(miter, normal);
		if (std::abs(HelperFunctions::GetLength(normal)) < 0.01f)
			std::cout << HelperFunctions::GetLength(normal) << std::endl;
		sf::Vector2f m1 = p1 - length * miter;
		sf::Vector2f m2 = p1 + length * miter;

		triangles.emplace_back(m1, vertexes[i - 1].color);
		triangles.emplace_back(m2, vertexes[i - 1].color);
	}

	p0 = vertexes[vertexes.size() - 2].position;
	p1 = vertexes[vertexes.size() - 1].position;
	line = p1 - p0;
	normal = HelperFunctions::GetNormal({ -line.y, line.x });
	triangles.emplace_back(p1 - normal * thickness, vertexes[vertexes.size() - 1].color);
	triangles.emplace_back(p1 + normal * thickness, vertexes[vertexes.size() - 1].color);
	window.draw(triangles.data(), triangles.size(), sf::TriangleStrip);
}
