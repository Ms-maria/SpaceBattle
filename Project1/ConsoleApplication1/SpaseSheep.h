#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

extern const int sizeX;
extern const int sizeY;

class SpaseShep : public Sprite
{
private:
	const double speed;
	const int power;
public:
	SpaseShep() : speed(0.5), power(10)
	{
		setPosition(sizeX / 2, sizeY - 60);
		setOrigin(60, 50);
	}
	void goLeft(double elapsed);
	void goRight(double elapsed);
};
