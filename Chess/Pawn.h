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

	int firstTime;

	std::vector<int> active;
	std::vector<int> attackPos;

	Pawn(float x, float y, int sideColor, int cubePos, float size);

	void updateNext(int pos, Field *field) override;	
	void figureAction(Field *field, int action) override;

};

