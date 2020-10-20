#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <sstream>
#include<iostream>
#include<string>
#include "Button.h"
#include "Textbox.h"
#include "Player.h"
#include "Board.h"
using namespace std;
using namespace sf;

// Worked on by Ben, Kaylee, Nafisa, Shant, Sheef, Sharon, and Tim

#define GAME_SCREEN_WIDTH 640;
#define GAME_SCREEN_HEIGHT 800;

int turnNum = 1;
int selectedSquare; //benC
bool turn;

bool is_over(RenderWindow &window, RectangleShape &shape)
{
	int btnWidth, btnHeight;

	btnWidth = shape.getSize().x;
	btnHeight = shape.getSize().y;

	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int btnPosX = shape.getPosition().x;
	int btnPosY = shape.getPosition().y;

	int btnxPosWidth = shape.getPosition().x + btnWidth;
	int btnyPosHeight = shape.getPosition().y + btnHeight;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}

int main()
{



	/*
	Define window size with horizontal and vertical
	Variable lineOffsets is padding from edges of window
	Lines is how many horizontal and veritcal lines each that are needed
	Size is board size (3x3)
	LineThickness is thickness of game lines
	*/
	int horizontal, vertical, lineOffsets, lines, size, lineThickness;
	int squareSize; // not used

	/*
	Divions defines length of one side of each square
	Length defines horizontal and vertical lines length
	*/
	float divisions, length;
	const int dim = 3, sqsz = 9;
	bool confirmedMove = false, squareSelected = false;
	int tempSquare; //to hold square that was clicked for finalize move
	vertical = GAME_SCREEN_HEIGHT;
	horizontal = GAME_SCREEN_WIDTH;


	lineOffsets = 25;
	size = 3;
	lineThickness = 25;
	lines = size - 1;

	//---------------------------------------------------------------------
	/*initialize the window menu with user prompt*/
	//startMenu menu;
	//menu.create(vertical, horizontal);

	bool menuDone = false, playAgainFlag = false;  //check to see if menu input is gathered

	sf::RectangleShape menuRectangle(sf::Vector2f(vertical, horizontal));
	menuRectangle.setFillColor(sf::Color(150, 250, 250));
	sf::Texture menuTexture;  //testing texture***
	menuTexture.loadFromFile("menuBack.png");
	menuRectangle.setTexture(&menuTexture);


	Font font;
	font.loadFromFile("BebasNeue-Regular.ttf");
	Text menuBox1, menuBox2;
	menuBox1.setFont(font);
	menuBox1.setString("Player 1 \nEnter a username:"); //text for username 1
	menuBox1.setCharacterSize(32);
	menuBox1.setFillColor(sf::Color::White);
	menuBox1.setPosition(120, 90);

	menuBox2.setFont(font);
	menuBox2.setString("Player 2 \nEnter a username: ");    //text for username2
	menuBox2.setCharacterSize(32);
	menuBox2.setFillColor(sf::Color::White);
	menuBox2.setPosition(450, 90);


	sf::RectangleShape pretzelIcon(sf::Vector2f(200, 200)); //donut icon benC
	pretzelIcon.setPosition(120, 300);
	sf::Texture pretzelIconTexture;
	pretzelIconTexture.loadFromFile("Pretzelcross.png");
	pretzelIcon.setTexture(&pretzelIconTexture);



	sf::RectangleShape donutIcon(sf::Vector2f(200, 200));   //donut icon benC
	donutIcon.setPosition(450, 300);
	sf::Texture donutIconTexture;
	donutIconTexture.loadFromFile("Realdonut.png");
	donutIcon.setTexture(&donutIconTexture);


	sf::RectangleShape PlayTheGame(sf::Vector2f(600, 150)); //Play The Game icon Shant
	PlayTheGame.setPosition(100, 500);
	sf::Texture PlayTheGameTexture;
	PlayTheGameTexture.loadFromFile("PlayTheGame.png");
	PlayTheGame.setTexture(&PlayTheGameTexture);



	//text box background for username input
	sf::RectangleShape textBack1(sf::Vector2f(180, 40));

	textBack1.setPosition(118, 200);
	textBack1.setOutlineThickness(5.f);
	textBack1.setOutlineColor(sf::Color(0, 0, 0));

	sf::RectangleShape textBack2(sf::Vector2f(180, 40));
	textBack2.setPosition(445, 200);
	textBack2.setOutlineThickness(5.f);
	textBack2.setOutlineColor(sf::Color(0, 0, 0));
	//---------------------------------------------------------------------





	//Define window
	RenderWindow window(VideoMode(vertical, horizontal), "Donuts and Pretzels");

	Player player1;
	Player player2;

	//User text box 1
	Textbox text1(30, sf::Color::Black, true);
	text1.setPosition({ 120, 200 });
	text1.setLimit(true, 12);
	text1.setFont(font);
	//User text box 2
	Textbox text2(30, sf::Color::Black, false);
	text2.setPosition({ 450, 200 });
	text2.setLimit(true, 12);
	text2.setFont(font);

	Button btn1("Confirm", { 190, 50 }, 25, sf::Color::Green, sf::Color::Black);
	btn1.setFont(font);
	btn1.setPosition({ 115, 250 });

	Button btn2("Confirm", { 190, 50 }, 25, sf::Color::Green, sf::Color::Black);
	btn2.setFont(font);
	btn2.setPosition({ 440, 250 });

	//Button for finalizing move
	Button finalizeMove("Confirm Move", { 125, 50 }, 25, sf::Color::Green, sf::Color::Black);
	finalizeMove.setFont(font);
	finalizeMove.setPosition({ 640, 515 });

	//Button for Play Again - Kaylee
	Button playAgain("Play Again", { 125, 50 }, 25, sf::Color::Green, sf::Color::Black);
	playAgain.setFont(font);
	playAgain.setPosition({ 640, 310 });

	//Button for Reset ie go back and reset usernames
	Button resetGame("Reset Game", { 125, 50 }, 25, sf::Color::Green, sf::Color::Black);
	resetGame.setFont(font);
	resetGame.setPosition({ 640, 240 });

	//Button for End Game - Kaylee
	Button exitGame("Exit Game", { 125, 50 }, 25, sf::Color::Green, sf::Color::Black);
	exitGame.setFont(font);
	exitGame.setPosition({ 640, 575 });

	// Score for the game - Shant 
	sf::Text Player1_Name;
	Player1_Name.setFont(font);
	Player1_Name.setCharacterSize(25);
	Player1_Name.setFillColor(sf::Color::Red);
	Player1_Name.setStyle(sf::Text::Bold);
	Player1_Name.setPosition({ 635, 30 });

	sf::Text Player2_Name;			// player name Shant 
	Player2_Name.setFont(font);
	Player2_Name.setCharacterSize(25);
	Player2_Name.setFillColor(sf::Color::Red);
	Player2_Name.setStyle(sf::Text::Bold);
	Player2_Name.setPosition({ 635, 55 });

	sf::Text scoreP1;				// player score Shant 
	scoreP1.setFont(font);
	scoreP1.setFillColor(sf::Color::Green);
	scoreP1.setStyle(sf::Text::Bold);
	scoreP1.setCharacterSize(25);
	scoreP1.setPosition(770, 30);

	sf::Text scoreP2;
	scoreP2.setFont(font);
	scoreP2.setFillColor(sf::Color::Green);
	scoreP2.setStyle(sf::Text::Bold);
	scoreP2.setCharacterSize(25);
	scoreP2.setPosition(770, 55);

	//Pop up text Congratulations - Nafisa
	sf::Text textCongra;
	textCongra.setFont(font);
	textCongra.setString("CONGRATULATIONS!!!");
	textCongra.setCharacterSize(100);
	textCongra.setFillColor(sf::Color::Green);
	textCongra.setStyle(sf::Text::Bold);
	textCongra.setPosition({ 70, 60 });
	//Pop up text when It is a tie -- Nafisa
	sf::Text textTie;
	textTie.setFont(font);
	textTie.setString("IT'S A TIE");
	textTie.setCharacterSize(150);
	textTie.setFillColor(sf::Color::Red);
	textTie.setStyle(sf::Text::Bold);
	textTie.setPosition({ 140, 200 });

	//Pop up text Game Over - Kaylee
	sf::Text text;
	text.setFont(font);
	text.setString("GAME OVER");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold);
	text.setPosition({ 140, 400 });

	//Have winner instead of gameover
	sf:Text winner;
	winner.setFont(font);
	winner.setString("IS THE WINNER!");
	winner.setFillColor(sf::Color::Green);
	winner.setCharacterSize(100);
	winner.setStyle(sf::Text::Bold);
	winner.setPosition({ 140, 400 });

	Board board(horizontal, vertical, size);
	board.buildObjects();

	//Add sound effect			-Kaylee
	sf::SoundBuffer buffer1;
	if (!buffer1.loadFromFile("selectsound.wav"))
	{
		cout << "Sound Error" << endl;
	}
	sf::Sound select;
	select.setBuffer(buffer1);

	sf::SoundBuffer buffer2;
	if (!buffer2.loadFromFile("uhoh.wav"))
	{
		cout << "Sound Error" << endl;
	}
	sf::Sound uhoh;
	uhoh.setBuffer(buffer2);

	sf::SoundBuffer buffer3;
	if (!buffer3.loadFromFile("TaDa.wav"))
	{
		cout << "Sound Error" << endl;
	}
	sf::Sound tada;
	tada.setBuffer(buffer3);	//end sound effect


	int square = -1; //temp square selection
	bool square_is_full[9] = { false };// if square is full then true if empty then false
	//While window is open
	while (window.isOpen())
	{
		sf::Event Event;
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		text1.setSelected(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		text1.setSelected(false);
		}*/
		while (window.pollEvent(Event))
		{
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				text1.typedOn(Event);
				text2.typedOn(Event);
			case sf::Event::MouseMoved:
				if (btn1.isMouseOver(window)) {
					btn1.setBackColor(sf::Color::Magenta);
				}
				else {
					btn1.setBackColor(sf::Color::Green);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (btn1.isMouseOver(window)) {
					select.play();		//sound effect 
					player1.name = text1.getText();
					Player1_Name.setString(std::string(player1.name));
					text1.setSelected(false);
					text2.setSelected(true);
				}
				if (btn2.isMouseOver(window)) {
					select.play();		//sound effect
					player2.name = text2.getText();
					Player2_Name.setString(std::string(player2.name));
					text2.setSelected(false);

				}
				if (is_over(window, PlayTheGame))
				{
					menuDone = true;
				}

				if (menuDone == true)
				{
					if (finalizeMove.isMouseOver(window)) //Set confirmedMove bool variable to true if finalize move button is clicked
					{
						confirmedMove = true;
						select.play();		//sound effect
					}


					for (int x = 0; x < (size*size); x++)
					{
						if (is_over(window, board.getSquareRef(x)))
						{
							square = x;
						}
					}
					if (square != -1)
					{
						int boardsquares[9];

						if (square_is_full[square] == false)  // Shant
						{
							/*

							Finalize Move
							Checks bool variables confirmedMove and squareSelected in nested if
							squareSelected is set true everytime a square is clicked
							This brings up finalize move button
							confirmedMove is set true when confirm move button is clicked
							This sets texture on recently clicked square
							This is set true in code above in if statement

							--- int selectedSquare shows what square the player clicked on, if another is clicked the
							previously clicked square will be removed -benC

							*/
							if (confirmedMove == false && squareSelected == false) //first time a square is clicked
							{
								squareSelected = true;
								selectedSquare = square; //benC
								tempSquare = square;
								board.setSquareColor(square, sf::Color(130, 0, 0, 250)); //benC
								//.setFillColor(sf::Color(150, 250, 250));
							}
							else if (confirmedMove == false && squareSelected == true) //update square that was last clicked
							{
								tempSquare = square;
								//----------benC
								board.setSquareColor(selectedSquare, sf::Color::Transparent);
								selectedSquare = square;
								//board.setSquareColor(square, sf::Color::Blue);
								board.setSquareColor(square, sf::Color(130, 0, 0, 250)); //benC
								//--------------


							}
							else
							{

								//take turns, odd are player 1, even are player 2--------benC
								if (turnNum % 2 != 0)
								{

									turn = true;
									board.setSquareTexture(square, turn);
									square_is_full[square] = true;
									player1.full_square[square] = true;
									player1.check_win();
									if (player1.winner) // Shant
									{
										player1.score++;
										tada.play();		//sound effect
									}



								}
								else if (turnNum % 2 == 0)
								{
									turn = false;
									board.setSquareTexture(square, turn);
									square_is_full[square] = true;
									player2.full_square[square] = true;
									player2.check_win();
									if (player2.winner) //Shant 
									{
										player2.score++;
										tada.play();		//sound effect
									}

								}
								if (!player1.winner && !player2.winner)   // check for full board with No winner - Kaylee
								{
									int countMarkSquare = 0;
									for (int i = 0; i < 9; i++)
									{
										if (square_is_full[i] == true)
										{
											countMarkSquare++;
										}
									}
									if (countMarkSquare == 9)
									{
										tada.play();	//sound effect
									}
								}
								turnNum++;
								confirmedMove = false;
								squareSelected = false;
								//---------------------------------------------------------------------------
							}

							std::stringstream s1; // Shant
							s1 << player1.score;
							scoreP1.setString(s1.str());
							std::stringstream s2;
							s2 << player2.score;
							scoreP2.setString(s2.str());
						}
					}
				}
				if (playAgain.isMouseOver(window))  // Play again Sharon
				{	
					select.play();		//sound effect
					//	window.close();
					// reset turn num
					playAgainFlag = true;
					//	return main();
				}

				if (resetGame.isMouseOver(window))
				{
					select.play();		//sound effect
					window.close();
					return main();
				}
				if (exitGame.isMouseOver(window))  // Exit game - Kaylee
				{
					select.play();		//sound effect
					window.close();
					exit(1);
				}

			}

		}
		if (playAgainFlag)
		{
			for (int x = 0; x < 9; x++)
			{
				square_is_full[x] = false;
			}
			board.resetTextures();
			turnNum = 1;
			menuDone = true;
			playAgainFlag = false;
			player1.reset();
			player2.reset();

		}

		if (menuDone == false && !playAgainFlag)
		{
			window.clear();

			window.draw(menuRectangle); //draw the blue menu rectangle-------------------
										//window.draw(menuRectangleP1); //draw the textured rectangle for enter player 1-------
			window.draw(menuBox1);
			window.draw(menuBox2);
			window.draw(pretzelIcon);
			window.draw(donutIcon);
			window.draw(PlayTheGame);
			window.draw(textBack1);
			window.draw(textBack2);
			text1.drawTo(window);
			text2.drawTo(window);
			btn1.drawTo(window);
			btn2.drawTo(window);
			window.display();


			window.draw(menuRectangle); //draw the blue menu rectangle-------------------
			//window.draw(menuRectangleP1); //draw the textured rectangle for enter player 1-------
			window.draw(menuBox1);
			window.draw(menuBox2);
			window.draw(pretzelIcon);
			window.draw(donutIcon);
			window.draw(PlayTheGame);
			window.draw(textBack1);
			window.draw(textBack2);
			text1.drawTo(window);
			text2.drawTo(window);
			btn1.drawTo(window);
			btn2.drawTo(window);
			window.display();
		}
		else if (menuDone == true && !playAgainFlag)
		{ //if menu is done go to the actual game-------------


			window.clear();
			if (player1.name == "")
				player1.name = "Player 1";
			if (player2.name == "")
				player2.name = "Player 2";
			window.draw(menuRectangle);
			window.draw(Player1_Name);
			window.draw(Player2_Name);
			window.draw(scoreP1);
			window.draw(scoreP2);
			board.drawTo(window);
			exitGame.drawTo(window);

			if (squareSelected)
			{
				finalizeMove.drawTo(window);
			}
			if (player1.winner || player2.winner) // pop up text for any winner - Kaylee
			{
				playAgain.drawTo(window);
				resetGame.drawTo(window);


												  //Pop up Winner name and winning greetings - Nafisa
				if (player1.winner)
				{
					sf::Text textCongraName;
					textCongraName.setFont(font);
					textCongraName.setString(std::string(player1.name));
					textCongraName.setCharacterSize(100);
					textCongraName.setFillColor(sf::Color::Red);
					textCongraName.setStyle(sf::Text::Bold);
					textCongraName.setPosition({ 200, 170 });

					window.draw(textCongraName);
					window.draw(textCongra);            //pop up congratulation - Nafisa
					window.draw(winner);
				}
				else if (player2.winner)
				{
					sf::Text textCongraName;
					textCongraName.setFont(font);
					textCongraName.setString(std::string(player2.name));
					textCongraName.setCharacterSize(100);
					textCongraName.setFillColor(sf::Color::Red);
					textCongraName.setStyle(sf::Text::Bold);
					textCongraName.setPosition({ 200, 170 });

					window.draw(textCongraName);
					window.draw(textCongra);            //pop up congratulation - Nafisa
					window.draw(winner);
				}
			}// end if

		}

		if (!player1.winner && !player2.winner)   // check for full board with No winner - Kaylee

		{
			int countMarkSquare = 0;
			for (int i = 0; i < 9; i++)
			{
				if (square_is_full[i] == true)
				{
					countMarkSquare++;
				}
			}
			if (countMarkSquare == 9)
			{
				playAgain.drawTo(window);
				resetGame.drawTo(window);

				exitGame.drawTo(window);


				window.draw(textTie);           //Show its a tie - Nafisa
				window.draw(text);
			}
		}// end if


		window.display();

	}

	return 0;
}
