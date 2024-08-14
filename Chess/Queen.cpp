#include "Queen.h"
#include "Field.h"

Queen::Queen(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {
	if (sideColor) 	def("Textures/queen.png");
	else def("Textures/queenWhite.png");
}





void Queen::updateNext(Field* field) {

	horizMove(field);
	diagMove(field);
}

