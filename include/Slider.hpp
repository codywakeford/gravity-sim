#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef SLIDER_HPP
#define SLIDER_HPP

class Slider {

private:
    sf::RectangleShape bar;          // The background of the slider
    sf::CircleShape knob;            // The draggable knob
    float minValue, maxValue;        // Min and max values for the slider
    float currentValue;              // Current value of the slider
    bool isDragging;                 // Whether the knob is being dragged

public:
    Slider(float x, float y, float width, float height, float minVal, float maxVal, float initialVal) 
        : minValue(minVal), maxValue(maxVal), currentValue(initialVal), isDragging(false) {
        
        // Create the background bar (the track of the slider)
        bar.setSize(sf::Vector2f(width, height));
        bar.setPosition(x, y);
        bar.setFillColor(sf::Color(200, 200, 200));

        // Create the knob
        knob.setRadius(height * 2);  // Set knob size based on the height of the bar
        knob.setFillColor(sf::Color::Blue);
        knob.setPosition(x + (initialVal - minVal) / (maxVal - minVal) * width, y - (height));  // Position the knob
    }

    // Function to update the slider based on mouse position
    void update(const sf::Vector2i& mousePos, bool mousePressed) {
        if (mousePressed && knob.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isDragging = true;
        }

        if (isDragging) {
            // Update the knob's position while dragging
            float newPosX = mousePos.x - knob.getRadius();
            newPosX = std::max(bar.getPosition().x, std::min(newPosX, bar.getPosition().x + bar.getSize().x - knob.getRadius() * 2));
            knob.setPosition(newPosX, knob.getPosition().y);

            // Update the current value of the slider based on the knob position
            currentValue = minValue + (newPosX - bar.getPosition().x) / bar.getSize().x * (maxValue - minValue);
        }

        if (!mousePressed) {
            isDragging = false;  // Stop dragging when mouse is released
        }
    }

    // Function to render the slider on the window
    void render(sf::RenderWindow& window) {
        window.draw(bar);
        window.draw(knob);
    }

    // Getter for the current value of the slider
    float getValue() const {
        return currentValue;
    }
};

extern Slider slider;

#endif