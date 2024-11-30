#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "utils.hpp"
// #include "font.cpp"

#ifndef SATELLITE_HPP
#define SATELLITE_HPP

class Satellite {
private:
    sf::Text massText;

public:
    sf::CircleShape body;
    sf::Vector2f position = {0.0f, 0.0};
    sf::Vector2f velocity = {0.0f, 0.0f};
    sf::Vector2f force = {0.0f, 0.0f};

    float radius;
    float mass;

    Satellite(sf::Vector2f position, float radius, sf::Vector2f velocity, sf::Color color)
        : body(radius), position(position), velocity(velocity) {
        body.setRadius(radius);
        body.setPosition(position);
        body.setFillColor(color);
        body.setOrigin(radius, radius);

        mass = 3.14159f * radius * radius;
            
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
