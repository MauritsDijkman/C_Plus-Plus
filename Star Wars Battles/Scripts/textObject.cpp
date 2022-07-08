#include "textObject.hpp"

TextObject::TextObject(std::string identifier, sf::Font& font, std::string textStr) : GameObject(identifier), font(font), textStr(textStr) {
	// Seths the text to the given values when created
	this->text.setString(this->textStr);
	this->text.setPosition(this->position.x, this->position.y);
	this->text.setCharacterSize(12);
	this->text.setFillColor(sf::Color::Black);
}

// Deletes everything after code has been runned
TextObject::~TextObject() { }

// Updates the textobject
void TextObject::update() { }

// Renders the textobject in the window
void TextObject::render(sf::RenderWindow& window) {
	window.draw(this->text);
}

// Returns a string with the text of the textobject
std::string TextObject::getTextStr() const {
	return this->textStr;
}

// Sets the text of the textobject to the given string
void TextObject::setText(const std::string textStr) {
	this->textStr = textStr;
	this->text.setString(this->textStr);
}

// Sets the charactersize of the text to the given size
void TextObject::setCharacterSize(const int size) {
	this->text.setCharacterSize(size);
}

// Sets the fillcolor of the text to the given color
void TextObject::setFillColor(const sf::Color color) {
	this->text.setFillColor(color);
}

// Sets the postion of the text to the given vector2 position
void TextObject::setPosition(const sf::Vector2f position) {
	this->text.setPosition(position.x, position.y);
}
