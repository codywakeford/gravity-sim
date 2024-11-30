#include <SFML/Graphics.hpp>
#include "Satellite.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

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

    void add_satellite(float radius, sf::Vector2f velocity, sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f pos(mousePos.x - radius, mousePos.y - radius);
        Satellite body(pos, radius, velocity, sf::Color::Green);
        bodies.push_back(body);
    }

    void update() {
        calculate_forces();
    }

private:
    void calculate_forces() {
        for (Satellite& body : bodies) {
            body.force = {0.0f, 0.0f};


            float bigG = 6.67;

            float forceX = 0.0f;
            float forceY = 0.0f;

            for (Satellite &body2 : bodies) {
                
                if (&body == &body2) {
                    continue;
                }

                int massProduct = body.mass * body2.mass;
                
                float dX = body2.position.x - body.position.x;
                float dY = body2.position.y - body.position.y;
                
                float distanceSquared = dX * dX + dY * dY;
                
                if (distanceSquared == 0.0f) continue;

                float distance = std::sqrt(distanceSquared);
                float forceMagnitude = (bigG * massProduct) / distanceSquared;

                forceX += forceMagnitude * (dX / distance);
                forceY += forceMagnitude * (dY / distance);
            }

            sf::Vector2f force(forceX, forceY);
            body.force = force;
            body.update();

            std::cout << "Force: " << body.force.x << ", " << body.force.y << std::endl;
            std::cout << "Velocity: " << body.velocity.x << ", " << body.velocity.y << std::endl;
            std::cout << "Position: " << body.position.x << ", " << body.position.y << std::endl;

        }
    }
};

extern GameObjects gameObjects;

#endif // GAME_OBJECTS_HPP
