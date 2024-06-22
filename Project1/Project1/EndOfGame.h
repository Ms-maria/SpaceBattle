#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

extern RenderWindow win;

void EndOfGame(bool lose, const std::vector<int> score);