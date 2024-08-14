#pragma once
#include "Figure.h"
class King :
    public Figure
{
public:

	King(float x, float y, int sideColor, int cubePos, float size);


	void updateNext(Field* field) override;

};

