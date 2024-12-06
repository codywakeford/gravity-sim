#include <SFML/Graphics.hpp>
#include <vector>
#ifndef TEXT_HPP
#define TEXT_HPP

class Text {
public:
    static std::vector<Text> texts;
    sf::Text text;
    const void *boundValue = NULL; // bind string to a value

    // Conditionally render the text by pointing to a bool.
    bool* conditional = NULL;
    bool displayWhen;

    Text(sf::Font &font, float x, float y, const std::string &string, bool* conditional, bool displayWhen) : conditional(conditional), displayWhen(displayWhen) {
        text.setFont(font);
        text.setString(string);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);
        texts.push_back(*this);
    };

    void bindValue(const void* valueToBind) {
        boundValue = valueToBind;
    }

    void update() {
        std::cout << this->boundValue << std::endl;
        if (boundValue) {
            if (const std::string* boundStr = static_cast<const std::string*>(boundValue)) {
                text.setString(*boundStr);
            }
            else if (const float* boundFloat = static_cast<const float*>(boundValue)) {
                std::string updatedString = "BigG: " + std::to_string(*boundFloat);
                text.setString(updatedString);
            }
        }
    }

    static void renderAllText(sf::RenderWindow& window) {
        for (const Text text : texts) {
            // std::cout << text.displayWhen << std::endl;
            
            if (*text.conditional == text.displayWhen)
            {
                window.draw(text.text);
            }
        }
    }

    static void updateAllText() {
        for (Text text : texts) {
            text.update();
        }
    }
    void updateText(){}
};
std::vector<Text> Text::texts;
// extern Text text;

extern sf::Font font;

#endif