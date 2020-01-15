#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"
#include "Menu.hpp"
#define MAX_LICZBA_POZIOMOW 2

int main()
{
	int menu_selected_flag = 0;
	sf::RenderWindow window(sf::VideoMode(300, 19 * 19), "Tetris");
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
				{
					menu.moveUp();
				}

				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
				{
					menu.moveDown();
				}
				if (menu_selected_flag == 0) {
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0) {
						Game game;
						game.run();
						menu_selected_flag = 0;
					}

					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1) {
						exit(1);
						menu_selected_flag = 1;
					}
				}

			}
		}
		window.clear();
		if (menu_selected_flag == 0)
			menu.draw(window);
		window.display();
	}

	return 0;
}




