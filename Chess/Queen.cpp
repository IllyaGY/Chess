#include "Queen.h"
#include "Field.h"

Queen::Queen(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	pointsForFigure = QueenP;
	if (sideColor) 	def("Textures/queen.png");
	else def("Textures/queenWhite.png");
}





void Queen::updateNext(Field* field) {

	horizMove(field, pos, sideColor);
	diagMove(field, pos, sideColor);
}

void Queen::lookUpFill()
{
}

