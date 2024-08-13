#include "Queen.h"
#include "Field.h"

Queen::Queen(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {
	if (sideColor) 	def("Textures/queen.png");
	else def("Textures/queenWhite.png");
}



void Queen::def(std::string texturePath) {
	if (!textureForm.loadFromFile(texturePath))
		if (!textureForm.create(size, size))
			throw std::invalid_argument("BLARGH");
	figure.setTexture(&textureForm);
}

void Queen::updateNext(int pos, Field* field) {
	this->pos = pos;
	active.clear();
	attackPos.clear();
	horizMove(field, active, attackPos);
	diagMove(field, active, attackPos, toGo);
}


void Queen::figureAction(Field* field, int action) {
	if (action)
		field->setPassMove(active, attackPos, pos);
	else
		field->deactivateMove();


}
