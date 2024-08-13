#pragma once
#include "Figure.h"
class Knight :
    public Figure
{
public:
	sf::Texture textureForm;

	int toGo[8][2] = {
		{-1,-2},
		{-2,-1},
		{-2,1},
		{-1,2},
		{1, -2},
		{2, -1},
		{2, 1},
		{1,2}
	};
	std::vector<int> active;
	std::vector<int> attackPos;

	Knight(float x, float y, int sideColor, int cubePos, float size);

	void def(std::string texturePath);

	void updateNext(int pos, Field* field) override;
	void figureAction(Field* field, int action) override;
};

