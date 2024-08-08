#include "Figure.h"
#include "Field.h"

Figure::Figure(float x, float y, int side, int pos, float size) {
	sideColor = side;
	this->pos = pos;
	this->size = size;
	this->figure.setSize(sf::Vector2f(size, size));
	this->figure.setPosition(sf::Vector2f(x, y));
}

void Figure::setPos(float x, float y) {
	this->figure.setPosition(sf::Vector2f(x, y));


}

void Figure::setPos(sf::Vector2f cubePos) {
	this->figure.setPosition(cubePos);

}

bool bordering(int side, int pos) {
	if (side) return true; 
} // Left - 0 Right - 1

int Figure::getPos() {
	return pos;
}

void Figure::drawFigure(sf::RenderWindow *window) {
	window->draw(figure);
}

bool Figure::isClicked(sf::Vector2f pos) {
	sf::Vector2f p = figure.getPosition();
	if (float(pos.x) >= figure.getPosition().x && float(pos.x) <= figure.getPosition().x + 100.f && float(pos.y) >= figure.getPosition().y && float(pos.y) <= figure.getPosition().y + 100.f)
		return true;
	return false;
}

void Figure::setUndraw() {
	this->setPos(0, 0);
	this->figure.setSize(sf::Vector2f(0, 0));
	pos = -1;
}

void Figure::selectedItem(sf::RenderWindow *window, int i) {
	if (i)
		figure.setFillColor(sf::Color::Green);
	else
		figure.setFillColor(sf::Color::White);





}
