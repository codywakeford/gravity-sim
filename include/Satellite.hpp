#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

#ifndef SATELLITE_HPP
#define SATELLITE_HPP

class Satellite {
private:
    sf::CircleShape body;

public:
    sf::Vector2f velocity = {0.0f, 0.0f};
    sf::Vector2f position = {0.0f, 0.0};
    sf::Vector2f force = {0.0f, 0.0f};

    float radius;
    float mass = 1.0f; // mass in metric tons

    Satellite(sf::Vector2f position, float radius, sf::Vector2f velocity, sf::Color color)
        : body(radius), position(position), velocity(velocity) {
            body.setPosition(position);
            body.setFillColor(color);
        }

    void update() {
        sf::Vector2f acceleration = force / mass;
            
        velocity += acceleration;
        position += velocity;
    }

    void render(sf::RenderWindow& window) {
        body.setPosition(position);
        window.draw(body);
    }
};

#endif // SATELLITE_HPP
