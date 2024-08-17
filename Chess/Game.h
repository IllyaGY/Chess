#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

#include "Field.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"

#include <vector>


#define KING_POS_WHITE 60 
#define KING_POS_BLACK 4 

class Game
{
public:


	std::vector<std::shared_ptr<Figure>> possesCheck{};


	sf::Font font;
	int white = 0; 
	int black = 0; 

	sf::Vector2f posWhite; 
	sf::Vector2f posBlack; 


	std::string WHITE = "White: ";
	std::string BLACK = "Black: ";

	sf::Text scoreWhite; 
	sf::Text scoreBlack; 

	sf::CircleShape sideMarker;


	int currSideMove = 0; //0 - White, 1 - Black

	std::vector<std::shared_ptr<Figure>> playerBase{};
	int lastSel = -1;
	bool done = true;
	bool lock = false; 

	Game(int side, Field *field, int objectSize);


	template <typename T>
	std::shared_ptr<T> getType(int pos);

	template <typename T>
	void figurePlacement(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);



	
	int getLast();
	void switchMarkerPos(int side);
	int getActionState();
	int getLockState(); 
	int getSideGlob(int index); 

	void addToSide(int side, int points);
	void drawAll(sf::RenderWindow *window, Field *field);
	void undo(sf::RenderWindow *window, Field *field);
	void check(int sideOfKing, std::shared_ptr<Figure> figure);
	void checkIf(sf::RenderWindow *window, Field *field);
	void makeMove(sf::RenderWindow *window, Field *field);
};


#include "Game.tpp"
