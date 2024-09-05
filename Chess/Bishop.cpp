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

