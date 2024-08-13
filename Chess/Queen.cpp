#include "Queen.h"
#include "Field.h"

Queen::Queen(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {
	if (sideColor) 	def("Textures/queen.png");
	else def("Textures/queenWhite.png");
}





void Queen::updateNext(int pos, Field* field) {
	this->pos = pos;
	active.clear();
	attackPos.clear();
	horizMove(field);
	diagMove(field, toGo);
}

