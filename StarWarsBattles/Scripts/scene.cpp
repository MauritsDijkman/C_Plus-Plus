#include "scene.hpp"

Scene::Scene(std::string identifier) : identifier(identifier) { }

// Deletes everything after code has been runned
Scene::~Scene() { }

void Scene::addGameObject(GameObject& object) {
	this->listOfGameObjects.push_back(&object);
}

// Handles the events in all the gameobjects in the list of the scene
void Scene::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
		this->listOfGameObjects[i]->handleEvent(event, window);
	}
}

// Updates all the gameobjects in the list of the scene
void Scene::update() {
	for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
		this->listOfGameObjects[i]->update();
	}
}

// Renders all the gameobjects in the list of the scene
void Scene::render(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
		this->listOfGameObjects[i]->render(window);
	}
}

// Returns a string with the name of the scene
std::string Scene::getIdentifier() const {
	return this->identifier;
}

// Removes the given gameobject from the scene
void Scene::removeGameObject(std::string childIdentifier) {
	// Sets the child index to -1, to make sure that it's not a value that matches with the for loop i
	int childIndex = -1;

	// Checks for every gameobject in the list if it's the same as the given one
	for (unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
		if (this->listOfGameObjects[i]->getIdentifier().compare(childIdentifier) == 0) {
			childIndex = i;
			break;
		}
	}
	// Checks if the index is not still -1 and that it has been changed in the previous for loop.
	// If the value is changed, erase the gameobject and unparent it from the scene
	if (childIndex != -1) {
		GameObject* child = this->listOfGameObjects[childIndex];
		this->listOfGameObjects.erase(this->listOfGameObjects.begin() + childIndex);
		child->unparent();
	}
}
