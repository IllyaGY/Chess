#pragma once
#include "Figure.h"
class Figure;

class Bishop :
    public Figure
{
public:
	sf::Texture textureForm;


	int toGo[4] = { -9, -7, 7, 9 };
	std::vector<int> active;
	std::vector<int> attackPos;

	Bishop(float x, float y, int sideColor, int cubePos, float size);

	void def(std::string texturePath);



	void updateNext(int pos, Field* field) override;
	void figureAction(Field* field, int action) override ;


};

