#include <SFML/Graphics.hpp>
#include "Mouse.hpp"
#include "GameObjects.hpp"
#include "QuadTree.hpp"
#include "Text.hpp"

#ifndef STATE_HPP
#define STATE_HPP

int WINDOW_HEIGHT = 1080;
int WINDOW_WIDTH = 1920;
int FPS = 165;
const float TIME_PER_FRAME = 1.0f / FPS;

class State {
private:
    sf::Clock clock;

public:
    Mouse mouse;
    GameObjects gameObjects;
    Quadtree quadtree;
    sf::RenderWindow window;
    
    bool isPaused = false;

    State() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity"), quadtree(Rectangle(960, 540, 1920, 1080)) {
        window.setFramerateLimit(FPS);
    }

    void handle_inputs(sf::RenderWindow& window) {
        sf::Event event;

        while (window.pollEvent(event)) {
        // Check for key press events inside the event loop
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                gameObjects.clear();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                isPaused = !isPaused;
            }
        }

        mouse.input(event, window, gameObjects);
    }

    void update(sf::RenderWindow& window) {
        gameObjects.update(quadtree);
        Text::updateAllText();
    }

    void render(sf::RenderWindow& window) {
        window.clear(sf::Color::Black);

        mouse.render(window);
        quadtree.render(window);
        gameObjects.render(window);
        Text::renderAllText(window); 

        window.display();
    }

    void awaitFrame() {
        sf::Time deltaTime = clock.restart();
        if (deltaTime.asSeconds() < TIME_PER_FRAME) {
            sf::sleep(sf::seconds(TIME_PER_FRAME - deltaTime.asSeconds()));
        }
        clock.restart();
    }
};

#endif
