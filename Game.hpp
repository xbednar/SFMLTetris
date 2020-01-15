#ifndef GAME_HPP
#define GAME_HPP
#include "Siatka.hpp"
#include "Bloki.hpp"
#include "Wynik.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <cstdlib>


class Game {

	friend class Grid;																						//Dostep do prywatnych pol klasy

public:
	Game();
	void run();

sf::Texture _Tekstura;
	Wynik _wynik;

private:
	void przystap(Sterowanie kierunek);
	void update(const sf::Time& dt);
	void obrot();
	void stworzBlok();
	bool czyMoznaRuch(std::array<sf::Vector2i, 4> blok);
	bool czyZajety(int x, int y);
	void wydarzenia();
	void render();

	sf::RenderWindow _RenderWindow;
	sf::RectangleShape _liniaSep;
	std::unique_ptr<Bloki> _Blok;																			//Kontrolowany blok
	std::unique_ptr<Bloki> _Podglad;																		//Podglad nastepnego bloku
	std::unique_ptr<Siatka> _Siatka;
	sf::Time _ElapsedTime;
	int _ID;
	
};

#endif 
