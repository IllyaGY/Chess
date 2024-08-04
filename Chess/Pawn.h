#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Figure.h"
#include "Field.h"

class Pawn : public Figure
{
public:
	sf::Texture texture;

	std::vector<int> active;

	Pawn(float x, float y, int sideColor, int cubePos, float size);

	void setFigure();
	void updateNext(int pos);	
	void movement(Field *field, int action) override;

	
	int getSide();
};

