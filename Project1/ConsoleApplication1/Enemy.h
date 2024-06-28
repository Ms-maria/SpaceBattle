#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy : public Sprite
{
private:
	const double speed;
	int healthPoints;
	const int fullhealth;
public:
	bool visible;
	Enemy(int health) : speed(0.15), healthPoints(health), visible(false), fullhealth(health)
	{
		setOrigin(25, 25);
	}
	void Move(double elapsed);
	void Wound();
};


