#pragma once
#pragma once

#include<sstream>

class Player {
public:
	bool shape;
	std::string name;

	bool full_square[9];
	bool winner;
	int score;
	bool check_win();
	void reset();
	Player();

};



Player::Player() {

	for (int i = 0; i < 9; i++)
		full_square[i] = false;
	winner = false;
	score = 0;

}

void Player::reset()
{
	for (int i = 0; i < 9; i++)
	{
		full_square[i] = false;
	}
	winner = false;

}

// Shant
bool Player::check_win() // if win return true, else false
{

	if (full_square[0] == true && full_square[1] == true && full_square[2] == true) // first row
		winner = true;

	else if (full_square[3] == true && full_square[4] == true && full_square[5] == true) // second row
		winner = true;

	else if (full_square[6] == true && full_square[7] == true && full_square[8] == true) // third row
		winner = true;

	else if (full_square[0] == true && full_square[3] == true && full_square[6] == true) // first column
		winner = true;

	else if (full_square[1] == true && full_square[4] == true && full_square[7] == true) // second column
		winner = true;

	else if (full_square[2] == true && full_square[5] == true && full_square[8] == true) // third column

		winner = true;
	else if (full_square[0] == true && full_square[4] == true && full_square[8] == true) // diagonal top left <-> low right
		winner = true;

	else if (full_square[2] == true && full_square[4] == true && full_square[6] == true) // diagonal bottom left <-> top right
		winner = true;
	else
		winner = false;


	return winner;

}
