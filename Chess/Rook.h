#pragma once
#include "Figure.h"
class Rook :
    public Figure
{

public: 

	
	sf::Texture textureForm;


	std::vector<int> active;
	std::vector<int> attackPos;

	Rook(float x, float y, int sideColor, int cubePos, float size);

	void def(std::string texturePath);


	void updateNext(int pos, Field* field) override;
	void figureAction(Field* field, int action) override;
};

