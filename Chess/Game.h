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


#define KING_LIST_WHITE 30
#define KING_LIST_BLACK 31 

#define MIDDLE_BOTTOM_INDEX 3
#define MIDDLE_TOP_INDEX 59
#define MARKER_OFFSET 50

#define LEFT_BORDER 0
#define RIGHT_BORDER 8


enum NUMS {
	PAWNS = 16,
	BISHOPS = 4,
	ROOKS = 4,
	KNIGHTS = 4,
	QUEENS = 2,
	KINGS = 2

};


class Game
{
public:

	int* pawnPos = nullptr;
	int* bishopPos = nullptr;
	int* rookPos = nullptr;
	int* knightPos = nullptr;
	int* queenPos = nullptr;
	int* kingPos = nullptr;

	std::shared_ptr<Pawn> currentEnPassPawn; 

	std::vector<std::shared_ptr<Figure>> possesCheck{};

	std::vector<std::shared_ptr<Figure>> refsToObj{}; 

	int kings[2] = {-1,-1 }; 


	bool endGame = false; 


	int playerSide; 
	int checkS = -1; 

	sf::Font font;
	int white = 0; 
	int black = 0; 

	sf::Vector2f posWhite; 
	sf::Vector2f posBlack; 


	std::string WHITE = "White: ";
	std::string BLACK = "Black: ";

	sf::Text scoreWhite; 
	sf::Text scoreBlack; 
	sf::Text checkText; 

	sf::CircleShape sideMarker;


	int currSideMove = 0; //0 - White, 1 - Black

	std::vector<std::shared_ptr<Figure>> playerBase{};
	int lastSel = -1;
	bool done = true;
	bool lock = false; 


	Game(int side, Field *field, int objectSize);

	void defScore(sf::Vector2f pos1, sf::Vector2f pos2, float offset1, float offset2);


	template <typename T>
	std::shared_ptr<T> getType(int pos);


	template <typename T>
	std::shared_ptr<T> getType(std::shared_ptr<Figure>);


	template <typename T>
	void figurePlacement(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);



	
	int getLast();
	int getActionState();
	int getLockState(); 
	int getSideGlob(int index); 


	void switchMarkerPos(int side);
	void addToSide(int side, int points);
	void drawAll(sf::RenderWindow *window, Field *field);
	void undo(sf::RenderWindow *window, Field *field);
	
	void checkIf(sf::RenderWindow *window, Field *field);
	bool end();
	void deletePlayers(Field* field);
	void winScreen(sf::RenderWindow* window, int x, int y);
	void different(std::shared_ptr<Figure> piece, Field* field);
	void move(int moveTo, Field* field, int lastSel, int fieldPos = -1);
	void updateKingsThreads(Field* field, int lastSel, int input, int* KingsPos);
	void makeMove(sf::RenderWindow *window, Field *field);

	void check(Field* field);	
};


#include "Game.tpp"
