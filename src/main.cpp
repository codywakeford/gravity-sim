#include <SFML/Graphics.hpp>
#include "State.hpp"


State state;
int main() {

    while (state.window.isOpen()) {
        state.handle_inputs(state.window);
        state.update(state.window);
        state.render(state.window);
        state.awaitFrame();
    }

    return 0;
}

