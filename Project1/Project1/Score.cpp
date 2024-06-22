#include "Score.h"

const std::vector<int> Score::getScore()
{
	std::vector<int> score_digits;
	int temp = score;
	while (temp > 0)
	{
		score_digits.push_back(temp % 10);
		temp /= 10;
	}
	return score_digits;
}

void Score::Add(int x)
{
	score += multiplier * x;
}
