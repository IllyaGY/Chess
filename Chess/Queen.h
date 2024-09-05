#pragma once
#include "Figure.h"
class Queen :
    public Figure
{
public:





	Queen(float x, float y, int sideColor, int cubePos, float size);


	void updateNext(Field* field) override;
	static void lookUpFill();

};

