#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {
private: // Values that are used for parent the gameobject to others
	GameObject* parent = nullptr; // It needs to be a pointer, because pointers can be null (references not)
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
	// The const in front of the event means that the event cannot be changed in the handleEvent function
	virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) { };
	virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	void unparent();
	std::string getIdentifier() const;

	// Const after means that the method cannot modify the value it returns
	sf::Vector2f getWorldPosition() const;
	sf::Vector2f getPosition() const;

	/*
	Const at the back means that the method is a constant which means it can't modify/change anything about the class instance it belongs to.
	So you can't do something like "this->value = something;" inside the method.

	Const in the front means that the value it returns is a constant and can't be changed.
	Saying "value = getWorldPosition();" when the const is at the front means that 'value' needs to be a const variable and it can't be changed afterwards.
	*/
};
