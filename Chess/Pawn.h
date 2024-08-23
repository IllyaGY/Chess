#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Field.h"

class Field;





class Pawn : public Figure
{
public:
	
	int enPass;
	int pawnMoves;
	int toAttack[2];
	int limit; 



	

	Pawn(float x, float y, int sideColor, int cubePos, float size);

	bool checkIfEnPass();
	bool checkHit(int hitPos, int objPos);

	void def(int toGo, int toA1, int toA2, int limit,  std::string texture);
	void updateNext(Field *field) override;	
	void passToEn(int enPos);
	void clearElPass();

	int getEnPass();
};

