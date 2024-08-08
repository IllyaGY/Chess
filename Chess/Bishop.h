#pragma once
#include "Figure.h"
class Figure;

class Bishop :
    public Figure
{
public:
	sf::Texture black;
	sf::Texture white;

	std::vector<int> active;
	std::vector<int> attackPos;

	Bishop(float x, float y, int sideColor, int cubePos, float size);

	void BishopActiveSet(Field* field);
	void setFigure(int sideColor);
	void figureAction(Field* field, int action);


	void updateNext(int pos, Field *field) override;


	int getSide();

};

