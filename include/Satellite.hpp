#include <SFML/Graphics.hpp>

#ifndef SATELLITE_HPP
#define SATELLITE_HPP

class Satellite {
private:
    float x, y, radius;
    sf::CircleShape shape;

public:
    Satellite(float x, float y, float radius, sf::Color color)
        : x(x), y(y), radius(radius), shape(radius) {
            shape.setPosition(x, y);
            shape.setFillColor(color);
        }

    void render(sf::RenderWindow& window) const {
        window.draw(shape);
    }
};

#endif // SATELLITE_HPP
