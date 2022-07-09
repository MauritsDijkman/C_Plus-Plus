#include "spriteObject.hpp"

SpriteObject::SpriteObject(std::string identifier, std::string spriteFile) :
	GameObject(identifier), spriteFile(spriteFile)
{
	this->texture.loadFromFile(this->spriteFile); // Loads the given string path file to a texture
	this->sprite.setTexture(this->texture); // Adds the texture to a sprite
}

// Copies the values from the other spriteobject
SpriteObject::SpriteObject(const SpriteObject& other) :
	GameObject(other.getIdentifier()), spriteFile(other.getSpriteFile())
{
	this->texture.loadFromFile(this->spriteFile);
	this->sprite.setTexture(this->texture);
}

// Deletes everything after code has been runned
SpriteObject::~SpriteObject() { }

// Updates the sprite
void SpriteObject::update() {}

// Renders the spriteobject in window
void SpriteObject::render(sf::RenderWindow& window) {
	window.draw(this->sprite);
}

// Sets the position of the sprite to the given position
void SpriteObject::setPosition(sf::Vector2f position) {
	sprite.setPosition(position);
}

// Scales the sprite to the given scale
void SpriteObject::setScale(sf::Vector2f scale) {
	sprite.setScale(scale);
}

// Returns an string with the sprite file
std::string SpriteObject::getSpriteFile() const {
	return this->spriteFile;
}
