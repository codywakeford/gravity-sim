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
    Quadtree quadtree;
    GameObjects(Quadtree quadtree) : quadtree(quadtree) {};

    void render(sf::RenderWindow& window) {
        for (Satellite& body : this->bodies) {
            body.render(window);
        }
    }

    void clear() {
        bodies.clear();
    }

    void add_satellite(float radius, sf::Vector2f velocity, sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f pos(mousePos.x, mousePos.y );
        Satellite body(pos, radius, velocity, sf::Color::Green);
        bodies.push_back(body);
    }

    void update() {
        calculate_forces();
        resolve_collisions();
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

    /**
    
    v - velocity
    m - mass
    x - normal
    v1f - velocity final
    
    Equation: 

                2 * m2      (v2 - v1) * (x2 - x1)
    v1f = v1 + -------- *  --------------------- * (x2 - x1)
                m1 + m2         (x1 - x2)^2

    */
    void resolve_collisions() {  
        const float EPSILON = 1e-6f;

        for (size_t i = 0; i < bodies.size(); i++) {
            for (size_t j = i + 1; j < bodies.size(); j++) {
                Satellite& body1 = bodies[i];
                Satellite& body2 = bodies[j];

                float dX = body1.position.x - body2.position.x;
                float dY = body1.position.y - body2.position.y;
                float normalMagnitude = std::sqrt(dX * dX + dY * dY);

                if (normalMagnitude < EPSILON) continue;

                // get the normal force
                sf::Vector2f normalVector((dX / normalMagnitude), (dY / normalMagnitude));

                // r1 + r2
                float sumOfRadii = body1.body.getRadius() + body2.body.getRadius();
                if (normalMagnitude + EPSILON >= sumOfRadii) continue;

                // v2 - v1
                sf::Vector2f velocityDifference = body1.velocity - body2.velocity;

                // (2 x m2)
                // ---------
                //  m1 + m2
                float massScaler = (2 * body2.mass) / (body1.mass + body2.mass);


                // (v2 - v1) * (x2 - x1)
                float dotProductResult = dotProduct(velocityDifference, normalVector);
                if (dotProductResult > 0) continue;

                float massScaler1 = (2.0f * body2.mass) / (body1.mass + body2.mass);
                float massScaler2 = (2.0f * body1.mass) / (body1.mass + body2.mass);

                sf::Vector2f impulse1 = normalVector * dotProductResult * massScaler1;
                sf::Vector2f impulse2 = normalVector * dotProductResult * massScaler2;

                body1.velocity -= impulse1;
                body2.velocity += impulse2;



                // Positional correction to prevent overlap
                float penetrationDepth = sumOfRadii - normalMagnitude;
                sf::Vector2f correctionVector = normalVector * (penetrationDepth / 2.0f);
                body1.position += correctionVector;
                body2.position -= correctionVector;
            }
        }
    }

};

extern GameObjects gameObjects;

#endif // GAME_OBJECTS_HPP
