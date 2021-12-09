#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {
private: // Values that are used for parent the gameobject to others
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
protected: // These values are inaccessible outside this class. But they can be accessed by subclasses of the class.
	sf::Vector2f position;
	sf::Vector2f offset;
private:
	const std::string identifier;
public:
	GameObject(std::string identifier);
	GameObject(const GameObject& other);

	virtual ~GameObject();
public:
	virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) { };
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	void unparent();
	std::string getIdentifier() const;

	sf::Vector2f getWorldPosition() const;
	sf::Vector2f getPosition() const;
};
