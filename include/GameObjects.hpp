#include <SFML/Graphics.hpp>
#include "Satellite.hpp"
#include <iostream>

#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

class GameObjects {
public:
    std::vector<Satellite> bodies;

    GameObjects() {};

    void render(sf::RenderWindow& window) {
        for (Satellite& body : this->bodies) {
            body.render(window);
        }
    }

    void add_satellite(float radius, sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        Satellite body(mousePos.x - radius, mousePos.y - radius, radius, sf::Color::Green);
        bodies.push_back(body);
    }

};

extern GameObjects gameObjects;

#endif // GAME_OBJECTS_HPP
