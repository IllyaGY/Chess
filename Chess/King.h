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
#include "Figure.h"

enum Castling {
	CastleLeft = -4,
	CastleRight = 3,
	CastlingLeft = -3,
	CastlingRight = 2,
	CastleNewPosLeft = -2,
	CastleNewPosRight = 1,

};


class King :
    public Figure
{
public:


	std::map<int, std::vector<int>> castlingToCastle{ };

	std::vector<int> castlingVec{};
	std::vector<int> castlingFig{}; 
	std::vector<int> castleNewPos{}; 
	std::vector<int> checkList{}; 

	bool castlingLeft;
	bool castlingRight;
	bool castling;

	King(float x, float y, int sideColor, int cubePos, float size);

	std::vector<int> getRook(int castlingPos);


	std::vector<int> getChecks();

	void setCastling();
	void setCastlingLeft(bool);
	void setCastlingRight(bool);

	bool XYPosEnemy(int thread, int kingPos);

	bool getFirst();

	bool diagPosEnemy(int thread, int kingPos);

	void setFirstFalse();

	void castlingCheck(Field* field);

	void updateNext(Field* field) override;
	static void lookUpFill();

	std::vector<int> getCastlingVec();
	bool getCastlingBool(); 



};

