/*
© 2024 IllyaGY
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
#include <array>


class Field; 

enum Points {
	PawnP = 1,
	BishopP = 3,
	KnightP = 3,
	RookP = 5,
	QueenP = 9,
	KingP = 100
};

enum Movement {

	//SHARED
	UP = 8,
	DOWN = -8,

	diagBottomLEFT = -7,
	diagBottomRIGHT = -9,

	limitUP = -1,
	limitDOWN = 64,

	diagUpLEFT = 9,
	diagUpRIGHT = 7,


	LEFT = -1,
	RIGHT = 1,


	rowTOP = 8, // Everything below 8 is the top row
	rowBOTTOM = 55 //Everything higher than 55 is the bottom row

	


};



class Figure
{
public:

	int pointsForFigure;
	
	sf::RectangleShape figure;
	int pos = -1;
	int firstPos = -1; 
	bool firstTime;
	int sideColor = -1;
	float size;

	
	static int diagCoords[4];
	static int XYCoords[4];



	std::vector<int> active = {};
	std::vector<int> attackPos = {};


	static std::vector<std::vector<int>> diagMoves;
	static std::vector<std::vector<int>> XYMoves;

	sf::Texture textureForm;

	Figure(float x, float y, int side, int pos, float size);

	void setPos(float x, float y);
	void setPos(sf::Vector2f cubePos);
	int getPoints();
	void setCubePos(int pos);
	void selectedItem(sf::RenderWindow* window, Field* field, int action);
	void drawFigure(sf::RenderWindow* window);
	void setUndraw();
	void def(std::string texturePath);
	void vecClean();

	void updateMoves(Field* field);
	void setFirstFalse(); 

	static bool lB(int pos);
	static bool rB(int pos);
	static bool tB(int pos);
	static bool bB(int pos);


	static void fillOutDiag();
	static void fillOutXY();

	std::vector<int> getAttackVec();
	std::vector<int> getActive();

	int getSide();
	int getPos();
	int getFirstPos();
	bool isClicked(sf::Vector2f pos);

	
	bool isFirst();
	virtual void updateNext(Field* field) = 0;

protected:


	void diagMove(Field* field, int &pos, int &side);
	static bool diagHelper(std::vector<int>& dirs, int& diag, bool(*func1)(int), bool(*func2)(int), int change);
	
	
	void horizMove(Field* field, int &pos, int &side);
	static bool horizHelper(int &move, bool (* func)(int), int& pos, std::vector<int>& allDirsVec);
	

	
	
	bool canCastle();
	
	friend class Rook;
	friend class Bishop;
	friend class Queen;

	
	
	
};

