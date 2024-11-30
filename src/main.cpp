#include <SFML/Graphics.hpp>
#include "inputs.cpp"
#include "step.cpp"
#include "render.cpp"
#include "GameObjects.hpp" 
#include "Mouse.hpp"
#include "window.cpp"
// #include "Slider.hpp"

GameObjects gameObjects;
Mouse mouse;

void awaitFrame(sf::Clock clock)
{
    sf::Time deltaTime = clock.restart();
    if (deltaTime.asSeconds() < TIME_PER_FRAME) {
        sf::sleep(sf::seconds(TIME_PER_FRAME - deltaTime.asSeconds()));
    }
    clock.restart();
}

int main() {

    window.setFramerateLimit(120);
    sf::Clock clock;

    // 120hz loop
    while (window.isOpen()) {
        processEvents(window);
        step(window);
        render(window);
        awaitFrame(clock);
    }

    return 0;
}

