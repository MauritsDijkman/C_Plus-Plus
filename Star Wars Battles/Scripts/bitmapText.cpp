#include "bitmapText.hpp"
#include <cstdio>

// source: opengameart.org, made by domsson, license CC0
// I edited the font so that it has no background
std::string defaultFilename = "Assets/Fonts/font.png";
// character width & height:
int defaultCw = 7;
int defaultCh = 9;
int defaultCols = 18;

sf::Texture defaultFontTexture;
sf::Sprite defaultFontSprite;

bitmapText::bitmapText()
{
	// Loads the texture if it is not loaded already and turns it into a sprite
	static bool textureLoaded = false;
	if (!textureLoaded) {
		defaultFontTexture.loadFromFile(defaultFilename);
		defaultFontSprite.setTexture(defaultFontTexture);
		textureLoaded = true;
	}
	// initialize with default values, including default font sprite:
	this->cw = defaultCw;
	this->ch = defaultCh;
	this->cols = defaultCols;
	fontSprite = &defaultFontSprite;
	x = 0;
	y = 0;
	scale = 1;
	ox = 0;
	oy = 0;
	text = "";
}

// Sets the position of the text
void bitmapText::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

// Sets the origin of the text
void bitmapText::setOrigin(float originX, float originY) {
	ox = originX;
	oy = originY;
}

// Sets the text to the given text
void bitmapText::setString(const std::string& text) {
	this->text = text;
}

// Sets the scale of the text
void bitmapText::setScale(float scale) {
	this->scale = scale;
}

// Sets the character size of the text
void bitmapText::setCharacterSize(int pixelHeight) {
	scale = 1.0 * pixelHeight / ch;
}

// Sets the fill color of the text
void bitmapText::setFillColor(const sf::Color& color) {
	this->color = color;
}

// Sets the font with the given sprite, width, height and columns
void bitmapText::setFont(sf::Sprite& fontSprite, int charWidth, int charHeight, int columns) {
	this->fontSprite = &fontSprite;
	cw = charWidth;
	ch = charHeight;
	cols = columns;
}

// Gets the bounds of the text
sf::FloatRect bitmapText::getLocalBounds() {
	return sf::FloatRect(0, 0, scale * text.length() * cw, scale * ch);
}

// Draws the text on screen
void bitmapText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	fontSprite->setScale(sf::Vector2f(scale, scale));
	fontSprite->setColor(color);
	for (int i = 0; i < text.length(); i++) {
		int ascii = (int)text[i];
		if (ascii < 32 && ascii >= 128) {
			ascii = 32; // insert space for unknown characters
		}
		int frame = ascii - 32;
		int col = frame % cols;
		int row = frame / cols;

		fontSprite->setTextureRect(sf::IntRect(col * cw, row * ch, cw, ch));
		fontSprite->setPosition(x + i * cw * scale - ox, y - oy);
		target.draw(*fontSprite, states);
	}
}

// Renders the text in the window
void bitmapText::render(sf::RenderWindow& window) {
	window.draw(*this);
}
