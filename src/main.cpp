#include <SFML/Graphics.hpp>
#include <format>

#include "HelperFunctions.h"
#include "InputHandler.h"
#include "Scene.h"


void ScrollView(sf::RenderWindow& window, float delta)
{
	auto view = window.getView();
	if (delta < 0 || view.getSize().x < 30000 && view.getSize().y < 30000)
		view.setSize(view.getSize() * (1 + delta * 0.1f));
	window.setView(view);
}

int main()
{
	srand(time(nullptr));

	sf::RenderWindow window;
	window.create(sf::VideoMode(1500, 800), "SFML Window");
	window.create(sf::VideoMode::getFullscreenModes()[0], "SFML Window", sf::Style::Fullscreen);

	InputHandler inputHandler;
	Scene scene(&window, &inputHandler);
	//scene.GenerateSpline();

	bool isBlackBackground = true;

	inputHandler.AddEventHandler(sf::Event::Closed, [&window](auto) {window.close(); });
	inputHandler.AddKeyPressedHandler(sf::Keyboard::Escape, [&window](auto) {window.close(); });
	inputHandler.AddEventHandler(sf::Event::MouseWheelScrolled, [&window](auto e) {ScrollView(window, -e.mouseWheelScroll.delta); });
	inputHandler.AddKeyPressedHandler(sf::Keyboard::R, [&scene](auto) {scene.Reset(); });
	inputHandler.AddEventHandler(sf::Event::MouseButtonPressed, [&scene](auto) {scene.SetGenerate(true); });
	inputHandler.AddEventHandler(sf::Event::MouseButtonReleased, [&scene](auto) {scene.SetGenerate(false); });
	inputHandler.AddKeyPressedHandler(sf::Keyboard::LControl, [&scene](auto) {scene.SetMouseFollowing(true); });
	inputHandler.AddKeyReleasedHandler(sf::Keyboard::LControl, [&scene](auto) {scene.SetMouseFollowing(false); });
	inputHandler.AddKeyReleasedHandler(sf::Keyboard::Space, [&isBlackBackground](auto) {isBlackBackground = !isBlackBackground; });


	sf::Clock clock;

	while (window.isOpen())
	{
		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		inputHandler.Update(window);
		scene.Update(dt);

		if(isBlackBackground)
		window.clear(sf::Color::Black);
		else
		window.clear(sf::Color::White);

		window.draw(scene);
		window.display();
	}

	return 0;
}
