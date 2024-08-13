#include "King.h"
#include "Field.h"


King::King(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {
	if (sideColor) 	def("Textures/king.png");
	else def("Textures/kingWhite.png");
}



void King::def(std::string texturePath) {
	if (!textureForm.loadFromFile(texturePath))
		if (!textureForm.create(size, size))
			throw std::invalid_argument("BLARGH");
	figure.setTexture(&textureForm);
}

void King::updateNext(int pos, Field* field) {
	this->pos = pos;
	active.clear();
	attackPos.clear();
	horizMove(field, active, attackPos, true);
	diagMove(field, active, attackPos, toGo, true);
}


void King::figureAction(Field* field, int action) {
	if (action)
		field->setPassMove(active, attackPos, pos);
	else
		field->deactivateMove();


}