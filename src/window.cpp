#include <SFML/Graphics.hpp>

#ifndef WINDOW_CPP
#define WINDOW_CPP

const float FPS = 120.0f;
const float TIME_PER_FRAME = 1.0f / FPS;

int WINDOW_HEIGHT = 1080;
int WINDOW_WIDTH = 1920;

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity");
sf::Font font;

#endif

