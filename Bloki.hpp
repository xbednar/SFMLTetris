#ifndef BLOKI_HPP
#define BLOKI_HPP
#include <SFML/Graphics.hpp>
#include <array>
#include "Sterowanie.hpp"

class Bloki : public sf::Drawable {
public:
	Bloki(sf::Texture& tekstura, int ID);
	~Bloki() = default;

	void obrot();
	void ruch(Sterowanie kierunek);
	void setPos(const sf::Vector2i& pozycja);
	void powrot();
	std::array<sf::Vector2i, 4> getBlokPos() const;
	std::array<sf::Vector2i, 4> getFutBlokPos(Sterowanie kierunek) const;
	int getID() const;
private:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	sf::Vector2i _Pozycja;
	int _aktObrot;
	int _ID;
	std::array<sf::Vector2i, 4> _Blok;
	std::array<sf::Vector2i, 4> _staryBlok;
	mutable sf::Sprite Sprite;
};

#endif 
