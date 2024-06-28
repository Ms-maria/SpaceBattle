#include "Bullet.h"

void Bullet::fly(double elapsed)
{
	move(0, -speed * elapsed);
}