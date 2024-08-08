#include "Bishop.h"
#include "Figure.h"
#include "Field.h"


Bishop::Bishop(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {






	if (!black.loadFromFile("Textures/bishop.png"))
		if (!black.create(size, size))
			throw std::invalid_argument("BLARGH");

	if (!white.loadFromFile("Textures/bishopWhite.png"))
		if (!white.create(size, size))
			throw std::invalid_argument("BLARGH");

}


void Bishop::setFigure(int sideColor) {
	if (sideColor)
		figure.setTexture(&black);
	else
		figure.setTexture(&white);

}


int Bishop::getSide() {
	return sideColor;
}

void Bishop::updateNext(int pos, Field *field) {				//TRASH CODE - REWRITE
	active.clear();
	attackPos.clear();
	bool diagPossible[4];
	for (auto& i : diagPossible) i = false;
	int diag[4] = {};
	for (auto& i : diag) i = pos;
	while (!diagPossible[0] || !diagPossible[1] || !diagPossible[2] || !diagPossible[3]) {
		if (!diagPossible[0] && (diag[0] % 8) != 0 && diag[0] >= 9) {
			if (!field->isTaken(diag[0] - 9)) {
				diag[0] -= 9;
				active.push_back(diag[0]);
			}
			else {
				attackPos.push_back(diag[0] - 9);
				diagPossible[0] = true;
			}
		}
		else diagPossible[0] = true;
		if (!diagPossible[1] && (diag[1] - 7) % 8 != 0 && diag[1] >= 7) {
			if (!field->isTaken(diag[1] - 7)) {
				diag[1] -= 7;
				active.push_back(diag[1]);
			}
			else {
				attackPos.push_back(diag[1] - 7);
				diagPossible[1] = true;
			}
		}
		else diagPossible[1] = true;
		if (!diagPossible[2] && diag[2] % 8 != 0 && diag[2] + 7 < 64) {
			if (!field->isTaken(diag[2] + 7)) {
				diag[2] += 7;
				active.push_back(diag[2]);
			}
			else {
				attackPos.push_back(diag[2] + 7);
				diagPossible[2] = true;
			}
		}
		else diagPossible[2] = true;
		if (!diagPossible[3] && (diag[3] - 7) % 8 != 0 && diag[3] + 9 < 64) {
			if (!field->isTaken(diag[3] + 9)) {
				diag[3] += 9;
				active.push_back(diag[3]);
			}
			else {
				attackPos.push_back(diag[3] + 9);
				diagPossible[3] = true;
			}
		}
		else diagPossible[3] = true;
	}
	

}


void Bishop::figureAction(Field* field, int action) {
	if (action)
		field->setPassMove(active, attackPos, pos);
	else
		field->deactivateMove();


}
