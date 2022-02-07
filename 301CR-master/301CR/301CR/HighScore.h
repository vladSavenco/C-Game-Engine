#pragma once

struct HighScore
{
public:
	int score;
	std::string name;

	HighScore(){}

	HighScore(int sc, std::string nm)
	{
		score = sc;
		name = nm;
	}
};