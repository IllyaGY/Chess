#include "Rook.h"
#include "Field.h"

Rook::Rook(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {


	if (sideColor) def("Textures/rook.png");

	else def("Textures/rookWhite.png");		

}

void Rook::def(std::string texturePath) {
	if (!textureForm.loadFromFile(texturePath))
		if (!textureForm.create(size, size))
			throw std::invalid_argument("BLARGH");
	figure.setTexture(&textureForm);
}





void Rook::updateNext(int pos, Field* field) {	
	this->pos = pos;
	active.clear();
	attackPos.clear();
	horizMove(field,active, attackPos);
}		


void Rook::figureAction(Field* field, int action) {
	if (action)
		field->setPassMove(active, attackPos, pos);
	else
		field->deactivateMove();


}