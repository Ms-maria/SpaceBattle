#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

extern const int sizeX;

class Bullet : public CircleShape
{
private:
	const double speed;
	const int power;
public:
	bool visible;
	Bullet() : power(10), speed(sizeX * 1.2 / 500), visible(false)
	{
		setRadius(3);
		setFillColor(Color::White);
		setOrigin(10, 10);
	}
	void fly(double elapsed);
};
