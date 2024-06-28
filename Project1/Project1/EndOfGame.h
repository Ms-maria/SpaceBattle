#pragma once
#include <SFML/Graphics.hpp>
#include "Score.h"
#include <string>

using namespace sf;

extern RenderWindow win;

bool EndOfGame(bool lose,Score score);