#include "Enemy.h"
void Enemy::Move(double elapsed)
{
	move(0, speed * elapsed);
}
void Enemy::Wound()
{
	healthPoints--;
	if (healthPoints == 0)
	{
		visible = false;
		healthPoints = 2;
	}
}