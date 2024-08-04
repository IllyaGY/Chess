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
	bool currentFrame;

	

	Game(Field *field, int objectSize);

	int getLast();
	bool getCurrFrame();
	
	void reverseCurrFrame();
	void drawAll(sf::RenderWindow *window, Field *field);
	void undo(sf::RenderWindow *window, Field *field);
	void checkIf(sf::RenderWindow *window, Field *field);
	void makeMove(sf::RenderWindow *window, Field *field);
};

