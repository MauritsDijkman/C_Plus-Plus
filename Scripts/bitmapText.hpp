#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class bitmapText : public sf::Drawable {
public:
	bitmapText();

	void setPosition(float x, float y);
	void setOrigin(float originX, float originY);
	/// <summary>
	/// Sets the text. Note: newlines or non-ASCII characters are not supported.
	/// </summary>
	void setString(const std::string& text);
	void setScale(float scale);
	void setCharacterSize(int pixelHeight);
	void setFillColor(const sf::Color& color);
	/// <summary>
	/// Sets the font sprite. This must be a monospace font sprite, 
	/// including the ASCII characters 32 up to 127.
	/// </summary>
	/// <param name="fontSprite">The font sprite</param>
	/// <param name="charWidth">character width in pixels</param>
	/// <param name="charHeight">character height in pixels</param>
	/// <param name="columns">number of columns in the font sprite</param>
	void setFont(sf::Sprite& fontSprite, int charWidth, int charHeight, int columns);
	sf::FloatRect getLocalBounds();

	void render(sf::RenderWindow& window);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	float x, y;
	float ox, oy;
	float scale;
	std::string text;
	sf::Color color;
	sf::Sprite* fontSprite;

	int cw, ch, cols; // character width, height & number of columns in the font sprite
};
