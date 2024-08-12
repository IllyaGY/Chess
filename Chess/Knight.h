#pragma once
#include "Figure.h"
class Knight :
    public Figure
{
public:
	sf::Texture black;
	sf::Texture white;

	int toGo[8][3] = {
		{-1,-2, -10},
		{-2,-1,-17},
		{-2,1, -15},
		{-1,2, -6},
		{1, -2, 6},
		{2, -1, 15},
		{2, 1, 17},
		{1,2, 10}
	};
	std::vector<int> active;
	std::vector<int> attackPos;

	Knight(float x, float y, int sideColor, int cubePos, float size);

	void updateNext(int pos, Field* field) override;
	void figureAction(Field* field, int action) override;
};

