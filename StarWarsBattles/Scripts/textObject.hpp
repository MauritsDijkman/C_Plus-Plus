#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "gameObject.hpp"
#include "bitmapText.hpp"

class TextObject : public GameObject {
private: // Cannot be called outside of the class
	sf::Font& font;
	bitmapText text;
	std::string textStr;
	sf::Vector2f position;
public: // Can be called from other classes (to change or get information)
	TextObject(std::string identifier, sf::Font& font, std::string textStr);
	~TextObject();

	void update() override;
	void render(sf::RenderWindow& window) override;

	std::string getTextStr() const;
	void setText(const std::string textStr);
	void setCharacterSize(const int size);
	void setFillColor(const sf::Color color);
	void setPosition(const sf::Vector2f position);
};
