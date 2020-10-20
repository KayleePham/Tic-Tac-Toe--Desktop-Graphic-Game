#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
// Worked on by Tim, Sharon, Ben
class Board
{



	/*

	BUG: lineOffsets and lineThickness must be the same to not mess up. Position of the squares to far out?

	*/

	//horizontal and vertical refer to the size of the window
	//lineOffsets is the padding from window edges
	//lines is how many lines for game board (ie size - 1)
	//size refers to the dimension of the game, so 3 for 3x3, 4 for 4x4 etc
	//lineThickness is how thick the lines of the game board
	//squareSize is how large square array has to be, (for 3x3, its 9, 4x4 its 16)
	//divisons is the length divided by size
	//Length is set to the smallest of horizontal or vertical, than is subtracted by 2 times lineOffsets

	int horizontal, vertical, lineOffsets, lines, size, lineThickness, squareSize;
	float divisions, length;
	sf::RectangleShape *verticalLines, *horizontalLines, *squares;

	sf::Texture donutIconTexture;
	sf::Texture pretzelIconTexture;


public:
	//Constructor
	Board(int hor, int ver, int size);
	//Destructor
	~Board();
	//function for leftClick

	/*

	This is where we build horizontal and vertical lines as well as squares


	*/
	void buildObjects();
	void drawTo(sf::RenderWindow &window);
	void getSquarePosition(int index, int &x, int &y);
	void setSquareColor(int index, sf::Color color);
	void setSquareTexture(int index, bool turn); //----------benC
	void resetTextures();
	sf::RectangleShape& getSquareRef(int index);
};
