#include "HelperFunctions.h"

#include <iostream>
#include <vector>

namespace HelperFunctions
{
	sf::Vector2f GetRandomPoint(sf::IntRect range)
	{
		sf::Vector2f point;
		point.x = static_cast<float>(range.left + rand() % range.width);
		point.y = static_cast<float>(range.top + rand() % range.height);
		return point;
	}

	float GetLength(const sf::Vector2f& v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	sf::Vector2f GetNormal(const sf::Vector2f& v)
	{
		auto len = GetLength(v);
		return { v.x / len, v.y / len };
	}

	float Dot(const sf::Vector2f& v, const sf::Vector2f& u)
	{
		return v.x * u.x + v.y * u.y;
	}


	int CalcFactorial(int n)
	{
		static std::vector<int> mem(100, 0);
		if (mem[n] != 0)
			return mem[n];
		int res = 1;
		for (int i = 2; i <= n; i++)
			res *= i;
		return mem[n] = res;
	}

	sf::Color GetGradientRgbColor(float t)
	{
		t *= 5;
		float rt = abs(6 - (t > 3 ? t : 6 + t));
		float gt = abs(2 - t);
		float bt = abs(4 - t);
		auto r = static_cast<sf::Uint8>(255 * (rt < 1 ? 1 : std::max(0.f, 2 - rt)));
		auto g = static_cast<sf::Uint8>(255 * (gt < 1 ? 1 : std::max(0.f, 2 - gt)));
		auto b = static_cast<sf::Uint8>(255 * (bt < 1 ? 1 : std::max(0.f, 2 - bt)));
		return {r, g, b};
	}

	sf::Color GetGradientColor(float t)
	{
		t *= 3;
		float bt = abs(1 - t);
		auto r = static_cast<sf::Uint8>(255 * std::clamp(t - 1, 0.f, 1.f));
		auto g = static_cast<sf::Uint8>(255 * std::max(0.f, t - 2));
		auto b = static_cast<sf::Uint8>(255 * (t < 2 ? std::max(0.f, 1 - bt) : t - 2));
		return {r, g, b};
	}


}