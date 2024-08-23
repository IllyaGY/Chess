#include <SFML/Graphics.hpp>
#include <iostream>
#include "wtypes.h"
#include "Field.h"
#include "Figure.h"
#include "Pawn.h"
#include "Game.h"
#include "Bishop.h"

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


	Field field(side, OBJECT_SIZE, x, y);

	Game game(side, &field, OBJECT_SIZE);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased)
				game.lock = false; 
			
				


		}
		window.clear();

		if (game.end()) {
			game.deletePlayers(&field);
			game.winScreen(&window, x / 2, y / 2);
			window.display();

		}
		else {
			field.fieldToScreen(&window);
			game.drawAll(&window, &field);
			window.display();




			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !game.getLockState()) {
				if (game.getActionState())
					game.checkIf(&window, &field);

				if (!game.getActionState() && !game.getLockState() && game.getLast() > -1)
					game.makeMove(&window, &field);


			}


		}
	}

	return 0;
}