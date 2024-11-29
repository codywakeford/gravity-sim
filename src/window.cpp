#include <SFML/Graphics.hpp>

#ifndef WINDOW_CPP
#define WINDOW_CPP

const float FPS = 120.0f;
const float TIME_PER_FRAME = 1.0f / FPS;

int WINDOW_HEIGHT = 720;
int WINDOW_WIDTH = 1080;

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity");

#endif