#include "Enemy.h"
void Enemy::Move(double elapsed)
{
	move(0, speed * elapsed);
}
bool Enemy::Wound()
{
	healthPoints--;
	if (healthPoints == 0)
	{
		visible = false;
		return true;
	}
	return false;
}