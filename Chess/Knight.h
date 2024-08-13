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


	Knight(float x, float y, int sideColor, int cubePos, float size);

	void updateNext(int pos, Field* field) override;
};

