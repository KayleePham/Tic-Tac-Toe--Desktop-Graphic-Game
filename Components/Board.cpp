#include <SFML/Graphics.hpp>
#include "Board.h"
// Worked on by Tim, Sharon, Ben
Board::Board(int hor, int ver, int size) : horizontal(hor), vertical(ver), size(size)
{
	lines = size - 1;
	lineOffsets = 15;
	lineThickness = 15;
	squareSize = size * size;
	if (horizontal > vertical)
	{
		//length = vertical;
		divisions = (vertical - (lineOffsets)) / size;
	}
	else
	{

		//length = horizontal;
		divisions = (horizontal - (lineOffsets)) / size;
	}

	length = divisions * size;
	verticalLines = new sf::RectangleShape[lines];
	horizontalLines = new sf::RectangleShape[lines];
	squares = new sf::RectangleShape[squareSize];

}
//Destructor
Board::~Board()
{
	delete[] verticalLines;
	delete[] horizontalLines;
	delete[] squares;
}
//function for leftClick

/*

This is where we build horizontal and vertical lines as well as squares


*/
void Board::buildObjects()
{
	// for each of the hor and vert lines, set size and position
	for (int x = 0; x < lines; x++)
	{
		verticalLines[x].setSize(sf::Vector2f(lineThickness, (length - (lineOffsets))));
		horizontalLines[x].setSize(sf::Vector2f((length - (lineOffsets)), lineThickness));

		verticalLines[x].setFillColor(sf::Color::Black);
		horizontalLines[x].setFillColor(sf::Color::Black);

		verticalLines[x].setPosition(sf::Vector2f((float)(((x + 1) * divisions)), (float)lineOffsets));
		horizontalLines[x].setPosition(sf::Vector2f(((float)lineOffsets), (float)((x + 1) * divisions)));

	}

	/*

	x is uesed to cycle though array
	w is the row index
	y is col index


	*/
	int y = 0, w = 0;
	for (int x = 0; x < (squareSize); x++)
	{
		//Since y is col index, we want to reset everytime it is a new line (square[3] on a 3x3 board should be 1st col 2nd row)
		if (y >= size)
		{
			y = 0;
			w++;
		}
		squares[x].setSize(sf::Vector2f(divisions - lineThickness, divisions - lineThickness));

		squares[x].setFillColor(sf::Color(255, 255, 255, 0)); //make square transparent until it is clicked

		squares[x].setPosition(sf::Vector2f(lineOffsets + (y * divisions), lineOffsets + (w * divisions)));
		y++;
	}
}
void Board::drawTo(sf::RenderWindow &window)
{
	for (int x = 0; x < lines; x++)
	{
		window.draw(horizontalLines[x]);
		window.draw(verticalLines[x]);
	}
	for (int x = 0; x < squareSize; x++)
	{
		window.draw(squares[x]);
	}
}
void Board::getSquarePosition(int index, int &x, int &y)
{
	x = squares[index].getPosition().x;
	y = squares[index].getPosition().y;
}
sf::RectangleShape& Board::getSquareRef(int index)
{
	return squares[index];
}
void Board::setSquareColor(int index, sf::Color color)
{
	squares[index].setFillColor(color);
}
void Board::setSquareTexture(int index, bool turn)	//if turn == true then player 1's move------------------------ benC
{
	
	if (turn == true)
	{

		pretzelIconTexture.loadFromFile("Pretzelcross.png");
		squares[index].setFillColor(sf::Color(255, 255, 255, 255)); //Set square so it is not transparent so the texture can be seen!
		squares[index].setTexture(&pretzelIconTexture);

	}
	else if (turn == false)
	{
		donutIconTexture.loadFromFile("Realdonut.png");
		squares[index].setFillColor(sf::Color(255, 255, 255, 255)); //Set square so it is not transparent so the texture can be seen!
		squares[index].setTexture(&donutIconTexture);

	}
}

void Board::resetTextures()
{
	for (int x = 0; x < squareSize; x++)
	{
		squares[x].setFillColor(sf::Color(255, 255, 255, 0));
		squares[x].setTexture(NULL);
	}

}
//----------------------------------------------------------------------------------
