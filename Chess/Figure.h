#pragma once
#include <SFML/Graphics.hpp>


class Field; 

class Figure
{
public:
	sf::RectangleShape figure;
	int pos = -1;
	int sideColor = -1;
	float size = 0;


	Figure(float x, float y, int side, int pos, float size);


	void setPos(float x, float y);
	void setPos(sf::Vector2f cubePos);
	void selectedItem(sf::RenderWindow *window, int i);
	void drawFigure(sf::RenderWindow *window);

	int getPos();
	bool isClicked(sf::Vector2f pos);

	virtual void figureAction(Field *field, int action) = 0;


};

