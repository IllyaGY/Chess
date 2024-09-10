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
#include <iostream>
#include "Field.h"

class Field;





class Pawn : public Figure
{
public:
	
	bool promote;
	int enPass;

	static int pawnMovesWhite;
	static int pawnMovesBlack;
	static int toAttackWhite[2];
	static int toAttackBlack[2];
	static int limitWhite; 
	static int limitBlack; 
	
	static std::vector<std::vector<int>> moveLookUpBlack;
	static std::vector<std::vector<int>> moveLookUpWhite;


	

	Pawn(float x, float y, int sideColor, int cubePos, float size);

	bool checkIfEnPass();
	bool checkHit(int hitPos, int objPos);
	bool checkPromotion();

	void defWhite(int toGo, int toA1, int toA2, int limit,  std::string texture);
	void updateNext(Field *field) override;

	static void define();


	static void lookUpFill();
	static void lookUpFillHelper(std::vector<std::vector<int>> &moveLookUp, const int &pawnMoves, const int* toAttack, const int& limit, int side);
	void passToEn(int enPos);
	void clearEnPass();

	int getEnPass();
};

