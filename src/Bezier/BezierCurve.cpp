#include "BezierCurve.h"
#include "HelperFunctions.h"


sf::Vector2f BezierCurve::GetValue(float t) const
{
	sf::Vector2f p(0, 0);
	int n =Points.size() - 1;
	for (int i = 0; i <= n; i++)
	{
		float k = (float)HelperFunctions::CalcFactorial(n) /
			(HelperFunctions::CalcFactorial(i) * HelperFunctions::CalcFactorial(n - i));
		for (int _ = 0; _ < i; _++)
			k *= t;
		for (int _ = 0; _ < n - i; _++)
			k *= 1 - t;

		p += Points[i] * k;
	}
	return p;
}

BezierCurve::BezierCurve(std::vector<sf::Vector2f> points) : Points(std::move(points))
{
}

