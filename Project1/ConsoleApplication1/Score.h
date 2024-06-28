#pragma once
#include <vector>
class Score
{
private:
	int score;
	const int multiplier;
public:
	Score(int mult) : multiplier(mult), score(0) {}
	void Add(int x);
	int GetScore();
	std::vector<int> GetNumbers();
};