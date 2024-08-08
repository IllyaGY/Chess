#pragma once
#include <memory>
#include <SFML/Graphics.hpp>


#include "Pawn.h"
#include "Bishop.h"
#include "Field.h"


#include <vector>
#define PAWN_SIZE 16

class Game
{
public:
	std::vector<std::shared_ptr<Figure>> playerBase{};
	int lastSel = -1;
	bool done = true;
	bool lock = false; 

	Game(Field *field, int objectSize);


	template <typename T>
	std::shared_ptr<T> getType(int pos);

	int getLast();
	int getActionState(); 
	int getLockState(); 

	void drawAll(sf::RenderWindow *window, Field *field);
	void undo(sf::RenderWindow *window, Field *field);
	void checkIf(sf::RenderWindow *window, Field *field);
	void makeMove(sf::RenderWindow *window, Field *field);
};


#include "Game.tpp"
