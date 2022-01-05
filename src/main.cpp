#include <list>
#include <SFML/Graphics.hpp>

#include "Bezier/BezierCurve.h"

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(1820, 950), "SFML works!");
	std::vector<BezierCurve> curves;
	std::vector<std::list<BezierCurve>> memory;
	int cnt = 20;
	for (int i = 0; i < 5; i++) {
		MovingPoint p1(&window), p2(&window), p3(&window);
		p1.Position = { 50,50 };
		p2.Position = { 250, 250 };
		p3.Position = { 450, 450 };
		p1.Speed = { 0, 0 };
		p2.Speed = { (float)(rand() % 800), (float)(rand() % 800) };
		p3.Speed = { 0, 0 };

		p1.Speed = { (float)(rand() % 800), (float)(rand() % 800) };
		p3.Speed = { (float)(rand() % 800), (float)(rand() % 800) };


		BezierCurve curve({ p1,p2, p3 });
		curve.Color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
		curves.push_back(curve);
	}
	memory.resize(curves.size());
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased)
			{

				for (auto&& curve : curves) {
					MovingPoint p(&window);
					p.Position = { float(event.mouseButton.x), float(event.mouseButton.y) };
					p.Speed = { (float)(rand() % 400), (float)(rand() % 400) };
					curve.AddPoint(p, 1);

				}
			}
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			{
				for (auto&& curve : curves)
					curve.ShowPoints = !curve.ShowPoints;
			}
		}

		float dt = clock.getElapsedTime().asSeconds();
		//float dt = 0.01;
		for (auto&& curve : curves)
			curve.Update(dt);
		clock.restart();

		window.clear();

		for (int i = 0; i < curves.size(); i++) {
			memory[i].push_back(curves[i]);

			if (memory[i].size() > cnt)
				memory[i].pop_front();


			int j = 0;
			for (auto&& mem : memory[i])
			{
				int a = float(j + 1) / cnt * 255;
				j++;
				mem.Color.a = a;
				window.draw(mem);
			}
		}

		window.display();
	}

	return 0;
}
