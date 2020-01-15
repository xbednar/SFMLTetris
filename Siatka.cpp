#include "Siatka.hpp"
#include "Game.hpp"
#include "Random.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

PoleInfo::PoleInfo(sf::Texture& tekstura, int ID) {
	sf::IntRect rect{ (ID % 7) * 18, 0, 18,18 };													//Odpowiednia pow z tiles.png
	Sprite.setTexture(tekstura);																	//Przypisanie tekstury do Sprite
	Sprite.setTextureRect(rect);
}

Pole& Pole::operator=(const Pole& pole) {
	this->Zajety = pole.Zajety;																		//Operator przypisania wartosci do obiektu
	this->Widoczny = pole.Widoczny;
	this->Info = pole.Info;
	return *this;
}

Siatka::Siatka(sf::Vector2i rozmiar, Game& game): _Game(game), _Pole(), _PoleInfo(), _Rozmiar(rozmiar), _YWyczyszczone(), _ElapsedTime(0.f), _Usunieto(false) {
	for (int x = 0; x < rozmiar.x; x++) {
		for (int y = 0; y < rozmiar.y; y++) {														//Inicjalizacja pol
			_Pole[zamiana(x, y)] = std::make_unique<Pole>();										//Zwraca unique_ptr
		}
	}
	for (int ID = 0; ID < 7; ID++) {
		_PoleInfo[ID] = std::make_unique<PoleInfo>(_Game._Tekstura, ID);							
	}
}

void Siatka::dodajBlok(int ID, std::array<sf::Vector2i, 4> blok) {									
	for (int i = 0; i < 4; i++) {
		auto pole = getPole(blok[i].x, blok[i].y);
		pole->Zajety = true;
		pole->Info = _PoleInfo[ID].get();
	}
}
int Siatka::zamiana(int x, int y) {																	//Zamiana 2D na 1D do uzywania std::map w Siatce
	return y * _Rozmiar.x + x;																		
}

void Siatka::draw(sf::RenderWindow &window) {														//
	for (int x = 0; x < _Rozmiar.x; x++) {
		for (int y = 0; y < _Rozmiar.y; y++) {

			auto pole = getPole(x, y);																			
			if (pole->Zajety && pole->Widoczny) {
				pole->Info->Sprite.setPosition(x * 18.f, y * 18.f);
				window.draw(pole->Info->Sprite);
			}
		}
	}
}

Pole* Siatka::getPole(int x, int y) {																//Zwraca wsk na Pole z kordynatami
	return _Pole[zamiana(x, y)].get();
}

void Siatka::wyczysc() {																			//przy GameOver
	for (int x = 0; x < _Rozmiar.x; x++) {
		for (int y = 0; y < _Rozmiar.y; y++) {
			auto pole = getPole(x, y);
			pole->Zajety = false;
			pole->Widoczny = true;
			pole->Info = nullptr;
		}
	}
}

void Siatka::zaznaczLinie() {
	if (_Usunieto)
		return;
	int liczbaUsunietych = 0;
	for (int y = _Rozmiar.y - 1; y > 0; y--) {
		int licznik = 0;
		for (int x = 0; x < _Rozmiar.x; x++) {
			auto pole = getPole(x, y);
			if (pole->Zajety) {
				licznik++;
			}
			if (licznik == 10) {																	//Pe³na linia
				_YWyczyszczone.push_back(y);														//Element dodany na koniec kontenera
				_Usunieto = true;
				liczbaUsunietych++;
			}
		}
		licznik = 0;
	}
	_Game._wynik.dodajWyczyszczone(liczbaUsunietych);	
	std::sort(_YWyczyszczone.begin(), _YWyczyszczone.end(), [](int left, int right) { return left < right; });
}

void Siatka::wymazLinie() {																			//Ustawia po usunieciu lini
	if (_YWyczyszczone.empty())
		return;
	for (auto i : _YWyczyszczone) {																	//Przez kazda linie
		for (auto y = i; y >= 0; y--) {
			for (auto x = 0; x < _Rozmiar.x; x++) {
				int up = y - 1;
				if (up < 0)
					continue;
				*getPole(x, y) = *getPole(x, up);													//Kopiowanie lini
			}
		}
	}
	_YWyczyszczone.clear();
	_Usunieto = false;
}

void Siatka::update(const sf::Time &dt) {															//Miganie
	zaznaczLinie();
	if (_Usunieto) {
		_ElapsedTime += dt.asSeconds();
		strobe();
		if (_ElapsedTime > 0.6f) {
			_ElapsedTime = 0.f;
			wymazLinie();
		}
	}
}

void Siatka::strobe(){																				//Przyspiesza miganie
	int num = int(_ElapsedTime * 5.f);
	for (auto y : _YWyczyszczone) {
		for (int x = 0; x < _Rozmiar.x; x++) {
			getPole(x, y)->Widoczny = (num % 2 != 0);
		}
	}
}

bool Siatka::czyZajety(std::array<sf::Vector2i, 4> blok) {											//
	for (int i = 0; i < 4; i++) {
		auto  pole = getPole(blok[i].x, blok[i].y);
		if (pole->Zajety) {
			return true;
		}
	}
	return false;
}





