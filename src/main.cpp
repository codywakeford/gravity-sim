#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Text.hpp"

State state;
sf::Font font;

std::string myText = "Hello, world!";

Text text(font,0, 0, "helllllo");
Text pausedText(font, 900, 25, "PAUSED");
Text bigG(font, 25, 25, "");

int main() {

    if (!font.loadFromFile("assets/Roboto-Regular.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return -1;
    }

    while (state.window.isOpen()) {
        state.handle_inputs(state.window);
        state.update(state.window);
        state.render(state.window);

        state.awaitFrame();
    }

    return 0;
}

