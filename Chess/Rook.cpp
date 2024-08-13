#include "Rook.h"
#include "Field.h"

Rook::Rook(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {


	if (sideColor) def("Textures/rook.png");

	else def("Textures/rookWhite.png");		

}






void Rook::updateNext(int pos, Field* field) {	
	this->pos = pos;
	active.clear();
	attackPos.clear();
	horizMove(field);
}		


