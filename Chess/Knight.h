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
class Knight :
    public Figure
{
public:
	sf::Texture textureForm;

	int knightMoves[8][2] = {
		{-1,-2},
		{-2,-1},
		{-2,1},
		{-1,2},
		{1, -2},
		{2, -1},
		{2, 1},
		{1,2}
	};


	Knight(float x, float y, int sideColor, int cubePos, float size);

	void updateNext(Field* field) override;
	static void lookUpFill();
};

