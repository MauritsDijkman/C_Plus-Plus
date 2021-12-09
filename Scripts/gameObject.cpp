#include "gameObject.hpp"

#include "scene.hpp"

// Sets the identifier to the the given string 
GameObject::GameObject(std::string identifier) : identifier(identifier) { }

// Sets the identifier to the identifier of the the other given gameobject
GameObject::GameObject(const GameObject& other) : identifier(other.getIdentifier()) { }

// Deletes everything after code has been runned
GameObject::~GameObject() { }

// Returns a string with the name of the gameobject
std::string GameObject::getIdentifier() const {
	return this->identifier;
}

// Returns a vector2f with the worldposition of the gameobject. If it's the child of another gameobject, return the correct worldposition according to that gameobject.
sf::Vector2f GameObject::getWorldPosition() const
{
	if (this->parent == nullptr) {
		return getPosition();
	}
	else {
		return(this->parent->getWorldPosition() - this->offset) + this->position;
	}
}

// Returns a vector2f with the position of the gameobject, doesn't check for parent or child
sf::Vector2f GameObject::getPosition() const {
	return this->position;
}

// Unparents the gameobject from his parent
void GameObject::unparent() {
	this->position = this->getWorldPosition();
	this->parent = nullptr;
}
