#include "Score.h"

void Score::Add(int x)
{
	score += multiplier * x;
}
int Score::GetScore()
{
	return score;
}
std::vector<int> Score::GetNumbers()
{
	std::vector<int> digits;
	if (score == 0)
	{
		digits.push_back(0);
	}
	while (score > 0)
	{
		int digit = score % 10;
		digits.push_back(digit);
		score /= 10;
	}
	std::reverse(digits.begin(), digits.end());
	return digits;
}