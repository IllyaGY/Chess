#pragma once
#include <SFML/Graphics.hpp>


class Field; 

class Figure
{
public:
	sf::RectangleShape figure;
	int pos = -1;
	int sideColor = -1;
	float size = 0;
	bool drawable = true;
	

	std::vector<int> active = {};
	std::vector<int> attackPos = {};


	sf::Texture textureForm;

	Figure(float x, float y, int side, int pos, float size);


	void setPos(float x, float y);
	void setPos(sf::Vector2f cubePos);
	void setCubePos(int pos);
	void selectedItem(sf::RenderWindow* window, int i);
	void drawFigure(sf::RenderWindow* window);
	void setUndraw();
	void def(std::string texturePath);


	bool lB(int pos);
	bool rB(int pos);
	bool tB(int pos);
	bool bB(int pos);

	int getSide();
	int getPos();
	bool isClicked(sf::Vector2f pos);

	virtual void updateNext(int pos, Field* field) = 0;
	void figureAction(Field* field, int action);

protected:

	void horizHelper(int move, Field* field, bool (Figure::* func)(int), bool king = false);
	void horizMove(Field* field, bool king = false);

	void diagHelper(Field* field, int &diag, bool &diagPossible, bool(Figure::* func1)(int), bool(Figure::* func2)(int),int toGo);
	void diagMove(Field* field, int* toGo, bool king = false);
	

	friend class Rook;
	friend class Bishop;
	friend class Queen;
};

