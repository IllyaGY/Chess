#include "Bishop.h"
#include "Figure.h"
#include "Field.h"


Bishop::Bishop(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	if (sideColor) def("Textures/bishop.png");

	else def("Textures/bishopWhite.png");

}


void Bishop::def(std::string texturePath) {
	if (!textureForm.loadFromFile(texturePath))
		if (!textureForm.create(size, size))
			throw std::invalid_argument("BLARGH");
	figure.setTexture(&textureForm);
}




void Bishop::updateNext(int pos, Field *field) {				
	this->pos = pos;
	active.clear();
	attackPos.clear();
	diagMove(field, active, attackPos, toGo);
}


void Bishop::figureAction(Field* field, int action) {
	if (action)
		field->setPassMove(active, attackPos, pos);
	else
		field->deactivateMove();


}
