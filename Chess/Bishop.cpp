
/*
� 2024 IllyaGY
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



#include "Bishop.h"
#include "Figure.h"
#include "Field.h"


Bishop::Bishop(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	pointsForFigure = BishopP;
	if (sideColor) def("Textures/bishop.png");

	else def("Textures/bishopWhite.png");

}






void Bishop::updateNext(Field *field) {				
	diagMove(field, pos, sideColor);
}

void Bishop::lookUpFill()
{

}

