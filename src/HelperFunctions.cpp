#include "HelperFunctions.h"

#include <iostream>
#include <vector>

namespace HelperFunctions
{
	sf::Vector2f GetRandomPoint(sf::IntRect range)
	{
		auto point = sf::Vector2f();
		point.x = static_cast<float>(range.left + rand() % range.width);
		point.y = static_cast<float>(range.top + rand() % range.height);
		return point;
	}

	float GetLength(const sf::Vector2f& v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}



	int CalcFactorial(int n)
	{
		static std::vector<int> mem(100, 0);
		if(mem[n] != 0)
			return mem[n];
		int res = 1;
		for(int i = 2; i <= n; i++)
			res *= i;
		return mem[n] = res;
	}
}
