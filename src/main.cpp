#include <SFML/Graphics.hpp>
#include <format>

#include "HelperFunctions.h"
#include "InputHandler.h"
#include "Scene.h"
#include "Constants.h"

void ScrollView(sf::RenderWindow& window, float delta) {
    auto view = window.getView();
    if (delta < 0 || view.getSize().x < 30000 && view.getSize().y < 30000)
        view.setSize(view.getSize() * (1 + delta * 0.1f));
    window.setView(view);
}

int main() {
    srand(time(nullptr));

    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "SFML Window");
    // window.create(sf::VideoMode::getFullscreenModes()[0], "SFML Window", sf::Style::Fullscreen);

    InputHandler inputHandler;
    Scene scene(&window, &inputHandler);
    for (int i = 0; i < INIT_SPLINES_COUNT; i++)
        scene.GenerateSpline();

    bool isBlackBackground = true;

    inputHandler.AddEventHandler(sf::Event::Closed, [&window](auto) { window.close(); });
    inputHandler.AddKeyPressedHandler(sf::Keyboard::Escape, [&window](auto) { window.close(); });
    inputHandler.AddEventHandler(sf::Event::MouseWheelScrolled, [&window](auto e) { ScrollView(window, -e.mouseWheelScroll.delta); });
    inputHandler.AddKeyPressedHandler(sf::Keyboard::R, [&scene](auto) { scene.Reset(); });
    inputHandler.AddEventHandler(sf::Event::MouseButtonPressed, [&scene](auto) { scene.SetGenerate(true); });
    inputHandler.AddEventHandler(sf::Event::MouseButtonReleased, [&scene](auto) { scene.SetGenerate(false); });
    inputHandler.AddKeyPressedHandler(sf::Keyboard::LControl, [&scene](auto) { scene.SetMouseFollowing(true); });
    inputHandler.AddKeyReleasedHandler(sf::Keyboard::LControl, [&scene](auto) { scene.SetMouseFollowing(false); });
    inputHandler.AddKeyReleasedHandler(sf::Keyboard::Space, [&isBlackBackground](auto) { isBlackBackground = !isBlackBackground; });
    inputHandler.AddKeyReleasedHandler(sf::Keyboard::D, [](auto) { MovingBezierSpline::isDrawCurve = !MovingBezierSpline::isDrawCurve; });

    sf::Clock clock;

    sf::Time fps = sf::seconds(1./120);
    while (window.isOpen()) {
        while(clock.getElapsedTime() < fps){
            sf::sleep(fps - clock.getElapsedTime());
        }
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        inputHandler.Update(window);
        scene.Update(dt);

        if (isBlackBackground)
            window.clear(sf::Color::Black);
        else
            window.clear(sf::Color::White);

        window.draw(scene);
        window.display();
    }

    return 0;
}
