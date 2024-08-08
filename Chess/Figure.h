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
	bool drawable = true; 

	Figure(float x, float y, int side, int pos, float size);

	
	void setPos(float x, float y);
	void setPos(sf::Vector2f cubePos);
	void setCubePos(int pos);
	void selectedItem(sf::RenderWindow *window, int i);
	void drawFigure(sf::RenderWindow *window);
	void setUndraw();
	

	int getPos();
	bool isClicked(sf::Vector2f pos);
	
	virtual void updateNext(int pos, Field *field) = 0;
	virtual void figureAction(Field *field, int action) = 0;


};

