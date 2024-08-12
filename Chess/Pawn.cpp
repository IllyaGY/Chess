#include "Pawn.h"
#include "Figure.h"

Pawn::Pawn(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	
	firstTime = cubePos; 

	if(sideColor){
		if (!black.loadFromFile("Textures/pawn.png"))
		if (!black.create(size, size))
			throw std::invalid_argument("BLARGH");
		figure.setTexture(&black);
	}

	else {
		if (!white.loadFromFile("Textures/pawnWhite.png"))
		if (!white.create(size, size))
			throw std::invalid_argument("BLARGH");
		figure.setTexture(&white);
	}

}





int Pawn::getSide() {
	return sideColor;
}

void Pawn::updateNext(int pos, Field *field) {			//THINK OF A DIFFERENT UPDATE COZ BISHOP IS WAY DIFFERENT
	this->pos = pos; 
	active.clear();
	attackPos.clear(); 
	if (sideColor) {
		if (pos - 8 >= 0 && !field->isTaken(pos - 8)) {
			active.push_back(pos - 8);
			if (firstTime == pos && pos - 16 >= 0 && !field->isTaken(pos - 16)) {
				active.push_back(pos - 16);
			}
		}
		if (pos % 8 != 0 && pos - 9 >= 0) {
			attackPos.push_back(pos - 9);
		}
		if ((pos - 7) % 8 != 0 && pos - 7 >= 0) {
			attackPos.push_back(pos - 7);

		}
	}
	else {
		if (pos + 8 < 64 && !field->isTaken(pos + 8)) {
			active.push_back(pos + 8);
			if (firstTime == pos && pos + 16 < 64 && !field->isTaken(pos + 16)) {
				active.push_back(pos + 16);
			}
		}
		if (pos % 8 != 0 && pos + 9 < 64) {
			attackPos.push_back(pos + 9);
		}
		if ((pos + 7) % 8 != 0 && pos + 7 < 64) {
			attackPos.push_back(pos + 7);

		}
	}
	
}


void Pawn::figureAction(Field *field, int action){
	if (action) 
		field->setPassMove(active,attackPos,pos);
	else
		field->deactivateMove();


}
