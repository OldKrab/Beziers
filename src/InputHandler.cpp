#include "InputHandler.h"
#include <SFML/Window/Window.hpp>

void InputHandler::AddKeyPressedHandler(sf::Keyboard::Key key, const std::function<void(sf::Event)>& handler)
{
	_keyPressedHandlers.emplace(key, handler);
}

void InputHandler::AddKeyReleasedHandler(sf::Keyboard::Key key, const std::function<void(sf::Event)>& handler)
{
	_keyReleasedHandlers.emplace(key, handler);
}

void InputHandler::AddMouseButtonHandler(sf::Mouse::Button button, std::function<void(sf::Event)> handler)
{
	_mouseHandlers.emplace(button, handler);
}

void InputHandler::AddEventHandler(sf::Event::EventType event, const std::function<void(sf::Event)>& handler)
{
	_eventHandlers.emplace(event, handler);
}

void InputHandler::Update(sf::Window& window) 
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		if(event.type == sf::Event::MouseMoved)
			_mousePosition = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
		else if (event.type == sf::Event::KeyPressed &&  _keyPressedHandlers.contains(event.key.code))
			_keyPressedHandlers.at(event.key.code)(event);
		else if (event.type == sf::Event::KeyReleased &&  _keyReleasedHandlers.contains(event.key.code))
			_keyReleasedHandlers.at(event.key.code)(event);
		else if(event.type == sf::Event::MouseButtonPressed && _mouseHandlers.contains(event.mouseButton.button))
			_mouseHandlers.at(event.mouseButton.button)(event);
		else if(_eventHandlers.contains(event.type))
			_eventHandlers.at(event.type)(event);
	}
}
