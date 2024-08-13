#pragma once
#include "Figure.h"
class King :
    public Figure
{
public:

	int toGo[4] = { -9, -7, 7, 9 };

	King(float x, float y, int sideColor, int cubePos, float size);


	void updateNext(int pos, Field* field) override;

};

