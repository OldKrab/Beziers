#pragma once
#include <functional>
#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class InputHandler
{
public:
	InputHandler(sf::Window* window) : window(window) {}
	void AddKeyHandler(sf::Keyboard::Key key, const std::function<void(sf::Event)>& handler);
	void AddMouseButtonHandler(sf::Mouse::Button button, std::function<void(sf::Event)> handler);
	void AddEventHandler(sf::Event::EventType event, const std::function<void(sf::Event)>& handler);
	void Update() const;
private:
	std::map<sf::Keyboard::Key, std::function<void(sf::Event)>> _keyHandlers;
	std::map<sf::Mouse::Button, std::function<void(sf::Event)>> _mouseHandlers;
	std::map<sf::Event::EventType, std::function<void(sf::Event)>> _eventHandlers;
	sf::Window* window;

};
