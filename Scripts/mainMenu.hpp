#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "scene.hpp"
#include "textObject.hpp"
#include "spriteObject.hpp"
#include "character.hpp"
#include "button.hpp"
#include "quitButton.hpp"

#include "sceneHandler.hpp"
#include "spriteObject.hpp"


class MainMenu {
public:
	Scene scene = Scene("MainMenu_Scene");

private:
	sf::Font font;
	sf::Color blackColor = sf::Color(0, 0, 0, 255);
	sf::Color whiteColor = sf::Color(255, 255, 255, 255);
	sf::Color orangeColor = sf::Color(255, 165, 0, 255);
	sf::Color highlightColor = sf::Color(255, 165, 0, 150);
	sf::Color invisibleColor = sf::Color(0, 0, 0, 0);
	sf::Color redColor = sf::Color(180, 0, 0, 255);
	sf::Color greenColor = sf::Color(0, 128, 0, 255);
	sf::Color blueColor = sf::Color(0, 0, 205, 255);

private:
	Button playButton = Button("playButton", font, "PLAY", sf::Vector2f(154.0f, 69.0f), true, blackColor, orangeColor);
	Button eraseButton = Button("eraseButton", font, "ERASE GAME DATA", sf::Vector2f(387.48f, 69.0f), true, blackColor, orangeColor);
	Button quitButton = Button("quitButton", font, "QUIT", sf::Vector2f(154.0f, 69.0f), true, blackColor, orangeColor);

private:
	//TextObject highscoreText1 = TextObject("highscoreText1", font, "Highscore 1: ...");
	//TextObject highscoreText2 = TextObject("highscoreText2", font, "Highscore 2: ...");
	//TextObject highscoreText3 = TextObject("highscoreText3", font, "Highscore 3: ...");
	//TextObject highscoreText4 = TextObject("highscoreText4", font, "Highscore 4: ...");
	//TextObject highscoreText5 = TextObject("highscoreText5", font, "Highscore 5: ...");

private:
	Button younglingButton = Button("YounglingButton", font, "Youngling", sf::Vector2f(208.94f, 37.4f), false, blackColor, orangeColor);
	Button apprenticeButton = Button("ApprenticeButton", font, "Apprentice", sf::Vector2f(208.94f, 37.4f), false, blackColor, orangeColor);
	Button masterButton = Button("MasterButton", font, "Master", sf::Vector2f(208.94f, 37.4f), false, blackColor, orangeColor);

private:
	void CheckForFile(std::string highscoreFile);

public:
	MainMenu(SceneHandler& sceneHandler, SpriteObject& spriteObject, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5);
	~MainMenu();

	void SetupScene(SceneHandler& sceneHandler, SpriteObject& spriteObject, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5);

	void Setup_PlayButton(SceneHandler& handler, Scene& scene, sf::Sound& sound);
	void Setup_EraseButton(sf::Sound& sound, std::string& file);
	void Setup_QuitButton(sf::RenderWindow& window, sf::Sound& sound);
	void SortScore(std::string highscoreFile);
	void UpdateScore(std::string highscoreFile);
	void Setup_YounglingButton(bool& youngling, bool& apprentice, bool& master, sf::Sound& sound);
	void Setup_ApprenticeButton(bool& youngling, bool& apprentice, bool& master, sf::Sound& sound);
	void Setup_MasterButton(bool& youngling, bool& apprentice, bool& master, sf::Sound& sound);
};
