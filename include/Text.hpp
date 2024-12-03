#include <SFML/Graphics.hpp>
#include <vector>
#ifndef TEXT_HPP
#define TEXT_HPP

class Text {
public:
    static std::vector<sf::Text> texts;
    sf::Text text;
    void *boundValue;

    Text(sf::Font &font, float x, float y, const std::string &string) {
        text.setFont(font);
        text.setString(string);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y); 
        texts.push_back(text);
    };

    void bind(void* valueToBind) {
        boundValue = valueToBind;
    }

    void update() {
        if (boundValue) {
            // Ensure boundValue is a pointer to a std::string
            std::string* boundStr = static_cast<std::string*>(boundValue);
            text.setString(*boundStr); // Dereference to get the string value
        }
    }

    static void renderAllText(sf::RenderWindow& window) {
        for (const sf::Text text : texts) {
            window.draw(text);
        }
    }

    void updateText(){}
};
std::vector<sf::Text> Text::texts;
// extern Text text;

extern sf::Font font;

#endif