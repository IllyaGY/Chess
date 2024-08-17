#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "Figure.h"
#define  SIZE  64 

class Figure;
class Game;


class Field
{
public:
	sf::RectangleShape field[8][8];
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


	Field(int side, int squareSize, int &x, int &y);

	sf::RectangleShape *cubeRet(int pos);
	sf::Vector2f getCoord(int i);


	void def(int start, int end, int inc);

	bool getStatus();
	bool isClicked(sf::Vector2f pos, sf::Vector2f posCurr);
	int cubesClicked(sf::Vector2f pos, Game* game);
	bool sameSides(int currPos, int comparable);
	bool isTaken(int pos); 
	bool isTaken(int posX, int poxY); 
	int emplaceBoard(int oldPos, int newPos);

	void setPassMove(std::vector<int> moveVec, std::vector<int> attackVec, int ourPos);
	void fillBoard(int pos, std::shared_ptr<Figure> figure);
	void deactivateMove();
	void fieldToScreen(sf::RenderWindow *window);
};

