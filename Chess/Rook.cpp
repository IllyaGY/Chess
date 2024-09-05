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


