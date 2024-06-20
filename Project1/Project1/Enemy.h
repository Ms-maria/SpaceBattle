#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy : public Sprite
{
private:
	const double speed;
	int healthPoints;
public:
	bool visible;
	Enemy() : speed(0.15), healthPoints(2), visible(false) 
	{
		setOrigin(25, 25);
	}
	void Move(double elapsed);
	void Wound();
};

