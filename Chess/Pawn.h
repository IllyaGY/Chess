#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Field.h"

class Field;


class Pawn : public Figure
{
public:
	sf::Texture black;
	sf::Texture white;

	std::vector<int> active;
	std::vector<int> attackPos;

	Pawn(float x, float y, int sideColor, int cubePos, float size);

	void setFigure(int sideColor);
	void updateNext(int pos) override;	
	void figureAction(Field *field, int action);


	
	int getSide();
};

