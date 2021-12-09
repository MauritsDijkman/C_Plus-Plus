#include "button.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>

Button::Button(std::string identifier, sf::Font& font, std::string buttonText, sf::Vector2f size, bool hover, sf::Color normalColor, sf::Color hoverColor) :
	GameObject(identifier), font(font), buttonText(buttonText)
{
	this->shape.setSize(size);
	this->shape.setFillColor(normalColor);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(1);

	this->text.setString(buttonText);
	this->text.setCharacterSize(26);
	this->text.setFillColor(sf::Color::White);

	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	this->setPosition(sf::Vector2f(0.0f, 0.0f));

	// Sets the hover and color to the provided values
	wantHover = hover;
	colorNormal = normalColor;
	colorHover = hoverColor;
}

// Deletes everything after code has been runned
Button::~Button() { }

// Handles the button click and button hover
void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f size = shape.getSize();
		sf::Vector2f position = shape.getPosition();

		if (mousePosition.x >= position.x && mousePosition.x <= position.x + size.x &&
			mousePosition.y >= position.y && mousePosition.y <= position.y + size.y) {
			this->onClick();
		}
	}
	else {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f size = shape.getSize();
		sf::Vector2f position = shape.getPosition();

		if (mousePosition.x >= position.x && mousePosition.x <= position.x + size.x &&
			mousePosition.y >= position.y && mousePosition.y <= position.y + size.y) {
			this->onHover();
		}
		// Checks if the mouse is not hovering over the button anymore
		else if (isHovering && wantHover) {
			isHovering = false;
			setButtonColor(colorNormal);
		}
	}
}

void Button::update() { }

// Renders the window with the button
void Button::render(sf::RenderWindow& window) {
	window.draw(this->shape);
	window.draw(this->text);
}

// Sets the character size of the text in the button
void Button::setCharacterSize(const int size) {
	this->text.setCharacterSize(size);
}

// Sets the position of the button
void Button::setPosition(const sf::Vector2f position) {
	this->shape.setPosition(position);
	sf::Vector2f size = this->shape.getSize();
	sf::Vector2f centerButton(position.x + (size.x / 2.0f), position.y + (size.y / 2.0f));
	this->text.setPosition(centerButton.x, centerButton.y);
}

// Handles the on click event
void Button::onClick() {
	this->action();
}

// Changes the color when the onHover is called
void Button::onHover() {
	if (wantHover) {
		isHovering = true;
		setButtonColor(colorHover);
	}
}

// Sets the button action
void Button::setButtonAction(std::function<void()> action) {
	this->action = action;
}

// Sets the button color
void Button::setButtonColor(sf::Color color) {
	this->shape.setFillColor(color);
}
