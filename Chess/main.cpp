#include <SFML/Graphics.hpp>
#include <iostream>
#include "wtypes.h"
#include "Field.h"
#include "Figure.h"
#include "Pawn.h"
#include "Game.h"

#define OBJECT_SIZE 100.f

void ScreenRes(int &x, int &y) {
	RECT desktop;
	HWND win = GetDesktopWindow();
	GetWindowRect(win, &desktop);
	x = desktop.right;
	y = desktop.bottom;


}


int main()
{


	int side = 0;
	int x = 0, y = 0;
	ScreenRes(x, y);
	sf::RenderWindow window(sf::VideoMode(x, y), "SFML works!");
	window.clear();
	sf::Text text;
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(24); // in pixels, not points!


	Field field(OBJECT_SIZE, x, y);

	Game game(&field, OBJECT_SIZE);

	Pawn pawn(field.getCoord(24 + 2).x, field.getCoord(24 + 2).y, 0, 24 + 2, OBJECT_SIZE);
	pawn.setFigure();



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased)
				game.reverseCurrFrame();

		}
		
		window.clear();







		text.setString(sf::Mouse::getPosition().x + " " + sf::Mouse::getPosition().y);
		window.draw(text);




		field.fieldToScreen(&window);
		pawn.drawFigure(&window);
		game.drawAll(&window, &field);
		window.display();


		
		
		if(!game.getCurrFrame() && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			game.checkIf(&window, &field);

		if (field.getStatus() && game.getLast() > -1) {
			game.makeMove(&window, &field);
		}




	}

	return 0;
}