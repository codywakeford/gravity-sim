#include <SFML/Graphics.hpp>
#include "Satellite.hpp"
#include "Mouse.hpp"
#include "GameObjects.hpp"

// Handle user inputs
void processEvents(sf::RenderWindow& window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
        gameObjects.clear();
    }

    mouse.input(event, window);
}

