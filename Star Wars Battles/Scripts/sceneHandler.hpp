#pragma once

#include <map>
#include <stack>
#include "scene.hpp"

class SceneHandler {
private: // Cannot be called in other classes
	std::map<std::string, Scene*> scenes;
	std::stack<Scene*> scenesStack;
public: // Can be called in other classes
	SceneHandler();
	~SceneHandler();
public: // Can be caled in other classes
	void render(sf::RenderWindow& window) const;
	void update();

	void addScene(Scene& scene);
	void stackScene(std::string sceneName);
	void popScene();
	std::string GetCurrentScene();
};
