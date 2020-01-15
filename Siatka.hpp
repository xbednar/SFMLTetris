#ifndef SIATKA_HPP
#define SIATKA_HPP
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <unordered_map>
#include <array>

class Game;
struct PoleInfo {
	PoleInfo(sf::Texture& tekstura, int ID);												//konstruktor z tekstura do wyswietlania, 1 z 7 blokow
	sf::Sprite Sprite;																		//zawiera Sprite ktory wyswietla blok na planszy
};

struct Pole {																				//Pole reprezentuje pola na Siatce i zna jego wlasnosci
	Pole& operator=(const Pole& pole);														//Operator przypisania wartosci do obiektu
	bool Zajety = false;
	bool Widoczny = true;																	//Kazde Pole wskazuje na PoleInfo przez wsk
	PoleInfo* Info = nullptr;																//gdy zostaje zajete przez Blok
};


class Siatka {
public:
	Siatka(sf::Vector2i rozmiar, Game& game);												//Konstruktor
	void update(const sf::Time& dt);
	void wyczysc();
	void dodajBlok(int ID, std::array<sf::Vector2i, 4> blok);								//Kontener std::array<typ_skalowany,ilosc>nazwa; dodaje i laczy ksztalty na planszy
	void draw(sf::RenderWindow& window);
	bool czyZajety(std::array<sf::Vector2i, 4> blok);
	inline bool UsunBlok() const {
		return _Usunieto;
	}
	Pole* getPole(int x, int y);
private:
	int zamiana(int x, int y);																//Zamiana 2D na 1D do KV
	void wymazLinie();
	void zaznaczLinie();
	void strobe();

	Game& _Game;																			//Referencja do klasy Game
	std::unordered_map<unsigned int, std::unique_ptr<Pole>> _Pole;							//Dostep do Pole i PoleInfo ktore sa przechowywane w std::map
	std::unordered_map<unsigned int, std::unique_ptr<PoleInfo>> _PoleInfo;					//int=KeyValue, KV=Bloki=0-6 ; mappedValue 
	sf::Vector2i _Rozmiar;																	//Rozmiar Siatki
	std::vector<int> _YWyczyszczone;														//Pozycja lini Y do czyszczenia
	float _ElapsedTime;
	bool _Usunieto;
};


#endif 


/*
std::map<K, V> mapuje klucz typu K na jakas dowolna wartosc typu V, która nie bierze udzialu w porzadkowaniu kontenera,
ani wyszukiwaniu

unique_ptr - 1 wsk tego typu na obiekt, kiedy przestaje isniec wsk usuwany jest obiekt na ktory wsk pokazywal
a pamiec jest zwalniana,
*/