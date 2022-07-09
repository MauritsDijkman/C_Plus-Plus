#pragma once

#include "selectMenu.hpp"
#include <fstream>
#include <stdio.h>
#include <vector>

SelectMenu::SelectMenu(SceneHandler& handler, SpriteObject& background)
{
	handler.addScene(this->scene);
	SetupScene(background);
}

SelectMenu::~SelectMenu() {}

void SelectMenu::SetupScene(SpriteObject& background) {
	// Positions
	background.setPosition(sf::Vector2f(0.0f, 0.0f));

	backButton.setPosition(sf::Vector2f(951.25f, 620.94f));

	character1Button.setPosition(sf::Vector2f(35.25f, 142.0f));
	character2Button.setPosition(sf::Vector2f(475.09f, 142.0f));
	character3Button.setPosition(sf::Vector2f(909.5f, 142.0f));

	// Setting the player stats with a function
	PlaceCharacterStats(character1Name, sf::Vector2f(150.0f, 167.89f), whiteColor, 18, character1Sprite, sf::Vector2f(109.22f, 221.25f), character1HP, sf::Vector2f(120.0f, 449.57f), whiteColor, 18, character1Attack, sf::Vector2f(120.0f, 469.57f), whiteColor, 18, character1Defense, sf::Vector2f(120.0f, 489.57f), whiteColor, 18);
	PlaceCharacterStats(character2Name, sf::Vector2f(545.0f, 167.89f), whiteColor, 18, character2Sprite, sf::Vector2f(549.22f, 221.25f), character2HP, sf::Vector2f(570.0f, 449.57f), whiteColor, 18, character2Attack, sf::Vector2f(570.0f, 469.57f), whiteColor, 18, character2Defense, sf::Vector2f(570.0f, 489.57f), whiteColor, 18);
	PlaceCharacterStats(character3Name, sf::Vector2f(1040.0f, 167.89f), whiteColor, 18, character3Sprite, sf::Vector2f(989.22f, 221.25f), character3HP, sf::Vector2f(1010.0f, 449.57f), whiteColor, 18, character3Attack, sf::Vector2f(1010.0f, 469.57f), whiteColor, 18, character3Defense, sf::Vector2f(1010.0f, 489.57f), whiteColor, 18);

	// Adding
	scene.addGameObject(background);
	scene.addGameObject(backButton);
	scene.addGameObject(character1Button);
	scene.addGameObject(character2Button);
	scene.addGameObject(character3Button);

	scene.addGameObject(character1Name);
	scene.addGameObject(character1Sprite);
	scene.addGameObject(character1HP);
	scene.addGameObject(character1Attack);
	scene.addGameObject(character1Defense);

	scene.addGameObject(character2Name);
	scene.addGameObject(character2Sprite);
	scene.addGameObject(character2HP);
	scene.addGameObject(character2Attack);
	scene.addGameObject(character2Defense);

	scene.addGameObject(character3Name);
	scene.addGameObject(character3Sprite);
	scene.addGameObject(character3HP);
	scene.addGameObject(character3Attack);
	scene.addGameObject(character3Defense);

	// Importing stats
	std::string fileCharacter1 = "Assets/PlayerCharacters/Character1.txt";
	std::string fileCharacter2 = "Assets/PlayerCharacters/Character2.txt";
	std::string fileCharacter3 = "Assets/PlayerCharacters/Character3.txt";

	// Loading stats
	LoadCharacterStats(fileCharacter1, character1, character1Name, character1HP, character1Attack, character1Defense);
	LoadCharacterStats(fileCharacter2, character2, character2Name, character2HP, character2Attack, character2Defense);
	LoadCharacterStats(fileCharacter3, character3, character3Name, character3HP, character3Attack, character3Defense);
}

void SelectMenu::Setup_BackButton(SceneHandler& sceneHandler, Scene& previousScene, sf::Sound& backSound) {
	backButton.setButtonAction([&sceneHandler, &previousScene, &backSound]() {

		// Play the sound
		backSound.play();

		sceneHandler.addScene(previousScene);						//Add the next scene to the scene handler
		sceneHandler.stackScene(previousScene.getIdentifier());		//Push that new scene to the scene handler	
		});
}

void SelectMenu::Setup_Character1Button(Character& player, SceneHandler& handler, Scene& nextScene, sf::Sound& selectSound, sf::Music& menuMusic, sf::Music& fightMusic) {
	character1Button.setButtonAction([=, &player, &handler, &nextScene, &selectSound, &menuMusic, &fightMusic]() {

		player = character1;	// Setting the player to be the selected character

		selectSound.play();		// Play select sounds
		menuMusic.stop();		// Stop menu music
		fightMusic.play();		// Play fight music

		handler.addScene(nextScene);						//Add the next scene to the scene handler
		handler.stackScene(nextScene.getIdentifier());		//Push that new scene to the scene handler	
		});
}

void SelectMenu::Setup_Character2Button(Character& player, SceneHandler& handler, Scene& nextScene, sf::Sound& selectSound, sf::Music& menuMusic, sf::Music& fightMusic) {
	character2Button.setButtonAction([=, &player, &handler, &nextScene, &selectSound, &menuMusic, &fightMusic]() {

		player = character2;	// Setting the player to be the selected character

		selectSound.play();		// Play select sound
		menuMusic.stop();		// Stop menu music
		fightMusic.play();		// Play fight music

		handler.addScene(nextScene);						//Add the next scene to the scene handler
		handler.stackScene(nextScene.getIdentifier());		//Push that new scene to the scene handler	
		});
}

void SelectMenu::Setup_Character3Button(Character& player, SceneHandler& handler, Scene& nextScene, sf::Sound& selectSound, sf::Music& menuMusic, sf::Music& fightMusic) {
	character3Button.setButtonAction([=, &player, &handler, &nextScene, &selectSound, &menuMusic, &fightMusic]() {

		player = character3;	// Setting the player to be the selected character

		selectSound.play();		// Play the select sound
		menuMusic.stop();		// Stop the menu music
		fightMusic.play();		// Play the fight music

		handler.addScene(nextScene);						//Add the next scene to the scene handler
		handler.stackScene(nextScene.getIdentifier());		//Push that new scene to the scene handler	
		});
}

void SelectMenu::PlaceCharacterStats(TextObject& characterName, sf::Vector2f namePosition, sf::Color nameColor, int nameSize, SpriteObject& characterSprite, sf::Vector2f spritePosition, TextObject& characterHP, sf::Vector2f HPPosition, sf::Color HPColor, int HPSize, TextObject& characterAttack, sf::Vector2f attackPosition, sf::Color attackColor, int attackSize, TextObject& characterDefense, sf::Vector2f defensePosition, sf::Color defenseColor, int defenseSize) {
	// Place the character stats on the given positions

	characterName.setPosition(namePosition);
	characterName.setFillColor(nameColor);
	characterName.setCharacterSize(nameSize);

	characterSprite.setPosition(spritePosition);

	characterHP.setPosition(HPPosition);
	characterHP.setFillColor(HPColor);
	characterHP.setCharacterSize(HPSize);

	characterAttack.setPosition(attackPosition);
	characterAttack.setFillColor(attackColor);
	characterAttack.setCharacterSize(attackSize);

	characterDefense.setPosition(defensePosition);
	characterDefense.setFillColor(defenseColor);
	characterDefense.setCharacterSize(defenseSize);
}

void SelectMenu::LoadCharacterStats(std::string& file, Character& character, TextObject& characterName, TextObject& characterHP, TextObject& characterAttack, TextObject& characterDefense) {
	// Opening the file and setting each line of the text file to the corresponding info of the player

	std::ifstream characterStats(file);

	if (!characterStats.fail()) {
		std::string line;

		std::getline(characterStats, line);
		character.setName(line);
		characterName.setText(line);

		std::getline(characterStats, line);
		character.setHP(std::stoi(line)); // stoi transfers string to int
		character.setmaxHP(std::stoi(line)); // stoi transfers string to int
		characterHP.setText("HP: " + std::to_string(character.getHP()));

		std::getline(characterStats, line);
		character.setAttack(std::stoi(line)); // stoi transfers string to int
		characterAttack.setText("Attack: " + std::to_string(character.getAttack()));

		std::getline(characterStats, line);
		character.setDefense(std::stoi(line)); // stoi transfers string to int
		characterDefense.setText("Defense: " + std::to_string(character.getDefense()));

		characterStats.close();
	}
}
