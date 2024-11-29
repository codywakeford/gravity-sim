#include <SFML/Graphics.hpp>
#include "GameObjects.hpp"
#include "Mouse.hpp"

// All drawing to the window happens in here.
void render(sf::RenderWindow& window) {  
    window.clear(sf::Color::Black);

    mouse.render(window);
    gameObjects.render(window);

    window.display();
}