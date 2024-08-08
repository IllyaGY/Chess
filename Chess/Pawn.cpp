#include "Pawn.h"
#include "Figure.h"

Pawn::Pawn(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {


	if (sideColor)
		active = { cubePos - 8, cubePos - 16 };
	else
		active = { cubePos + 8, cubePos + 16 };




	attackPos = {};
	if (cubePos % 8 != 0) {
		attackPos.push_back(cubePos + 7);
	}
	if((cubePos-7) % 8 != 0) {
		attackPos.push_back(cubePos + 9);
	}

	if (!black.loadFromFile("Textures/pawn.png"))
	if (!black.create(size, size))
		throw std::invalid_argument("BLARGH");

	if (!white.loadFromFile("Textures/pawnWhite.png"))
	if (!white.create(size, size))
		throw std::invalid_argument("BLARGH");

}


void Pawn::setFigure(int sideColor) {
	if (sideColor)
		figure.setTexture(&black);
	else
		figure.setTexture(&white);

}


int Pawn::getSide() {
	return sideColor;
}

void Pawn::updateNext(int pos) {			//THINK OF A DIFFERENT UPDATE COZ BISHOP IS WAY DIFFERENT
	this->pos = pos; 
	active.clear();
	attackPos.clear(); 
	if (sideColor) {
		active.push_back(pos - 8);
		if (pos % 8 != 0) {
			attackPos.push_back(pos - 9);
		}
		if ((pos - 7) % 8 != 0) {
			attackPos.push_back(pos - 7);
			
		}
	}
	else {
		active.push_back(pos + 8);
		if (pos % 8 != 0) {
			attackPos.push_back(pos + 7);
		}
		if ((pos - 7) % 8 != 0) {
			attackPos.push_back(pos + 9);
		}
	}
	
}


void Pawn::figureAction(Field *field, int action){
	if (action) 
		field->setPassMove(active,attackPos,pos);
	else
		field->deactivateMove();


}
