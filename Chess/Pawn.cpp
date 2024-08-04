#include "Pawn.h"


Pawn::Pawn(float x, float y, int sideColor, int cubePos, float size)
	: Figure(x, y, sideColor, cubePos, size) {

	active = { cubePos + 8, cubePos + 16 };


	if (!texture.loadFromFile("Textures/pawn.png"))




		if (!texture.create(size, size))
			throw std::invalid_argument("BLARGH");

}


void Pawn::setFigure() {

	figure.setTexture(&texture);


}


int Pawn::getSide() {
	return sideColor;
}

void Pawn::updateNext(int pos) {
	active.clear();
	active.push_back(pos + 8);
}


void Pawn::movement(Field *field, int action){
	if (action) {

		field->setPassMove(active);

	}
	else
		field->deactivateMove();


}