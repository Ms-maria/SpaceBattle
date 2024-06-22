#pragma once
#include <vector>
class Score
{
private:
	int score;
	const int multiplier;
public:
	Score(int mult) : score(0), multiplier(mult) {}

	const std::vector<int> getScore();

	void Add(int x);
};

