#pragma once
#include "Figure.h"
class Figure;

class Bishop :
    public Figure
{
public:


	Bishop(float x, float y, int sideColor, int cubePos, float size);



	void updateNext(Field* field) override;
	static void lookUpFill();

};

