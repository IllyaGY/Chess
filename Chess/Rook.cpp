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


#include "Rook.h"
#include "Field.h"

Rook::Rook(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {


	pointsForFigure = RookP;
	if (sideColor) def("Textures/rook.png");

	else def("Textures/rookWhite.png");		

}






void Rook::updateNext(Field* field) {	
	horizMove(field, pos, sideColor);
}

void Rook::lookUpFill()
{
}


