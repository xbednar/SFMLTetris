#ifndef WYNIK_HPP
#define WYNIK_HPP
#include <SFML/Graphics.hpp>


class Wynik {
public:
	Wynik();
	void draw(sf::RenderWindow& window);
	void reset();
	void dodajsWynik(int score);
	void sumujsWynik();
	void dodajWyczyszczone(int num);
	void update(const sf::Time& dt);
	void GameOver();
	void drawPause();
	int getLevel() const;
	void zapiszWynik();
	void Highscore();
	
private:
	sf::Font _Font;
	sf::Text _LevelText;
	sf::Text _WynikText;
	sf::Text _WyczyszczoneText;
	sf::Text _GameOverText;
	sf::Text _InstrukcjaText;
	sf::Text _InstrukcjaText2;

	int stan;
	int _Highscore;
	int _Wynik;
	int _najWynik;
	int _loadsWynik;
	int _linieWyczyszczone;
	bool _isGameOver;
	bool _ifdrawPause;
	bool _HS;
	static bool sort_function(double p, double q);
};


#endif 