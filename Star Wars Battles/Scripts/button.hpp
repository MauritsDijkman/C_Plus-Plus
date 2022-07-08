#pragma once

#include "gameObject.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "scene.hpp"
#include <functional> 
#include "bitmapText.hpp"

class Button : public GameObject {

	// Values that cannot be changed when creating a button
private:
	bitmapText text;
	sf::Font& font;
	sf::RectangleShape shape;
	std::string buttonText;
	// Bools used for changing the color with hover
	bool isHovering;
	bool wantHover;
	// Colors used for changing the button color with hover
	sf::Color colorNormal;
	sf::Color colorHover;

	std::function<void()> action;
	// Values that can be called when creating a button
public:
	Button(std::string identifier, sf::Font& font, std::string buttonText,
		sf::Vector2f size, bool hover, sf::Color normalColor, sf::Color hoverColor);
	~Button();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	virtual void onClick();
	virtual void onHover();

	void update() override;
	void render(sf::RenderWindow& window) override;
	void setButtonAction(std::function<void()> action);
	void setCharacterSize(const int size);
	void setPosition(const sf::Vector2f position);
	void setButtonColor(sf::Color color);
};
