#pragma once
#include "Figure.h"
class Rook :
    public Figure
{

public: 


	Rook(float x, float y, int sideColor, int cubePos, float size);

	

	void updateNext(Field* field) override;
	static void lookUpFill();
};

