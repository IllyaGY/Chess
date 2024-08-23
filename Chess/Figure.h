#pragma once
#include <SFML/Graphics.hpp>


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
	float size = 0;
	bool drawable = true;
	
	int diagCoords[4] = { diagBottomRIGHT, diagBottomLEFT, diagUpRIGHT, diagUpLEFT };
	int XYCoords[4] = { DOWN, LEFT, RIGHT, UP  };


	std::vector<int> active = {};
	std::vector<int> attackPos = {};


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

	bool lB(int pos);
	bool rB(int pos);
	bool tB(int pos);
	bool bB(int pos);

	std::vector<int> getAttackVec();
	std::vector<int> getActive();

	int getSide();
	int getPos();
	bool isClicked(sf::Vector2f pos);

	
	bool isFirst();
	virtual void updateNext(Field* field) = 0;

protected:

	

	void horizHelper(int move, Field* field, bool (Figure::* func)(int));
	void horizMove(Field* field);

	void diagHelper(Field* field, int &diag, bool &diagPossible, bool(Figure::* func1)(int), bool(Figure::* func2)(int),int toGo);
	void diagMove(Field* field);
	bool canCastle();
	
	friend class Rook;
	friend class Bishop;
	friend class Queen;

	
	
	
};

