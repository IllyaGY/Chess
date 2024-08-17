#include "King.h"
#include "Field.h"


King::King(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {
	
	pointsForFigure = KingP;
	if (sideColor) 	def("Textures/king.png");
	else def("Textures/kingWhite.png");
}




void King::updateNext(Field* field) {
	horizMove(field, true);
	diagMove(field, true);
}


void King::check() {
	
}


