#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "Figure.h"
#include "Pawn.h"
#include "Game.h"
#define  SIZE  64 

class Figure;
class Game;


class Field
{
public:
	sf::RectangleShape field[SIZE];
	std::map<int, std::shared_ptr<Figure>> board;

	sf::RectangleShape green;
	sf::RectangleShape white;

	float s = 0;
	int spawnPos = -1;

	bool setActive = false;
	std::vector<sf::Color> backUp;
	std::vector<sf::Color> backUpAttack;

	float leftOffset = 0;
	float topOffset = 0;


	std::vector<int> activeFields{};
	std::vector<int> activeAttackFields{};


	Field(int squareSize, int &x, int &y);


	sf::Vector2f getCoord(int i);
	bool getStatus();
	bool isClicked(sf::Vector2f pos, sf::Vector2f posCurr);
	int cubesClicked(sf::Vector2f pos, Game* game);
	bool sameSides(int currPos, int comparable);
	bool isTaken(int pos); 

	void setPassMove(std::vector<int> moveVec, std::vector<int> attackVec, int ourPos);
	void fillBoard(int pos, std::shared_ptr<Figure> figure);
	void emplaceBoard(int oldPos, int newPos);
	void deactivateMove();
	void fieldToScreen(sf::RenderWindow *window);
};

