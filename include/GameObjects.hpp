#include <SFML/Graphics.hpp>
#include "Satellite.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "utils.hpp"
#include "vector_math_utils.hpp"
#include "QuadTree.hpp"

#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

class GameObjects {
public:
    std::vector<Satellite> bodies;

    GameObjects() {}

    void render(sf::RenderWindow& window) {
        for (Satellite& body : bodies) {
            body.render(window);
        }
    }

    void clear() {
        bodies.clear();
    }

    void add_satellite(float radius, sf::Vector2f velocity, sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f pos(mousePos.x, mousePos.y);

        Satellite body(pos, radius, velocity, sf::Color::Green);
        bodies.push_back(body);
    }

    void update() {
        quadtree.clear();
        for (Satellite& body : bodies) {
            quadtree.insert(&body);
        }

        calculate_forces();
        quadtree.resolve_collisions();
    }

private:
    void calculate_forces() {
        const float bigG = 0.1f;
        const float minDistance = 50.0f;
        const float dampingFactor = 0.2f;
        
        for (Satellite& body : bodies) {
            body.force = {0.0f, 0.0f};

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

    // Brute force, not used // 
    void resolve_collisions() {  
        const float EPSILON = 1e-6f;

        for (size_t i = 0; i < bodies.size(); i++) {
            for (size_t j = i + 1; j < bodies.size(); j++) {
                Satellite& body1 = bodies[i];
                Satellite& body2 = bodies[j];

                resolve_collision(body1, body2);
            }
        }
    }

 
};

extern GameObjects gameObjects;

#endif // GAME_OBJECTS_HPP
