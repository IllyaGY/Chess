#pragma once
#include "Figure.h"
class Rook :
    public Figure
{
	sf::Texture black;
	sf::Texture white;

	int firstTime;

	std::vector<int> active;
	std::vector<int> attackPos;

	Rook(float x, float y, int sideColor, int cubePos, float size);

	void updateNext(int pos, Field* field) override;
	void figureAction(Field* field, int action) override;
};

