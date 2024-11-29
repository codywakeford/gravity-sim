#include <SFML/Graphics.hpp>
#include "GameObjects.hpp"
#include "Satellite.hpp"
#include <iostream>

#ifndef MOUSE_HPP
#define MOUSE_HPP

class Mouse {
private:
    float x, y;
    float radius;
    sf::Color color = sf::Color::Blue;
    sf::CircleShape shape;

public: 
    Mouse(float x = 0.0f, float y = 0.0f, float radius = 25.0f)
            : x(x), y(y), radius(radius), shape(radius) {}

    void input(sf::Event& event, sf::RenderWindow& window) {
        switch (event.type) {
            case sf::Event::MouseWheelScrolled:
                changeSatelliteSize(event);
                break;
            
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    createSatellite(window);
                }
                break;
            default:
                break;
        }
    }

    void render(sf::RenderWindow& window) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        shape.setPosition(mousePosition.x - radius, mousePosition.y - radius);
        shape.setFillColor(color);
        window.draw(this->shape);
    }

private: 
    // Changes the size of the satellite under the mouse cursor // 
    void changeSatelliteSize(sf::Event& event) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                radius += 5;
            } else {
                if (radius > 5) {
                    radius -= 5;
                }
            }
        }
        shape.setRadius(radius);
    }

    // Add a satellite to the scene on mouse press. //
    void createSatellite(sf::RenderWindow& window) {
        gameObjects.add_satellite(radius, window);
    }
};

extern Mouse mouse;

#endif // MOUSE_HPP