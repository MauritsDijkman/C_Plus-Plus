#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

#include "gameObject.hpp"

class Scene {
private: // Values used for the parent function
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
private:
	const std::string identifier; // Not changable
	std::vector<GameObject*> listOfGameObjects;
protected: // Can only be used in subclases
	sf::Vector2f position;
public: // Can be changed 
	Scene(std::string identifier);
	~Scene();
public: // Can be called
	void addGameObject(GameObject& object);
	void removeGameObject(std::string objectIdentifier);
	void handleEvent(const sf::Event& event, sf::RenderWindow& window);
	void update();
	void render(sf::RenderWindow& window);

	std::string getIdentifier() const;
};
