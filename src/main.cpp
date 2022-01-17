#include <SFML/Graphics.hpp>

#include "Bezier/MovingBezierSpline.h"
#include "HelperFunctions.h"

sf::RenderWindow window;
int splinesCount = 1;
std::vector<MovingBezierSpline> splines;
bool isMousePressed = false, isFirstGenerate = true;
float generateTimeDelta = 0.01f, timeSum = 0.f, secondGenerateTime = 1;
sf::Vector2i mousePos;

void Generate()
{
	auto&& spline = splines.emplace_back();
	auto dest = window.mapPixelToCoords(mousePos);
	spline.AddBezier(dest, dest);
	spline.SetColor(sf::Color(rand() % 200 + 55,rand() % 200 + 55, rand() % 200 + 55));
	spline.SetSpeed((float)(rand() % 300) / 1000 + 0.4f);
}

int main()
{
	srand(time(0));

	//window.create(sf::VideoMode(1000, 600), "SFML Window");
	window.create(sf::VideoMode::getFullscreenModes()[0], "SFML Window", sf::Style::Fullscreen);
	sf::View view(sf::FloatRect({ 0,0 }, { 1520,850 }));
	window.setView(view);

	for (int i = 0; i < splinesCount; i++) {
		Generate();
	}

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.type == sf::Event::MouseMoved)
				mousePos = { event.mouseMove.x, event.mouseMove.y };
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				auto scrollDelta = -event.mouseWheelScroll.delta;

				if (scrollDelta < 0 || view.getSize().x < 30000 && view.getSize().y < 30000)
					view.setSize(view.getSize() * (1 + scrollDelta * 0.1f));
			}
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				splines.erase(splines.begin() + 1, splines.end());
				splinesCount = 1;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				isMousePressed = true;
				isFirstGenerate = true;
				timeSum = 0;
				Generate();
			}
			if(event.type == sf::Event::MouseButtonReleased)
				isMousePressed = false;
		}

		if (isMousePressed)
		{
			bool isGenerate = false;
			if (isFirstGenerate && timeSum > secondGenerateTime)
			{
				isFirstGenerate = false;
				timeSum = 0;
				isGenerate = true;
			}
			else if (!isFirstGenerate && timeSum > generateTimeDelta)
			{
				timeSum = 0;
				isGenerate = true;
			}
			if (isGenerate) {
				Generate();
			}
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
				delta = std::max(delta, 50);
				auto pos = worldPos;

				sf::Vector2f p1 = pos, p2 = pos;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
					p1 += HelperFunctions::GetRandomPoint({ lt, rb - lt });
					p2 += HelperFunctions::GetRandomPoint({ lt, rb - lt });
				}
				else {
					p1 += HelperFunctions::GetRandomPoint({ {-delta / 2, -delta / 2},{delta,  delta} });
					p2 += HelperFunctions::GetRandomPoint({ {-delta / 2, -delta / 2},{delta,  delta} });
				}
				splines[i].AddBezier(p1, p2);
			}
			sum += splines[i].GetCurrentPosition();
		}

		auto prevCenter = view.getCenter();
		auto curCenter = sum / (float)splines.size();
		auto centerDelta = curCenter - prevCenter;
		auto dist = HelperFunctions::GetLength(centerDelta);
		auto curDist = dist * dt * 10;
		curCenter = prevCenter + curDist / dist * centerDelta;
		view.setCenter(curCenter);
		window.setView(view);

		window.clear();
		for (const auto& spline : splines)
			window.draw(spline);

		window.display();
	}

	return 0;
}
