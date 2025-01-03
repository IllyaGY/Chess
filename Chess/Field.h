/*
� 2024 IllyaGY
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see https://www.gnu.org/licenses/.
*/

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
	sf::RectangleShape field[8][8];					//Field drawing
	std::map<int, std::shared_ptr<Figure>> board;	//board with all of the objects 


	sf::RectangleShape green;
	sf::RectangleShape white;

	float s = 0;
	int spawnPos = -1;
	

	float leftOffset = 0;
	float topOffset = 0;

	std::vector<sf::Color> backUp;
	std::vector<int> activeFields{};
	int activeSize = 0; 
	int attackSize = 0; 

	Field(int side, int squareSize, int &x, int &y);

	sf::RectangleShape *cubeRet(int pos);
	sf::Vector2f getCoord(int i);


	void def(int start, int end, int inc);


	bool isKing(int pos, int sideOfKing);
	bool isClicked(sf::Vector2f pos, sf::Vector2f posCurr);
	int cubesClicked(sf::Vector2f pos, Game* game);
	int helper(int &, sf::Vector2f pos, int end);
	int isTaken(int pos);
	int isTaken(int posX, int poxY);
	int emplaceBoard(int oldPos, int newPos);
	void clearField();
	bool isCastleSquare(int pos);

	std::shared_ptr<Figure> figurePoint(int boardIndex);


	void setPassMove(Figure *figure);
	void fillBoard(int pos, std::shared_ptr<Figure> figure);
	void deactivateMove();
	void fieldToScreen(sf::RenderWindow *window);
};

