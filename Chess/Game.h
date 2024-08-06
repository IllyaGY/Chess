#pragma once
#include <memory>
#include <SFML/Graphics.hpp>


#include "Pawn.h"
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

	int getLast();

	void remove(std::shared_ptr<Figure> figure);
	void drawAll(sf::RenderWindow *window, Field *field);
	void undo(sf::RenderWindow *window, Field *field);
	void checkIf(sf::RenderWindow *window, Field *field);
	void makeMove(sf::RenderWindow *window, Field *field);
};

