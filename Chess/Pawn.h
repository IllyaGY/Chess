#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Field.h"

class Field;


class Pawn : public Figure
{
public:

	int toGo;
	int toAttack[2];
	int limit; 

	sf::Texture textureForm;

	int firstTime;

	std::vector<int> active;
	std::vector<int> attackPos;

	Pawn(float x, float y, int sideColor, int cubePos, float size);


	void def(int toGo, int toA1, int toA2, int limit,  std::string texture);
	void updateNext(int pos, Field *field) override;	
	void figureAction(Field *field, int action) override;

};

