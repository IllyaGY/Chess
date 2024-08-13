#include "King.h"
#include "Field.h"


King::King(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {
	if (sideColor) 	def("Textures/king.png");
	else def("Textures/kingWhite.png");
}




void King::updateNext(int pos, Field* field) {
	this->pos = pos;
	active.clear();
	attackPos.clear();
	horizMove(field, true);
	diagMove(field, toGo, true);
}



