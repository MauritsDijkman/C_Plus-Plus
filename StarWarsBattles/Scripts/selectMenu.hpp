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

class SelectMenu {
public:
	Scene scene = Scene("SelectMenu_Scene");

private:
	Character character1 = Character("character1", "Character1", 0, 0, 0);
	Character character2 = Character("character2", "Character2", 0, 0, 0);
	Character character3 = Character("character3", "Character3", 0, 0, 0);

public:
	SpriteObject character1Sprite = SpriteObject("character1_Sprite", "Assets/PlayerCharacters/Character1.png");
	TextObject character1Name = TextObject("character1_Name", font, "Name");
	TextObject character1HP = TextObject("character1_HP", font, "HP: ...");
	TextObject character1Attack = TextObject("character1_Attack", font, "Strength: ...");
	TextObject character1Defense = TextObject("character1_Defense", font, "Defense: ...");

	SpriteObject character2Sprite = SpriteObject("character2_Sprite", "Assets/PlayerCharacters/Character2.png");
	TextObject character2Name = TextObject("character2_Name", font, "Name");
	TextObject character2HP = TextObject("character2_HP", font, "HP: ...");
	TextObject character2Attack = TextObject("character2_Attack", font, "Strength: ...");
	TextObject character2Defense = TextObject("character2_Defense", font, "Defense: ...");

	SpriteObject character3Sprite = SpriteObject("character3_Sprite", "Assets/PlayerCharacters/Character3.png");
	TextObject character3Name = TextObject("character3_Name", font, "Name");
	TextObject character3HP = TextObject("character3_HP", font, "HP: ...");
	TextObject character3Attack = TextObject("character3_Attack", font, "Strength: ...");
	TextObject character3Defense = TextObject("character3_Defense", font, "Defense: ...");

private:
	sf::Font font;
	sf::Color blackColor = sf::Color(0, 0, 0, 255);
	sf::Color whiteColor = sf::Color(255, 255, 255, 255);
	sf::Color orangeColor = sf::Color(255, 165, 0, 255);
	sf::Color highlightColor = sf::Color(255, 165, 0, 150);
	sf::Color invisibleColor = sf::Color(0, 0, 0, 0);

private:
	Button backButton = Button("backButton", font, "BACK", sf::Vector2f(288.0f, 62.0f), true, blackColor, orangeColor);
	Button character1Button = Button("character1Button", font, "", sf::Vector2f(328.98f, 436.01f), true, invisibleColor, highlightColor);
	Button character2Button = Button("character2Button", font, "", sf::Vector2f(328.98f, 436.01f), true, invisibleColor, highlightColor);
	Button character3Button = Button("character3Button", font, "", sf::Vector2f(328.98f, 436.01f), true, invisibleColor, highlightColor);

public:
	SelectMenu(SceneHandler& sceneHandler, SpriteObject& spriteObject);
	~SelectMenu();

	void SetupScene(SpriteObject& background);

	void Setup_BackButton(SceneHandler& sceneHandler, Scene& previousScene, sf::Sound& backSound);
	void Setup_Character1Button(Character& player, SceneHandler& handler, Scene& nextScene, sf::Sound& selectSound, sf::Music& menuMusic, sf::Music& fightMusic);
	void Setup_Character2Button(Character& player, SceneHandler& handler, Scene& nextScene, sf::Sound& selectSound, sf::Music& menuMusic, sf::Music& fightMusic);
	void Setup_Character3Button(Character& player, SceneHandler& handler, Scene& nextScene, sf::Sound& selectSound, sf::Music& menuMusic, sf::Music& fightMusic);

private:
	void PlaceCharacterStats(TextObject& characterName, sf::Vector2f namePosition, sf::Color nameColor, int nameSize, SpriteObject& characterSprite, sf::Vector2f spritePosition, TextObject& characterHP, sf::Vector2f HPPosition, sf::Color HPColor, int HPSize, TextObject& characterAttack, sf::Vector2f attackPosition, sf::Color attackColor, int attackSize, TextObject& characterDefense, sf::Vector2f defensePosition, sf::Color defenseColor, int defenseSize);
	void LoadCharacterStats(std::string& file, Character& character, TextObject& characterName, TextObject& characterHP, TextObject& characterAttack, TextObject& characterDefense);
};
