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

class FightMenu {

public:
	Scene scene = Scene("FightMenu_Scene");

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
	Button attackButton = Button("attackButton", font, "Attack", sf::Vector2f(205.0f, 69.66f), true, blackColor, orangeColor);
	Button healButton = Button("healButton", font, "Heal", sf::Vector2f(205.0f, 69.66f), true, blackColor, orangeColor);
	Button proceedButton = Button("ProceedButton", font, "Proceed", sf::Vector2f(205.0f, 70.0f), true, blackColor, orangeColor);
	Button backButton = Button("backButton", font, "BACK", sf::Vector2f(288.0f, 62.0f), true, blackColor, orangeColor);

	TextObject descriptionText = TextObject("DescriptionText", font, "You attacked the enemy and did 3 damage.");
	TextObject specialDescriptionText = TextObject("specialDescriptionText", font, "...");

private:
	//Character player = Character("Player", "playerSprite", 0, 0, 0);

	TextObject playerName = TextObject("playerName", font, "Name");
	TextObject playerHP = TextObject("playerHP", font, "HP");
	TextObject playerAttack = TextObject("playerAttack", font, "Attack");
	TextObject playerDefense = TextObject("playerDefense", font, "Defense");

	SpriteObject player1Sprite = SpriteObject("player1Sprite", "Assets/PlayerCharacters/Character1.png");
	SpriteObject player2Sprite = SpriteObject("player2Sprite", "Assets/PlayerCharacters/Character2.png");
	SpriteObject player3Sprite = SpriteObject("player3Sprite", "Assets/PlayerCharacters/Character3.png");

	SpriteObject playerSprites[3] = { player1Sprite, player2Sprite, player3Sprite };

private:
	TextObject enemyName = TextObject("enemyName", font, "Name");
	TextObject enemyHP = TextObject("enemyHP", font, "HP: ...");
	TextObject enemyAttack = TextObject("enemyAttack", font, "Attack: ...");
	TextObject enemyDefense = TextObject("enemyDefense", font, "Defense: ...");

	Character enemy1 = Character("Darth Vader", "Assets/EnemyCharacters/Enemy1.png", 20, 13, 13);
	Character enemy2 = Character("Darth Sidious", "Assets/EnemyCharacters/Enemy2.png", 18, 15, 14);
	Character enemy3 = Character("Stormtrooper", "Assets/EnemyCharacters/Enemy3.png", 17, 10, 10);
	Character enemy4 = Character("Boba Fett", "Assets/EnemyCharacters/Enemy4.png", 19, 13, 13);
	Character enemy5 = Character("Tusken Raider", "Assets/EnemyCharacters/Enemy5.png", 17, 11, 10);
	Character enemy6 = Character("Moff Tarkin", "Assets/EnemyCharacters/Enemy6.png", 17, 10, 15);
	Character enemy7 = Character("Bossk", "Assets/EnemyCharacters/Enemy7.png", 19, 13, 10);
	Character enemy8 = Character("Red Guard", "Assets/EnemyCharacters/Enemy8.png", 18, 13, 13);
	Character enemy9 = Character("IG-88B", "Assets/EnemyCharacters/Enemy9.png", 18, 11, 15);
	Character enemy10 = Character("Scout Trooper", "Assets/EnemyCharacters/Enemy10.png", 17, 10, 11);

	Character enemyCharacters[10] = { enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7, enemy8, enemy9, enemy10 };

	SpriteObject enemy1Sprite = SpriteObject("Enemy1Sprite", enemy1.getSpriteFile());
	SpriteObject enemy2Sprite = SpriteObject("Enemy2Sprite", enemy2.getSpriteFile());
	SpriteObject enemy3Sprite = SpriteObject("Enemy3Sprite", enemy3.getSpriteFile());
	SpriteObject enemy4Sprite = SpriteObject("Enemy4Sprite", enemy4.getSpriteFile());
	SpriteObject enemy5Sprite = SpriteObject("Enemy5Sprite", enemy5.getSpriteFile());
	SpriteObject enemy6Sprite = SpriteObject("Enemy6Sprite", enemy6.getSpriteFile());
	SpriteObject enemy7Sprite = SpriteObject("Enemy7Sprite", enemy7.getSpriteFile());
	SpriteObject enemy8Sprite = SpriteObject("Enemy8Sprite", enemy8.getSpriteFile());
	SpriteObject enemy9Sprite = SpriteObject("Enemy9Sprite", enemy9.getSpriteFile());
	SpriteObject enemy10Sprite = SpriteObject("Enemy10Sprite", enemy10.getSpriteFile());

	SpriteObject enemySprites[10] = { enemy1Sprite, enemy2Sprite, enemy3Sprite, enemy4Sprite, enemy5Sprite, enemy6Sprite, enemy7Sprite, enemy8Sprite, enemy9Sprite, enemy10Sprite };

public:
	FightMenu(SceneHandler& sceneHandler, SpriteObject& spriteObject, Character& player);
	~FightMenu();

	void SetupScene(SceneHandler& sceneHandler, SpriteObject& background, Character& player);
	void Setup_AttackButton(sf::Music& fightMusic, Character& player);
	void Setup_HealButton(sf::Sound& healSound, Character& player);
	void Setup_ProceedButton(bool& youngling, bool& apprentice, bool& master, sf::Music& fightMusic, Character& player);
	void Setup_BackButton(SceneHandler& sceneHandler, Scene& previousScene, sf::Sound& backSound, sf::Music& menuMusic, sf::Music& fightMusic, Character& player);

private:
	bool playerTurn = true;
	int score = 0;
	int enemySelected = 0;
	std::string attackWho = " ";
	std::string healWho = " ";

	std::string previousEnemy = " ";

	int damageDone = 0;
	int healDone = 0;

	sf::SoundBuffer victoryBuffer;
	sf::Sound victorySound;

	sf::SoundBuffer gameoverBuffer;
	sf::Sound gameoverSound;

	sf::SoundBuffer attackBuffer;
	sf::Sound attackSound;

	sf::SoundBuffer healBuffer;
	sf::Sound healSound;

	sf::SoundBuffer donothingBuffer;
	sf::Sound donothingSound;

private:
	void SetValuesFightScene(Scene& fightScene, bool& playerTurn, int& score, Button& proceedButton, Button& attackButton, Button& healButton, TextObject& specialDescriptionText);
	void SetPlayer(Character& player, TextObject& playerName, TextObject& playerHP, TextObject& playerAttack, TextObject& playerDefense, SpriteObject playerSprites[]);
	void GenerateRandomEnemy(int& enemySelected, Character enemyCharacters[], SpriteObject enemySprites[], TextObject& enemyName, TextObject& enemyHP, TextObject& enemyAttack, TextObject& enemyDefense, TextObject& descriptionText, std::string previousEnemy);
	void Attack(std::string attackWho, Character& player, Character enemyCharacters[], int enemySelected, int& damageDone, TextObject& playerHP, TextObject& enemyHP, TextObject& descriptionText, TextObject& specialDescription, bool& playerTurn, int score, sf::Sound& victorySound, sf::Sound& gameoverSound, sf::Sound& attackSound, sf::Music& fightMusic);
	void Heal(std::string healWho, Character& player, Character enemyCharacters[], int enemySelected, int& healDone, TextObject& playerHP, TextObject& enemyHP, TextObject& descriptionText, bool& playerTurn, sf::Sound& healSound);
	void DoNothing(TextObject& descriptionText, Character enemyCharacters[], int enemySelected, bool& playerTurn, sf::Sound& donothingSound);
	void EnemyTurn(bool youngling, bool apprentice, bool master, sf::Music& fightMusic, Character& player);
	void UpdateDescription(std::string attackedWho, std::string healedWho);
	void RemoveImages(Character& player, SpriteObject playerSprites[], SpriteObject enemySprites[], int enemySelected);

	void SortScore(std::string highscoreFile);
	void UpdateScore(std::string highscoreFile);
};
