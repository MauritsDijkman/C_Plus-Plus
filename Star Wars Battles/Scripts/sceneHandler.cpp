#include "sceneHandler.hpp"

SceneHandler::SceneHandler() { }

// Deletes everything after code has been runned
SceneHandler::~SceneHandler() { }

// Renders the scene that is on top of the stacklist
void SceneHandler::render(sf::RenderWindow& window) const {
	if (this->scenesStack.size() != 0) {
		this->scenesStack.top()->render(window);
	}
}

// Updates the scene that is on top of the stacklist
void SceneHandler::update() {
	if (this->scenesStack.size() != 0) {
		this->scenesStack.top()->update();
	}
}

// Adds the given scene to the scenehandler and ads it to the stackScene list
void SceneHandler::addScene(Scene& scene) {
	this->scenes.emplace(scene.getIdentifier(), &scene);
	if (this->scenes.size() == 1) {
		this->stackScene(scene.getIdentifier());
	}
}

// Adds the given scene to the ScenesStack list (list of added scenes)
void SceneHandler::stackScene(std::string sceneName) {
	this->scenesStack.push(scenes[sceneName]);
}

// Removes the given scene from the top of the scenesStack list
void SceneHandler::popScene(void) {
	this->scenesStack.pop();
}

std::string SceneHandler::GetCurrentScene()
{
	return std::string(this->scenesStack.top()->getIdentifier());
}
