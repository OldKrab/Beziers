#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

#include "Bezier/MovingBezierSpline.h"
#include "HelperFunctions.h"

int main()
{
	srand(time(0));

	//sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML Window");
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "SFML Window", sf::Style::Fullscreen);
	sf::View view(sf::FloatRect({ 0,0 }, { 1520,850 }));
	window.setView(view);

	int curvesCount = 1;
	std::vector<MovingBezierSpline> splines(curvesCount);
	for (int i = 0; i < curvesCount; i++) {
		splines[i].SetColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		splines[i].SetSpeed((float)(rand() % 200) / 1000 + 0.4f);
	}

	sf::Clock clock;
	sf::Vector2i mousePos;
	bool mousePressed = false;
	float timeToGenerate = 0.01f, timeSum = 0.f;
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

				if (scrollDelta < 0 || view.getSize().x < 30000 && view.getSize().y < 30000)
					view.setSize(view.getSize() * (1 + scrollDelta * 0.1f));
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				mousePressed = true;
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				mousePressed = false;
			}
		}

		if (mousePressed && timeSum > timeToGenerate)
		{
			timeSum = 0;
			splines.emplace_back();
			auto p = window.mapPixelToCoords(mousePos);
			splines.back().AddBezier(p, p );
			splines.back().SetColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
			splines.back().SetSpeed((float)(rand() % 200) / 1000 + 0.4f);
		}



		float dt = clock.getElapsedTime().asSeconds();
		timeSum += dt;
		//float dt = 0.01;
		clock.restart();

		sf::Vector2f sum(0, 0);
		for (int i = 0; i < splines.size(); i++) {
			splines[i].Update(dt);

			if (splines[i].IsEnded())
			{
				sf::Vector2i lt(-20, -20), rb(20, 20);
				sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
				auto delta = (int)HelperFunctions::GetLength(worldPos - splines[i].GetCurrentPosition());
				delta = std::max(delta, 500);
				auto pos = worldPos;

				sf::Vector2f p1 = pos, p2 = pos;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					p1 +=  HelperFunctions::GetRandomPoint({ lt, rb-lt });
					p2 += HelperFunctions::GetRandomPoint({ lt, rb-lt });
				}
				else {
					p1 += HelperFunctions::GetRandomPoint({ {-delta / 2, -delta / 2},{delta,  delta} });
					p2 += HelperFunctions::GetRandomPoint({ {-delta / 2, -delta / 2},{delta,  delta} });
				}
				splines[i].AddBezier(p1, p2);
			}
			sum += splines[i].GetCurrentPosition();
		}
		view.setCenter(sum / (float)splines.size());
		window.setView(view);

		window.clear();
		for (int i = 0; i < splines.size(); i++)
			window.draw(splines[i]);

		window.display();
	}

	return 0;
}
