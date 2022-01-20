#include "InputHandler.h"
#include <SFML/Window/Window.hpp>

void InputHandler::AddKeyHandler(sf::Keyboard::Key key, const std::function<void(sf::Event)>& handler)
{
	_keyHandlers.emplace(key, handler);
}

void InputHandler::AddMouseButtonHandler(sf::Mouse::Button button, std::function<void(sf::Event)> handler)
{
	_mouseHandlers.emplace(button, handler);
}

void InputHandler::AddEventHandler(sf::Event::EventType event, const std::function<void(sf::Event)>& handler)
{
	_eventHandlers.emplace(event, handler);
}

void InputHandler::Update() const
{
	sf::Event event{};
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed &&  _keyHandlers.contains(event.key.code))
			_keyHandlers.at(event.key.code)(event);
		else if(event.type == sf::Event::MouseButtonPressed && _mouseHandlers.contains(event.mouseButton.button))
			_mouseHandlers.at(event.mouseButton.button)(event);
		else if(_eventHandlers.contains(event.type))
			_eventHandlers.at(event.type)(event);
	}
}
