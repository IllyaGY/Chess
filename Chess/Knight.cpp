#include "Knight.h"
#include "Field.h"


Knight::Knight(float x, float y, int sideColor, int cubePos, float size) : Figure(x, y, sideColor, cubePos, size) {

	pointsForFigure = KnightP;
	if (sideColor) 	def("Textures/knight.png");
	else	def("Textures/knightWhite.png");
}





void Knight::updateNext(Field* field) {			
	int posIn2D[2] = {pos/8, pos%8};
	for (int i = 0; i < 8; i++) {
		int x = posIn2D[0] + knightMoves[i][0];
		int y = posIn2D[1] + knightMoves[i][1];
		if (field->isTaken(x, y) == -1) {
			if (x >= 0 && x < 8 && y >= 0 && y < 8)
				active.push_back(x * 8 + y);
		}
		else 
			if (field->isTaken(x, y) != sideColor)
				attackPos.push_back(x * 8 + y);
			
	}
}
