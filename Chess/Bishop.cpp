#include "Bishop.h"
#include "Figure.h"
#include "Field.h"


Bishop::Bishop(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	if (sideColor) def("Textures/bishop.png");

	else def("Textures/bishopWhite.png");

}






void Bishop::updateNext(int pos, Field *field) {				
	this->pos = pos;
	active.clear();
	attackPos.clear();
	diagMove(field, toGo);
}

