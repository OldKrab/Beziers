#pragma once
#include <functional>
#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class InputHandler
{
public:
	InputHandler() {}
	void AddKeyPressedHandler(sf::Keyboard::Key key, const std::function<void(sf::Event)>& handler);
	void AddKeyReleasedHandler(sf::Keyboard::Key key, const std::function<void(sf::Event)>& handler);
	void AddMouseButtonHandler(sf::Mouse::Button button, std::function<void(sf::Event)> handler);
	void AddEventHandler(sf::Event::EventType event, const std::function<void(sf::Event)>& handler);
	void Update(sf::Window& window);

	sf::Vector2i GetMousePosition() const { return _mousePosition; }
private:
	std::map<sf::Keyboard::Key, std::function<void(sf::Event)>> _keyPressedHandlers;
	std::map<sf::Keyboard::Key, std::function<void(sf::Event)>> _keyReleasedHandlers;
	std::map<sf::Mouse::Button, std::function<void(sf::Event)>> _mouseHandlers;
	std::map<sf::Event::EventType, std::function<void(sf::Event)>> _eventHandlers;

	sf::Vector2i _mousePosition;

};
