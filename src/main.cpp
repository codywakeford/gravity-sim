#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Text.hpp"

State state;
sf::Font font;

std::string myText = "Hello, world!";

bool hello = true;

int main() {
    Text bigG(font, 25, 25, "Big G", &hello, true);
    Text pausedText(font, 900, 25, "PAUSED", &state.isPaused, true);
    bigG.bindValue(&state.gameObjects.bigG);

    if (!font.loadFromFile("assets/Roboto-Regular.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
        return -1;
    }

    while (state.window.isOpen()) {
        state.handle_inputs(state.window);
        state.render(state.window);

        if (!state.isPaused) {
            state.update(state.window);
        }
        state.awaitFrame();
    }

    return 0;
}

