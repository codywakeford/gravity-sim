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
        sf::Vector2f pos(mousePos.x, mousePos.y );
        Satellite body(pos, radius, velocity, sf::Color::Green);
        bodies.push_back(body);
    }

    void update() {
        calculate_forces();
        handle_collisions();
    }

private:
    void calculate_forces() {
        for (Satellite& body : bodies) {
            body.force = {0.0f, 0.0f};

            float minDistance = 50.0f;
            float dampingFactor = 0.2f;
            float bigG = 0.1f;

            float forceX = 0.0f;
            float forceY = 0.0f;

            for (Satellite &body2 : bodies) {
                
                if (&body == &body2) continue;

                int massProduct = body.mass * body2.mass;

                float dX = body2.position.x - body.position.x;
                float dY = body2.position.y - body.position.y;
                

                float distanceSquared = dX * dX + dY * dY;
                float distance = std::sqrt(distanceSquared);

                if (distance < minDistance) {
                    float forceMagnitude = (bigG * body.mass * body2.mass) / (distanceSquared + minDistance);
                    dX *= dampingFactor;
                    dY *= dampingFactor;
                    body.force.x += forceMagnitude * (dX / distance);
                    body.force.y += forceMagnitude * (dY / distance);
                    continue; 
                }

                float forceMagnitude = (bigG * massProduct) / distanceSquared;

                forceX += forceMagnitude * (dX / distance);
                forceY += forceMagnitude * (dY / distance);
            }

            sf::Vector2f force(forceX, forceY);
            body.force = force;
            body.update();

        }
    }

    void handle_collisions() {  
        for (size_t i = 0; i < bodies.size(); i++) {
            for (size_t j = i + 1; j < bodies.size(); j++) {
                Satellite& body1 = bodies[i];
                Satellite& body2 = bodies[j];

                float dX = body1.position.x - body2.position.x;
                float dY = body2.position.y - body2.position.y;
                float distance = std::sqrt(dX * dX + dY * dY);

                if (distance < (body2.radius + body1.radius)) {
                    float overlap = distance - (body2.radius - body2.radius);
                }
            }
        }
    }

    bool areCirclesOverlapping(const sf::Vector2f& pos1, float radius1, const sf::Vector2f& pos2, float radius2) {
        float dx = pos2.x - pos1.x;
        float dy = pos2.y - pos1.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        return distance <= (radius1 + radius2);
    }
};

extern GameObjects gameObjects;

#endif // GAME_OBJECTS_HPP
