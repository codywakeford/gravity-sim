#include <SFML/Graphics.hpp>
#include "GameObjects.hpp"
#include "Satellite.hpp"
#include <iostream>

#ifndef MOUSE_HPP
#define MOUSE_HPP

float VELOCITY_MULTIPLYER = 0.05;

class Mouse {
private:
    float x, y;
    float radius;
    sf::Color color = sf::Color::Blue;
    sf::CircleShape shape;

    bool isDragging = false;
    sf::Vector2f dragStart;
    sf::Vector2f dragEnd;

public:
    Mouse(float x = 0.0f, float y = 0.0f, float radius = 25.0f)
            : x(x), y(y), radius(radius), shape(radius) {
        shape.setOrigin(radius, radius);
    }

    void input(sf::Event& event, sf::RenderWindow& window) {
        switch (event.type) {
            case sf::Event::MouseWheelScrolled:
                changeSatelliteSize(event);
                break;
            

            // Click and drag to add velocity to new object. // 
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    startDrag(window);
                }
                break;

            // Create satellite on release //
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    endDrag(window);
                }
                break;
            default:
                break;


        }
        if (isDragging) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            dragEnd = sf::Vector2f(mousePos.x, mousePos.y);
        }
    }

    void render(sf::RenderWindow& window) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        shape.setPosition(mousePosition.x, mousePosition.y);
        shape.setFillColor(color);
        window.draw(this->shape);

        if (isDragging) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = dragStart;
            line[0].color = sf::Color::White;
            line[1].position = dragEnd;
            line[1].color = sf::Color::White;
            window.draw(line);
        }   
    }

private: 
    // Changes the size of the satellite under the mouse cursor // 
    void changeSatelliteSize(sf::Event& event) {
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                radius += 3;
            } else {
                if (radius > 3) {
                    radius -= 3;
                }
            }
        }
        shape.setOrigin(radius, radius);
        shape.setRadius(radius);
    }

    // Add a satellite to the scene on mouse release. //
    void createSatellite(sf::RenderWindow& window, sf::Vector2f velocity) {
        gameObjects.add_satellite(radius, velocity, window);
    }

    void startDrag(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        dragStart = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        isDragging = true;
    }

    void endDrag(sf::RenderWindow& window) {
        float vX = dragStart.x - dragEnd.x;
        float vY = dragStart.y - dragEnd.y;

        sf::Vector2f velocity(vX, vY);

        createSatellite(window, velocity * VELOCITY_MULTIPLYER);

        isDragging = false;
    }
};

extern Mouse mouse;

#endif // MOUSE_HPP