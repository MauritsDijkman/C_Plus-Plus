#pragma once

#include "gameObject.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SpriteObject : public GameObject {
private: // Cannot be called
	std::string spriteFile;
	sf::Sprite sprite;
	sf::Texture texture;
public: // Can be called to create a spriteobject
	SpriteObject(std::string identifier, std::string spriteFile);
	SpriteObject(const SpriteObject& other);
	~SpriteObject();

public: // Can be called to change some values from the spriteobject or get information from the spriteobject
	void update() override;
	void render(sf::RenderWindow& window) override;

	void setPosition(sf::Vector2f position);
	void setScale(sf::Vector2f scale);
	std::string getSpriteFile() const;
};
