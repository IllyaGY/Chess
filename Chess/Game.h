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
#define PAWN_SIZE 16

class Game
{
public:

	int currSideMove = 0; //0 - White, 1 - Black

	std::vector<std::shared_ptr<Figure>> playerBase{};
	int lastSel = -1;
	bool done = true;
	bool lock = false; 

	Game(Field *field, int objectSize);


	template <typename T>
	std::shared_ptr<T> getType(int pos);

	template <typename T>
	void figurePlacement(int& ind, int* positions, int size_of_pos,  Field* field, int objectSize);




	int getLast();
	int getActionState(); 
	int getLockState(); 
	int getSideGlob(int index); 

	void drawAll(sf::RenderWindow *window, Field *field);
	void undo(sf::RenderWindow *window, Field *field);
	void checkIf(sf::RenderWindow *window, Field *field);
	void makeMove(sf::RenderWindow *window, Field *field);
};


#include "Game.tpp"
