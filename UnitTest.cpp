#include "pch.h"
#include "../Project1/Player.h"
#include <iostream>
#include <string>

using namespace std;

//Worked on by Kaylee, Shifa, Sharon, and Nafisa

// A player should have no moves made in the beginning of the game
TEST(playerMovesRecord,player1) {						//Shifa
	Player Player1;
	EXPECT_EQ(Player1.full_square[0], false);
	EXPECT_EQ(Player1.full_square[1], false);
	EXPECT_EQ(Player1.full_square[2], false);
	EXPECT_EQ(Player1.full_square[3], false);
	EXPECT_EQ(Player1.full_square[4], false);
	EXPECT_EQ(Player1.full_square[5], false);
	EXPECT_EQ(Player1.full_square[6], false);
	EXPECT_EQ(Player1.full_square[7], false);
	EXPECT_EQ(Player1.full_square[8], false);
}

// Any player should start at not a winner
TEST(playerBegin, playerBeginAtNotAWinner) {		//Kaylee
	Player player1;
	Player player2;
	EXPECT_FALSE(player1.winner);
	EXPECT_FALSE(player2.winner);
}
// Any player should start with score is zero
TEST(playerBegin, scoreIsZero) {		//Kaylee
	Player player1;
	Player player2;
	EXPECT_EQ(player1.score,0);
	EXPECT_EQ(player2.score,0);
}
// Testing if username crashes if you input no username
TEST(testNoUserName, maxChar_20) {      //Sharon
  Player player1, player2;
  EXPECT_EQ(player1.name, "test");
  EXPECT_EQ(player2.name, "");
}
// Unit test of inputting a username that is more than 20 characters long
TEST(testUserNameLength, maxChar_20) {      //Sharon
  Player player1, player2;
  EXPECT_EQ(player1.name, "test");
  EXPECT_EQ(player2.name, "testtesttesttesttesttest");
}
// Another unit test of inputting a username that is more than 20 characters long
TEST(testUserNameLength1, maxChar_20) {         //Sharon
  Player player1, player2;
  string astring;
  for (int i = 0; i < 10; i++)
    astring += "a";
  EXPECT_EQ(player1.name, "test");
  EXPECT_EQ(player2.name, astring);
}

//Unit test -- scores for any player cannot be negative                       // Nafisa
TEST(playersNegScoreChecking, negativeScoreChecking) {		
	Player player1;
	Player player2;
	
	EXPECT_FALSE (player1.score < 0);
	EXPECT_FALSE (player2.score < 0);
	}


//Unit test to check if there is two winner                          // Nafisa
//Using Manual Unit testing, Not Automated that is why making it as a comment 
/*
TEST(playersScoreChecking, scoreChecking) {		
	Player player1;
	Player player2;
	int x,y;
	
	player1.score = x;
	player2.score =y;
	
	if ((player1.winner == true) 
	    EXPECT_TRUE(player1.score  = x+1 );
	else if (player2.winner == true))
	    EXPECT_TRUE(player2.score = y+1 );
	}
*/