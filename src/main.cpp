#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

#include "Bezier/MovingBezierSpline.h"
#include "HelperFunctions.h"

int main()
{
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(1520, 850), "SFML works!");
	sf::View view(sf::FloatRect({ 0,0 }, { 500,500 }));
	window.setView(view);

	MovingBezierSpline spline;

	sf::Clock clock;
	sf::Vector2i mousePos;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseMoved)
				mousePos = { event.mouseMove.x, event.mouseMove.y };
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				auto scrollDelta = -event.mouseWheelScroll.delta;
				sf::Vector2f scroll{ 100,100 };
				if (scrollDelta > 0 || view.getSize().x > scroll.x*scrollDelta && view.getSize().y > scroll.y*scrollDelta)
					view.setSize(view.getSize() + scrollDelta * scroll);
			}
		}

		float dt = clock.getElapsedTime().asSeconds();
		//float dt = 0.01;
		clock.restart();

		spline.Update(dt);
		if (spline.IsEnded())
		{
			sf::Vector2i lt(-10, -10), rb(10, 10);
			sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
			auto v = (worldPos - spline.GetCurrentPosition());
			auto delta = (int)sqrt(v.x * v.x + v.y * v.y)+1;

			auto pos = worldPos;
			// convert it to world coordinates
			auto p = pos + HelperFunctions::GetRandomPoint({ lt, rb - lt });
			auto p2 = pos + HelperFunctions::GetRandomPoint({ {-delta, -delta},{2 * delta, 2 * delta} });

			spline.AddBezier(p, p2);
		}
		view.setCenter(spline.GetCurrentPosition());
		window.setView(view);

		window.clear();

		window.draw(spline);

		window.display();
	}

	return 0;
}
