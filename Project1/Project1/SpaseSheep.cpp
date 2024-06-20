#include "SpaseSheep.h"

void SpaseShep::goLeft(double elapsed)
{
	move(-speed * elapsed, 0);
}
void SpaseShep::goRight(double elapsed)
{
	move(speed * elapsed, 0);
}