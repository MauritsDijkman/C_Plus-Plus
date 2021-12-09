#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fstream>
#include <iostream> 

// Extra STL structures
#include <vector> 
#include <iterator> 

#include "scene.hpp"
#include "textObject.hpp"
#include "spriteObject.hpp"
#include "character.hpp"
#include "button.hpp"
#include "quitButton.hpp"
#include "sceneHandler.hpp"
#include "soundHandler.hpp"
#include "mainMenu.hpp"
#include "selectMenu.hpp"
#include "fightMenu.hpp"

using namespace std;

// Voids that are being used in the game
void UpdateScore(TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5, string highscoreFile);
void SetPlayer(Character character, Character& player, TextObject& playerName, TextObject& playerHP, TextObject& playerAttack, TextObject& playerDefense, int characterSelected, SpriteObject playerSprites[], Scene& fightScene);
void LoadCharacterStats(std::ifstream& characterStats, Character& character, TextObject& characterName, TextObject& characterHP, TextObject& characterAttack, TextObject& characterDefense);
void PlaceCharacterStats(TextObject& characterName, sf::Vector2f namePosition, sf::Color nameColor, int nameSize, SpriteObject& characterSprite, sf::Vector2f spritePosition, TextObject& characterHP, sf::Vector2f HPPosition, sf::Color HPColor, int HPSize, TextObject& characterAttack, sf::Vector2f attackPosition, sf::Color attackColor, int attackSize, TextObject& characterDefense, sf::Vector2f defensePosition, sf::Color defenseColor, int defenseSize);
void GenerateRandomEnemy(int& randomNumber, Character enemies[], SpriteObject enemySprites[], TextObject& enemyName, TextObject& enemyHP, TextObject& enemyAttack, TextObject& enemyDefense, Scene& fightScene, TextObject& descriptionText, string previousEnemy);
void RemoveImages(Scene& fightScene, Character& player, SpriteObject playerSprites[], SpriteObject enemySprites[], int enemySelected);
void Attack(string attackWho, Character& player, Character enemyCharacters[], int enemySelected, int& damageDone, TextObject& playerHP, TextObject& enemyHP, TextObject& descriptionText, TextObject& specialDescription, bool& playerTurn, int score, sf::Sound& victorySound, sf::Sound& gameoverSound, sf::Sound& attackSound, sf::Music& fightMusic);
void Heal(string healWho, Character& player, Character enemyCharacters[], int enemySelected, int& healDone, TextObject& playerHP, TextObject& enemyHP, TextObject& descriptionText, bool& playerTurn, sf::Sound& healSound);
void UpdateDescription(string attackedWho, string healedWho, TextObject& descriptionText, Character player, Character enemyCharacters[], int enemySelected, int damageDone, int healDone);
void EnemyTurn(Character& player, Character enemyCharacters[], int enemySelected, int& healDone, int& damageDone, TextObject& playerHP, TextObject& enemyHP, TextObject& descriptionText, TextObject& specialDescriptionText, bool& playerTurn, int score, bool youngling, bool apprentice, bool master, sf::Sound& victorySound, sf::Sound& gameoverSound, sf::Sound& attackSound, sf::Sound& healSound, SoundHandler& donothingSound, sf::Music& fightMusic);
void DoNothing(TextObject& descriptionText, Character enemyCharacters[], int enemySelected, bool& playerTurn, SoundHandler& donothingSound);
void SortScore(std::ifstream& highscoreStats, std::vector<int>& vectorScore, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5, string highscoreFile);
void SetValuesFightScene(Scene& fightScene, bool& playerTurn, int& score, Button& proceedButton, Button& attackButton, Button& healButton, TextObject& specialDescriptionText);

// Some (font) colors that are used. They are placed here so that they can be used everywhere
sf::Color blackColor = sf::Color(0, 0, 0, 255);
sf::Color whiteColor = sf::Color(255, 255, 255, 255);
sf::Color orangeColor = sf::Color(255, 165, 0, 255);
sf::Color highlightColor = sf::Color(255, 165, 0, 150);
sf::Color invisibleColor = sf::Color(0, 0, 0, 0);
sf::Color redColor = sf::Color(180, 0, 0, 255);
sf::Color greenColor = sf::Color(0, 128, 0, 255);
sf::Color blueColor = sf::Color(0, 0, 205, 255);

SceneHandler handler = SceneHandler();

Character player = Character("Player", "playerSprite", 0, 0, 0);
string previousEnemy = " ";

// Font that is not used but is needed for the buttons and text
sf::Font font;

TextObject highscoreText1 = TextObject("highscoreText1", font, "Highscore 1: ...");
TextObject highscoreText2 = TextObject("highscoreText2", font, "Highscore 2: ...");
TextObject highscoreText3 = TextObject("highscoreText3", font, "Highscore 3: ...");
TextObject highscoreText4 = TextObject("highscoreText4", font, "Highscore 4: ...");
TextObject highscoreText5 = TextObject("highscoreText5", font, "Highscore 5: ...");

SpriteObject backgroundMainMenu("backgroundMainMenu", "Assets/Backgrounds/Background_MainMenu.png");
SpriteObject backgroundSelectMenu("backgrounSelectMenu", "Assets/Backgrounds/Background_SelectMenu.png");
SpriteObject backgroundFightMenu("backgroundFightMenu", "Assets/Backgrounds/Background_FightScene.png");

MainMenu mainMenu(handler, backgroundMainMenu, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
SelectMenu selectMenu(handler, backgroundSelectMenu);
FightMenu fightMenu(handler, backgroundFightMenu, player);

int main()
{
	// Initialize a random seed for the random function
	srand(time(NULL));

	// Values that used for changing the scenes
	//int sceneCounter = 0;
	//bool sceneChanged = false;

	// Values used for the dificulty setting
	bool youngling = false;
	bool apprentice = true;
	bool master = false;

	//// Values for the selected enemy and the score of the player
	int enemySelected = 0;
	//int score = 0;

	// A vector that is used for importing the score from a file and sort it
	// A vector is used to make it simpler to add a number to that array (a normal arrray of integers is not that easy)
	//std::vector<int> vectorScore;

	// Renders a window with the given measurements and the name of the windows
	sf::RenderWindow window(sf::VideoMode(1280, 720), "C++ Game - Maurits Dijkman - 495475 - ECM2V.Ea");


	// A string with the path of the highscore that is used for searching the highscore file
	std::string highscoreFile = "Assets/Input_Output_Files/highscores.cmgt";


#pragma region Music and sounds

	//Creating sound effect
	sf::SoundBuffer selectBuffer;
	selectBuffer.loadFromFile("Assets/Music_Sounds/SelectSound.ogg");
	sf::Sound selectSound;
	selectSound.setBuffer(selectBuffer);

	sf::SoundBuffer backBuffer;
	backBuffer.loadFromFile("Assets/Music_Sounds/BackSound.ogg");
	sf::Sound backSound;
	backSound.setBuffer(backBuffer);

	sf::SoundBuffer victoryBuffer;
	victoryBuffer.loadFromFile("Assets/Music_Sounds/VictorySound.ogg");
	sf::Sound victorySound;
	victorySound.setBuffer(victoryBuffer);

	sf::SoundBuffer gameoverBuffer;
	gameoverBuffer.loadFromFile("Assets/Music_Sounds/GameOverSound.ogg");
	sf::Sound gameoverSound;
	gameoverSound.setBuffer(gameoverBuffer);

	sf::SoundBuffer attackBuffer;
	attackBuffer.loadFromFile("Assets/Music_Sounds/AttackSound.ogg");
	sf::Sound attackSound;
	attackSound.setBuffer(attackBuffer);

	sf::SoundBuffer healBuffer;
	healBuffer.loadFromFile("Assets/Music_Sounds/HealSound.ogg");
	sf::Sound healSound;
	healSound.setBuffer(healBuffer);

	// New way of using sound with special cpp and hpp classes
	sf::SoundBuffer donothingBuffer;
	sf::Sound donothingSound;
	SoundHandler doNothingSoundHandler("DoNothingSound", donothingBuffer, "Assets/Music_Sounds/DoNothingSound.ogg", donothingSound);

	// Creating music 
	sf::Music menuMusic;
	menuMusic.openFromFile("Assets/Music_Sounds/MenuMusic.ogg");
	menuMusic.setLoop(true);
	menuMusic.play();

	sf::Music fightMusic;
	fightMusic.openFromFile("Assets/Music_Sounds/FightMusic.ogg");
	fightMusic.setLoop(true);

#pragma endregion


#pragma region Creating and setting up the scenes



	mainMenu.Setup_PlayButton(handler, selectMenu.scene, selectSound);
	mainMenu.Setup_EraseButton(selectSound, highscoreFile, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
	mainMenu.Setup_QuitButton(window, selectSound);
	mainMenu.Setup_YounglingButton(youngling, apprentice, master, selectSound);
	mainMenu.Setup_ApprenticeButton(youngling, apprentice, master, selectSound);
	mainMenu.Setup_MasterButton(youngling, apprentice, master, selectSound);

	selectMenu.Setup_BackButton(handler, mainMenu.scene, backSound);
	selectMenu.Setup_Character1Button(player, handler, fightMenu.scene, selectSound, menuMusic, fightMusic);
	selectMenu.Setup_Character2Button(player, handler, fightMenu.scene, selectSound, menuMusic, fightMusic);
	selectMenu.Setup_Character3Button(player, handler, fightMenu.scene, selectSound, menuMusic, fightMusic);

	fightMenu.Setup_AttackButton(fightMusic, player);
	fightMenu.Setup_HealButton(healSound, player);
	fightMenu.Setup_ProceedButton(youngling, apprentice, master, fightMusic, player);
	fightMenu.Setup_BackButton(handler, selectMenu.scene, backSound, menuMusic, fightMusic, player);


	//fightMenu.Setup_AttackButton(victorySound, gameoverSound, attackSound, fightMusic);
	//fightMenu.Setup_HealButton(healSound);


#pragma endregion


#pragma region OldCode


#pragma region Setting up the backgrounds of the scenes

	//Creating the scenes here for so I can use them later in the code
	//Scene mainMenu("mainMenu");
	/*Scene selectMenu("selectMenu");
	Scene fightScene("fightScene");*/

	////Setting up the backgrounds so that they are always behind everything
	//SpriteObject backgroundMainMenu("backgroundMainMenu", "Assets/Backgrounds/Background_MainMenu.png");
	//backgroundMainMenu.setPosition(sf::Vector2f(0.0f, 0.0f));
	//mainMenu.addGameObject(backgroundMainMenu);

	//SpriteObject backgroundSelectMenu("backgrounSelectMenu", "Assets/Backgrounds/Background_SelectMenu.png");
	//backgroundSelectMenu.setPosition(sf::Vector2f(0.0f, 0.0f));
	//selectMenu.addGameObject(backgroundSelectMenu);

	/*SpriteObject backgroundFightScene("backgroundFightScene", "Assets/Backgrounds/Background_FightScene.png");
	backgroundFightScene.setPosition(sf::Vector2f(0.0f, 0.0f));
	fightScene.addGameObject(backgroundFightScene);*/

#pragma endregion


#pragma region MainMenu

#pragma region Setting up and updating highscore

	// Creating the textobjects for the highscores
	//TextObject highscoreText1("highscoreText1", font, "Highscore 1: 0");
	//highscoreText1.setPosition(sf::Vector2f(100.0f, 280.0f));
	//highscoreText1.setFillColor(whiteColor);

	//TextObject highscoreText2("highscoreText2", font, "Highscore 2: 0");
	//highscoreText2.setPosition(sf::Vector2f(100.0f, 300.0f));
	//highscoreText2.setFillColor(whiteColor);

	//TextObject highscoreText3("highscoreText3", font, "Highscore 3: 0");
	//highscoreText3.setPosition(sf::Vector2f(100.0f, 320.0f));
	//highscoreText3.setFillColor(whiteColor);

	//TextObject highscoreText4("highscoreText4", font, "Highscore 4: 0");
	//highscoreText4.setPosition(sf::Vector2f(100.0f, 340.0f));
	//highscoreText4.setFillColor(whiteColor);

	//TextObject highscoreText5("highscoreText5", font, "Highscore 5: 0");
	//highscoreText5.setPosition(sf::Vector2f(100.0f, 360.0f));
	//highscoreText5.setFillColor(whiteColor);

	// Some values that are used for the main menu
	//bool fileExists = false;
	//float timer = 0;
	//float desiredTime = 1;

	//// Opening the file so that it can be read
	//std::ifstream ifStream_Highscore(highscoreFile);

	//// Creating highscore file and adding five scores of zero if it doesn't exist. If the file exists, update the score.
	//if (ifStream_Highscore.fail())
	//{
	//	// Opening the file and edit it
	//	std::ofstream ofStream_Highscore(highscoreFile);

	//	ofStream_Highscore << "0\n";
	//	ofStream_Highscore << "0\n";
	//	ofStream_Highscore << "0\n";
	//	ofStream_Highscore << "0\n";
	//	ofStream_Highscore << "0\n";

	//	ofStream_Highscore.close();

	//	// Small timer, otherwise the program opens the file before it is created in Windows
	//	if (!fileExists)
	//	{
	//		if (timer >= desiredTime)
	//			fileExists = true;
	//		else if (timer < desiredTime)
	//			timer++;
	//	}
	//}
	//else
	//	fileExists = true;

	//// Sort the score if the file of the scores exists
	//if (fileExists) {
	//	//SortScore(ifStream_Highscore, vectorScore, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5, highscoreFile);
	//}

#pragma endregion

#pragma region PlayButton
//	// Creating the playbutton and setting the scene change action
//
//	Button playButton("playButton", font, "PLAY", sf::Vector2f(154, 69.0f), true, blackColor, orangeColor);
//	playButton.setPosition(sf::Vector2f(562.69f, 265.5f));
//
//	playButton.setButtonAction([&sceneCounter, &sceneChanged, &selectSound]()
//		{
//			selectSound.play();
//			sceneCounter = 1;
//			sceneChanged = false;
//		});
//
#pragma endregion

#pragma region EraseButton
//	// Creating the erase button and setting the action for erasing the game data

//	Button eraseButton("eraseButton", font, "ERASE GAME DATA", sf::Vector2f(387.48f, 69.0f), true, blackColor, orangeColor);
//	eraseButton.setPosition(sf::Vector2f(445.47f, 375.0f));
//
//	eraseButton.setButtonAction([&highscoreText1, &highscoreText2, &highscoreText3, &highscoreText4, &highscoreText5, &highscoreFile, &selectSound]()
//		{
//			selectSound.play();
//
//			// Opening the file with scores
//			std::ifstream ifStream_Highscore(highscoreFile);
//
//			//If opening the file doesn't fail, reset all the score to 0
//			if (!ifStream_Highscore.fail())
//			{
//				std::ofstream ofStream_Highscore(highscoreFile);
//
//				for (int i = 0; i < 5; i++) {
//					ofStream_Highscore << "0\n";
//				}
//
//				ofStream_Highscore.close();
//
//				// Update the score text
//				UpdateScore(highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5, highscoreFile);
//			}
//		});

#pragma endregion

#pragma region QuitButton
//	// Adding the quit button to close the game
//
//	QuitButton quitButton("quitButton", font, "QUIT", sf::Vector2f(154, 69.0f), true, blackColor, orangeColor, window);
//	quitButton.setPosition(sf::Vector2f(562.69f, 484.5f));
//
#pragma endregion

#pragma region DifficultyButtons

//	Button younglingButton("YounglingButton", font, "Youngling", sf::Vector2f(208.94f, 37.4f), false, blackColor, orangeColor);
//	younglingButton.setPosition(sf::Vector2f(987.25f, 278.0f));
//	younglingButton.setButtonColor(redColor);

//	Button apprenticeButton("ApprenticeButton", font, "Apprentice", sf::Vector2f(208.94f, 37.4f), false, blackColor, orangeColor);
//	apprenticeButton.setPosition(sf::Vector2f(987.25f, 336.59f));
//	apprenticeButton.setButtonColor(greenColor);

//	Button masterButton("MasterButton", font, "Master", sf::Vector2f(208.94f, 37.4f), false, blackColor, orangeColor);
//	masterButton.setPosition(sf::Vector2f(987.25f, 395.69f));
//	masterButton.setButtonColor(redColor);

//	younglingButton.setButtonAction([&youngling, &apprentice, &master, &younglingButton, &apprenticeButton, &masterButton, &selectSound]() {
//		youngling = true;
//		apprentice = false;
//		master = false;

//		selectSound.play();

//		younglingButton.setButtonColor(greenColor);
//		apprenticeButton.setButtonColor(redColor);
//		masterButton.setButtonColor(redColor);
//		});

//	apprenticeButton.setButtonAction([&youngling, &apprentice, &master, &younglingButton, &apprenticeButton, &masterButton, &selectSound]() {
//		youngling = false;
//		apprentice = true;
//		master = false;

//		selectSound.play();

//		younglingButton.setButtonColor(redColor);
//		apprenticeButton.setButtonColor(greenColor);
//		masterButton.setButtonColor(redColor);
//		});

//	masterButton.setButtonAction([&youngling, &apprentice, &master, &younglingButton, &apprenticeButton, &masterButton, &selectSound]() {
//		youngling = false;
//		apprentice = false;
//		master = true;

//		selectSound.play();

//		younglingButton.setButtonColor(redColor);
//		apprenticeButton.setButtonColor(redColor);
//		masterButton.setButtonColor(greenColor);
//		});

#pragma endregion

#pragma endregion


#pragma region FightScene

#pragma region PlayerInfo
//
//	Character player("Player", "playerSprite", 0, 0, 0);
//
//	TextObject playerName("playerName", font, "Name");
//	playerName.setCharacterSize(23);
//	playerName.setFillColor(whiteColor);
//	playerName.setPosition(sf::Vector2f(272.0f, 60.88f));
//
//	TextObject playerHP("playerHP", font, "HP");
//	playerHP.setCharacterSize(23);
//	playerHP.setFillColor(whiteColor);
//	playerHP.setPosition(sf::Vector2f(244.0f, 99.57f));
//
//	TextObject playerAttack("playerAttack", font, "Attack");
//	playerAttack.setCharacterSize(23);
//	playerAttack.setFillColor(whiteColor);
//	playerAttack.setPosition(sf::Vector2f(278.0f, 137.57f));
//
//	TextObject playerDefense("playerDefense", font, "Defense");
//	playerDefense.setCharacterSize(23);
//	playerDefense.setFillColor(whiteColor);
//	playerDefense.setPosition(sf::Vector2f(298.0f, 179.57f));
//
//	SpriteObject player1Sprite("player1Sprite", "Assets/PlayerCharacters/Character1.png");
//	SpriteObject player2Sprite("player2Sprite", "Assets/PlayerCharacters/Character2.png");
//	SpriteObject player3Sprite("player3Sprite", "Assets/PlayerCharacters/Character3.png");
//
//	SpriteObject playerSprites[3] = { player1Sprite, player2Sprite, player3Sprite };
//
#pragma endregion
//
//
#pragma region EnemyInfo
//
//	Character enemy1("Darth Vader", "Assets/EnemyCharacters/Enemy1.png", 20, 13, 13);
//	Character enemy2("Darth Sidious", "Assets/EnemyCharacters/Enemy2.png", 18, 15, 14);
//	Character enemy3("Stormtrooper", "Assets/EnemyCharacters/Enemy3.png", 17, 10, 10);
//	Character enemy4("Boba Fett", "Assets/EnemyCharacters/Enemy4.png", 19, 13, 13);
//	Character enemy5("Tusken Raider", "Assets/EnemyCharacters/Enemy5.png", 17, 11, 10);
//	Character enemy6("Moff Tarkin", "Assets/EnemyCharacters/Enemy6.png", 17, 10, 15);
//	Character enemy7("Bossk", "Assets/EnemyCharacters/Enemy7.png", 19, 13, 10);
//	Character enemy8("Red Guard", "Assets/EnemyCharacters/Enemy8.png", 18, 13, 13);
//	Character enemy9("IG-88B", "Assets/EnemyCharacters/Enemy9.png", 18, 11, 15);
//	Character enemy10("Scout Trooper", "Assets/EnemyCharacters/Enemy10.png", 17, 10, 11);
//
//	Character enemyCharacters[10] = { enemy1, enemy2, enemy3, enemy4, enemy5, enemy6, enemy7, enemy8, enemy9, enemy10 };
//
//	TextObject enemyName("enemyName", font, "Name");
//	enemyName.setCharacterSize(25);
//	enemyName.setFillColor(whiteColor);
//	enemyName.setPosition(sf::Vector2f(970.75f, 60.88f));
//
//	TextObject enemyHP("enemyHP", font, "HP");
//	enemyHP.setCharacterSize(25);
//	enemyHP.setFillColor(whiteColor);
//	enemyHP.setPosition(sf::Vector2f(941.79f, 99.57f));
//
//	TextObject enemyAttack("enemyAttack", font, "Attack");
//	enemyAttack.setCharacterSize(25);
//	enemyAttack.setFillColor(whiteColor);
//	enemyAttack.setPosition(sf::Vector2f(975.75f, 137.57f));
//
//	TextObject enemyDefense("enemyDefense", font, "Defense");
//	enemyDefense.setCharacterSize(25);
//	enemyDefense.setFillColor(whiteColor);
//	enemyDefense.setPosition(sf::Vector2f(995.73f, 179.57f));
//
//	SpriteObject enemy1Sprite("Enemy1Sprite", enemy1.getSpriteFile());
//	SpriteObject enemy2Sprite("Enemy2Sprite", enemy2.getSpriteFile());
//	SpriteObject enemy3Sprite("Enemy3Sprite", enemy3.getSpriteFile());
//	SpriteObject enemy4Sprite("Enemy4Sprite", enemy4.getSpriteFile());
//	SpriteObject enemy5Sprite("Enemy5Sprite", enemy5.getSpriteFile());
//	SpriteObject enemy6Sprite("Enemy6Sprite", enemy6.getSpriteFile());
//	SpriteObject enemy7Sprite("Enemy7Sprite", enemy7.getSpriteFile());
//	SpriteObject enemy8Sprite("Enemy8Sprite", enemy8.getSpriteFile());
//	SpriteObject enemy9Sprite("Enemy9Sprite", enemy9.getSpriteFile());
//	SpriteObject enemy10Sprite("Enemy10Sprite", enemy10.getSpriteFile());
//
//	SpriteObject enemySprites[10] = { enemy1Sprite, enemy2Sprite, enemy3Sprite, enemy4Sprite, enemy5Sprite, enemy6Sprite, enemy7Sprite, enemy8Sprite, enemy9Sprite, enemy10Sprite };

#pragma endregion

//	// Values used for the fight scene
//	int damageDone = 0;
//	int healDone = 0;
//	bool playerTurn = true;
//	string previousEnemy = " ";
//
//	// Description text creations and settings
//	TextObject descriptionText("DescriptionText", font, "You attacked the enemy and did 3 damage.");
//	descriptionText.setFillColor(whiteColor);
//	descriptionText.setCharacterSize(15);
//	descriptionText.setPosition(sf::Vector2f(736.35f, 430.35f));
//
//	TextObject specialDescriptionText("specialDescriptionText", font, " ");
//	specialDescriptionText.setFillColor(whiteColor);
//	specialDescriptionText.setCharacterSize(15);
//	specialDescriptionText.setPosition(sf::Vector2f(736.35f, 460.35f));
//
//	// Buttons creation and settings
//	Button attackButton("attackButton", font, "Attack", sf::Vector2f(205.0f, 69.66f), true, blackColor, orangeColor);
//	attackButton.setPosition(sf::Vector2f(57.63f, 399.69f));
//
//	Button healButton("healButton", font, "Heal", sf::Vector2f(205.0f, 69.66f), true, blackColor, orangeColor);
//	healButton.setPosition(sf::Vector2f(403.0f, 399.69f));
//
//	Button proceedButton("ProceedButton", font, "Proceed", sf::Vector2f(205.0f, 70.0f), true, blackColor, orangeColor);
//	proceedButton.setPosition(sf::Vector2f(231.0f, 556.0f));


#pragma region ButtonActions

//	proceedButton.setButtonAction([&fightScene, &proceedButton, &player, &enemyCharacters, &enemySelected, &healDone, &damageDone, &playerHP, &enemyHP, &descriptionText, &specialDescriptionText, &playerTurn, &enemySprites,
//		&enemyName, &enemyAttack, &enemyDefense, &attackButton,
//		&healButton, &score, &vectorScore, &previousEnemy,
//		&ifStream_Highscore, &highscoreText1, &highscoreText2, &highscoreText3, &highscoreText4, &highscoreText5, highscoreFile,
//		&youngling, &apprentice, &master,
//		&victorySound, &gameoverSound, &attackSound, &healSound, &doNothingSoundHandler, &fightMusic]() {
//
//			fightScene.removeGameObject(proceedButton.getIdentifier());
//			specialDescriptionText.setText("");
//
//			if (enemyCharacters[enemySelected].getHP() > 0) {
//				EnemyTurn(player, enemyCharacters, enemySelected, healDone, damageDone, playerHP, enemyHP, descriptionText, specialDescriptionText, playerTurn, score, youngling, apprentice, master, victorySound, gameoverSound, attackSound, healSound, doNothingSoundHandler, fightMusic);
//			}
//			else if (enemyCharacters[enemySelected].getHP() <= 0) {
//				previousEnemy = enemyCharacters[enemySelected].getName();
//				fightScene.removeGameObject(enemySprites[enemySelected].getIdentifier());
//				GenerateRandomEnemy(enemySelected, enemyCharacters, enemySprites, enemyName, enemyHP, enemyAttack, enemyDefense, fightScene, descriptionText, previousEnemy);
//				score += 1;
//				playerTurn = true;
//			}
//
//			if (player.getHP() > 0) {
//				fightScene.addGameObject(attackButton);
//				fightScene.addGameObject(healButton);
//			}
//			else if (player.getHP() <= 0) {
//				fightScene.removeGameObject(attackButton.getIdentifier());
//				fightScene.removeGameObject(healButton.getIdentifier());
//				fightScene.removeGameObject(proceedButton.getIdentifier());
//				vectorScore.push_back(score);
//				SortScore(ifStream_Highscore, vectorScore, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5, highscoreFile);
//			}
//
//		});
//
//
//	attackButton.setButtonAction([&playerTurn, &player, &enemyCharacters, &enemySelected, &damageDone, &playerHP, &enemyHP, &descriptionText, &specialDescriptionText, &fightScene,
//		&enemySprites, &enemyName, &enemyAttack, &enemyDefense,
//		&proceedButton, &attackButton, &healButton, &score,
//		&victorySound, &gameoverSound, &attackSound, &fightMusic]() {
//			if (playerTurn) {
//				Attack("Enemy", player, enemyCharacters, enemySelected, damageDone, playerHP, enemyHP, descriptionText, specialDescriptionText, playerTurn, score, victorySound, gameoverSound, attackSound, fightMusic);
//
//				fightScene.addGameObject(proceedButton);
//				fightScene.removeGameObject(attackButton.getIdentifier());
//				fightScene.removeGameObject(healButton.getIdentifier());
//			}
//		});
//
//
//	healButton.setButtonAction([&player, &enemyCharacters, &enemySelected, &healDone, &playerHP, &enemyHP, &descriptionText, &playerTurn, &fightScene, &proceedButton, &attackButton, &healButton, &healSound]() {
//		if (playerTurn) {
//			Heal("Player", player, enemyCharacters, enemySelected, healDone, playerHP, enemyHP, descriptionText, playerTurn, healSound);
//
//			fightScene.addGameObject(proceedButton);
//			fightScene.removeGameObject(attackButton.getIdentifier());
//			fightScene.removeGameObject(healButton.getIdentifier());
//		}
//		});
//
#pragma endregion
//
//
#pragma endregion


#pragma region SelectMenu

#pragma region BackButton
//
//	// Creating the back button and setting up the button action
//
//	Button backButton("backButton", font, "QUIT", sf::Vector2f(288.0f, 62.0f), true, blackColor, orangeColor);
//	backButton.setPosition(sf::Vector2f(951.25f, 620.94f));
//
//	backButton.setButtonAction([&sceneCounter, &sceneChanged, &fightScene, &player, &playerSprites, &enemySprites, &enemySelected, &menuMusic, &fightMusic, &backSound]()
//		{
//			// If the player goes back in the fightscene, the images of the player and enemy should be removed
//			if (sceneCounter == 2) {
//				RemoveImages(fightScene, player, playerSprites, enemySprites, enemySelected);
//				menuMusic.play();
//				fightMusic.stop();
//			}
//
//			backSound.play();
//
//			sceneCounter = 0;
//			sceneChanged = false;
//		});
//
#pragma endregion


#pragma region LoadingCharacters
//
#pragma region Character1
//
//	// Setting up the character, sprite and text
//	Character character1("character1", "Character1", 0, 0, 0);
//
//	TextObject character1Name("character1_Name", font, "Name");
//	SpriteObject character1Sprite("character1_Sprite", "Assets/PlayerCharacters/Character1.png");
//	TextObject character1HP("character1_HP", font, "HP: ");
//	TextObject character1Attack("character1_Attack", font, "Strength: ");
//	TextObject character1Defense("character1_Defense", font, "Defense: ");
//
//	// Place the stats of the characters on the right spot
//	PlaceCharacterStats(character1Name, sf::Vector2f(150.0f, 167.89f), whiteColor, 18, character1Sprite, sf::Vector2f(109.22f, 221.25f), character1HP, sf::Vector2f(120.0f, 449.57f), whiteColor, 18, character1Attack, sf::Vector2f(120.0f, 469.57f), whiteColor, 18, character1Defense, sf::Vector2f(120.0f, 489.57f), whiteColor, 18);
//
//	// Opening the characterfile en load the stats if the file opens
//	std::ifstream character1Stats("Assets/PlayerCharacters/Character1.txt");
//	if (!character1Stats.fail())
//		LoadCharacterStats(character1Stats, character1, character1Name, character1HP, character1Attack, character1Defense);
//
#pragma endregion
//
//
#pragma region Character2
//
//	// Setting up the character, sprite and text
//	Character character2("character2", "Character2", 0, 0, 0);
//
//	TextObject character2Name("character2_Name", font, "Name");
//	SpriteObject character2Sprite("character2_Sprite", "Assets/PlayerCharacters/Character2.png");
//	TextObject character2HP("character2_HP", font, "HP: ");
//	TextObject character2Attack("character2_Attack", font, "Attack: ");
//	TextObject character2Defense("character2_Defense", font, "Defense: ");
//
//	// Place the stats of the characters on the right spot
//	PlaceCharacterStats(character2Name, sf::Vector2f(545.0f, 167.89f), whiteColor, 18, character2Sprite, sf::Vector2f(549.22f, 221.25f), character2HP, sf::Vector2f(570.0f, 449.57f), whiteColor, 18, character2Attack, sf::Vector2f(570.0f, 469.57f), whiteColor, 18, character2Defense, sf::Vector2f(570.0f, 489.57f), whiteColor, 18);
//
//	// Opening the characterfile en load the stats if the file opens
//	std::ifstream character2Stats("Assets/PlayerCharacters/Character2.txt");
//	if (!character2Stats.fail())
//		LoadCharacterStats(character2Stats, character2, character2Name, character2HP, character2Attack, character2Defense);
//
#pragma endregion
//
//
#pragma region Character3
//
//	// Setting up the character, sprite and text
//	Character character3("character3", "Character3", 0, 0, 0);
//
//	TextObject character3Name("character3_Name", font, "Name");
//	SpriteObject character3Sprite("character3_Sprite", "Assets/PlayerCharacters/Character3.png");
//	TextObject character3HP("character3_HP", font, "HP: ");
//	TextObject character3Attack("character3_Attack", font, "Attack: ");
//	TextObject character3Defense("character3_Defense", font, "Defense: ");
//
//	// Place the stats of the characters on the right spot
//	PlaceCharacterStats(character3Name, sf::Vector2f(1040.0f, 167.89f), whiteColor, 18, character3Sprite, sf::Vector2f(989.22f, 221.25f), character3HP, sf::Vector2f(1010.0f, 449.57f), whiteColor, 18, character3Attack, sf::Vector2f(1010.0f, 469.57f), whiteColor, 18, character3Defense, sf::Vector2f(1010.0f, 489.57f), whiteColor, 18);
//
//	// Opening the characterfile en load the stats if the file opens
//	std::ifstream character3Stats("Assets/PlayerCharacters/Character3.txt");
//	if (!character3Stats.fail())
//		LoadCharacterStats(character3Stats, character3, character3Name, character3HP, character3Attack, character3Defense);
//
#pragma endregion
//
#pragma endregion


#pragma region CharacterSelection
//
//	// Creating the buttons for the character and the action of the buttons themselves
//	Button character1Button("character1Button", font, "", sf::Vector2f(328.98f, 436.01f), true, invisibleColor, highlightColor);
//	character1Button.setPosition(sf::Vector2f(35.25f, 142.0f));
//
//	Button character2Button("character2Button", font, "", sf::Vector2f(328.98f, 436.01f), true, invisibleColor, highlightColor);
//	character2Button.setPosition(sf::Vector2f(475.09f, 142.0f));
//
//	Button character3Button("character3Button", font, "", sf::Vector2f(328.98f, 436.01f), true, invisibleColor, highlightColor);
//	character3Button.setPosition(sf::Vector2f(909.5f, 142.0f));
//
//	// If the player clicks on a character, the previous enemy will be stored and the chosen character will be casted to the player character. A random enemy is generated and the values for the fightscene are being reset. The scenecounter changes and shows the other scene.
//	character1Button.setButtonAction([&player, &enemySelected, &sceneCounter, &sceneChanged, &character1, &playerName, &playerHP, &playerAttack, &playerDefense, &playerSprites, &fightScene, &enemyCharacters, &enemySprites, &enemyName, &enemyHP, &enemyAttack, &enemyDefense, &descriptionText, &playerTurn, &score, &proceedButton, &attackButton, &healButton, &specialDescriptionText, &previousEnemy, &menuMusic, &fightMusic, &selectSound]() {
//		previousEnemy = enemyCharacters[enemySelected].getName();
//		SetPlayer(character1, player, playerName, playerHP, playerAttack, playerDefense, 1, playerSprites, fightScene);
//		GenerateRandomEnemy(enemySelected, enemyCharacters, enemySprites, enemyName, enemyHP, enemyAttack, enemyDefense, fightScene, descriptionText, previousEnemy);
//		SetValuesFightScene(fightScene, playerTurn, score, proceedButton, attackButton, healButton, specialDescriptionText);
//
//		selectSound.play();
//		menuMusic.stop();
//		fightMusic.play();
//
//		sceneCounter = 2;
//		sceneChanged = false;
//		});
//
//	// If the player clicks on a character, the previous enemy will be stored and the chosen character will be casted to the player character. A random enemy is generated and the values for the fightscene are being reset. The scenecounter changes and shows the other scene.
//	character2Button.setButtonAction([&player, &enemySelected, &sceneCounter, &sceneChanged, &character2, &playerName, &playerHP, &playerAttack, &playerDefense, &playerSprites, &fightScene, &enemyCharacters, &enemySprites, &enemyName, &enemyHP, &enemyAttack, &enemyDefense, &descriptionText, &playerTurn, &score, &proceedButton, &attackButton, &healButton, &specialDescriptionText, &previousEnemy, &menuMusic, &fightMusic, &selectSound]() {
//		previousEnemy = enemyCharacters[enemySelected].getName();
//		SetPlayer(character2, player, playerName, playerHP, playerAttack, playerDefense, 2, playerSprites, fightScene);
//		GenerateRandomEnemy(enemySelected, enemyCharacters, enemySprites, enemyName, enemyHP, enemyAttack, enemyDefense, fightScene, descriptionText, previousEnemy);
//		SetValuesFightScene(fightScene, playerTurn, score, proceedButton, attackButton, healButton, specialDescriptionText);
//
//		selectSound.play();
//		menuMusic.stop();
//		fightMusic.play();
//
//		sceneCounter = 2;
//		sceneChanged = false;
//		});
//
//	// If the player clicks on a character, the previous enemy will be stored and the chosen character will be casted to the player character. A random enemy is generated and the values for the fightscene are being reset. The scenecounter changes and shows the other scene.
//	character3Button.setButtonAction([&player, &enemySelected, &sceneCounter, &sceneChanged, &character3, &playerName, &playerHP, &playerAttack, &playerDefense, &playerSprites, &fightScene, &enemyCharacters, &enemySprites, &enemyName, &enemyHP, &enemyAttack, &enemyDefense, &descriptionText, &playerTurn, &score, &proceedButton, &attackButton, &healButton, &specialDescriptionText, &previousEnemy, &menuMusic, &fightMusic, &selectSound]() {
//		previousEnemy = enemyCharacters[enemySelected].getName();
//		SetPlayer(character3, player, playerName, playerHP, playerAttack, playerDefense, 3, playerSprites, fightScene);
//		GenerateRandomEnemy(enemySelected, enemyCharacters, enemySprites, enemyName, enemyHP, enemyAttack, enemyDefense, fightScene, descriptionText, previousEnemy);
//		SetValuesFightScene(fightScene, playerTurn, score, proceedButton, attackButton, healButton, specialDescriptionText);
//
//		selectSound.play();
//		menuMusic.stop();
//		fightMusic.play();
//
//		sceneCounter = 2;
//		sceneChanged = false;
//		});
//
#pragma endregion

#pragma endregion


#pragma region Adding elements to selectMenu and fightScene
//
//	//----------Main Menu----------//
//	mainMenu.addGameObject(playButton);
//	mainMenu.addGameObject(eraseButton);
//	mainMenu.addGameObject(quitButton);
//
//	mainMenu.addGameObject(younglingButton);
//	mainMenu.addGameObject(apprenticeButton);
//	mainMenu.addGameObject(masterButton);
//
//	mainMenu.addGameObject(highscoreText1);
//	mainMenu.addGameObject(highscoreText2);
//	mainMenu.addGameObject(highscoreText3);
//	mainMenu.addGameObject(highscoreText4);
//	mainMenu.addGameObject(highscoreText5);
//
//
//	//----------Select Menu----------//
//	selectMenu.addGameObject(character1Name);
//	selectMenu.addGameObject(character1Sprite);
//	selectMenu.addGameObject(character1HP);
//	selectMenu.addGameObject(character1Attack);
//	selectMenu.addGameObject(character1Defense);
//
//	selectMenu.addGameObject(character2Name);
//	selectMenu.addGameObject(character2Sprite);
//	selectMenu.addGameObject(character2HP);
//	selectMenu.addGameObject(character2Attack);
//	selectMenu.addGameObject(character2Defense);
//
//	selectMenu.addGameObject(character3Name);
//	selectMenu.addGameObject(character3Sprite);
//	selectMenu.addGameObject(character3HP);
//	selectMenu.addGameObject(character3Attack);
//	selectMenu.addGameObject(character3Defense);
//
//	selectMenu.addGameObject(backButton);
//	selectMenu.addGameObject(character1Button);
//	selectMenu.addGameObject(character2Button);
//	selectMenu.addGameObject(character3Button);
//
//
//	//----------Fight Scene----------//
//	fightScene.addGameObject(playerName);
//	fightScene.addGameObject(playerHP);
//	fightScene.addGameObject(playerAttack);
//	fightScene.addGameObject(playerDefense);
//
//	fightScene.addGameObject(enemyName);
//	fightScene.addGameObject(enemyHP);
//	fightScene.addGameObject(enemyAttack);
//	fightScene.addGameObject(enemyDefense);
//
//	fightScene.addGameObject(backButton);
//
//	fightScene.addGameObject(descriptionText);
//	fightScene.addGameObject(specialDescriptionText);
//
#pragma endregion

#pragma region SceneHandler

	// Creating SceneHandler and adding the three scenes
	//SceneHandler handler;
	//handler.addScene(mainMenu);
	//handler.addScene(selectMenu);
	//handler.addScene(fightScene);

	// Runs the code below while the window is open
	//while (window.isOpen())
	//{
	//	sf::Event event; // Creating an event

	//	while (window.pollEvent(event)) // While there is activity, run the code below
	//	{
	//		if (event.type == sf::Event::Closed) // If the event is being closed, close the window
	//			window.close();
	//		else
	//		{
	//			// Updates the scene for input
	//			/*if (sceneCounter == 0)
	//				mainMenu.handleEvent(event, window);
	//			else if (sceneCounter == 1)
	//				selectMenu.handleEvent(event, window);
	//			else if (sceneCounter == 2)
	//				fightScene.handleEvent(event, window);*/

	//			handler.handleEvent(newEvent, window);
	//		}

	//		// Changes, adds and removes the scenes
	//		if (sceneCounter == 0 && !sceneChanged)
	//		{
	//			handler.popScene();
	//			handler.stackScene("mainMenu");
	//			sceneChanged = true;
	//		}
	//		else if (sceneCounter == 1 && !sceneChanged)
	//		{
	//			handler.popScene();
	//			handler.stackScene("selectMenu");
	//			sceneChanged = true;
	//		}
	//		else if (sceneCounter == 2 && !sceneChanged)
	//		{
	//			handler.popScene();
	//			handler.stackScene("fightScene");
	//			sceneChanged = true;
	//		}

	//		window.clear(whiteColor); // Clears the window to a white color
	//		handler.update(); // Updates the handles
	//		handler.render(window); // Renders the window of the handler
	//		window.display(); // Shows the window
	//	}
	//}



#pragma endregion

#pragma endregion

#pragma endregion
}

//	while (window.isOpen())
//	{
//		sf::Event newEvent;
//		while (window.pollEvent(newEvent))
//		{
//			if (newEvent.type == sf::Event::Closed)
//				window.close();
//			else {
//				if (handler.GetCurrentScene() == "MainMenu_Scene")
//					mainMenu.scene.handleEvent(newEvent, window);
//				else if (handler.GetCurrentScene() == "SelectMenu_Scene")
//					selectMenu.scene.handleEvent(newEvent, window);
//				else if (handler.GetCurrentScene() == "FightMenu_Scene")
//					fightMenu.scene.handleEvent(newEvent, window);
//			}
//		}
//
//		window.clear(sf::Color::White);
//		handler.update();
//		handler.render(window);
//		window.display();
//	}
//
//	// Returns 0 because main is an int that requires a return
//	return 0;
//}
//
//void SortScore(std::ifstream& highscoreStats, std::vector<int>& vectorScore, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5, string highscoreFile) {
//
//	std::string line; // String that is used for importing the lines
//
//	// Checks if the file has ended, if not, import the lines and convert it to ints and push it to the vectorScore
//	while (highscoreStats.peek() != EOF) {
//		std::getline(highscoreStats, line);
//		vectorScore.push_back(stoi(line));
//	}
//
//	// Iterators used to point at the memort addresses of the vectorscore
//	// Iterators reduce the complexity and execution time of the program
//	vector<int>::iterator ptr = vectorScore.begin();
//	vector<int>::iterator ftr = vectorScore.end();
//
//	// Sorts the list from big to small numbers
//	sort(ptr, ftr, greater<int>());
//
//	// Opening the file so that it can be edited
//	std::ofstream phighscoreStats(highscoreFile);
//
//	// Editing the file with the sorted score
//	for (int i = 0; i < 5; i++) {
//		phighscoreStats << to_string(vectorScore[i]) + "\n";
//	}
//
//	// Closing the file after it has beed edited
//	phighscoreStats.close();
//
//	// Updating the score to be displayed on screen
//	UpdateScore(highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5, highscoreFile);
//}
//
//void UpdateScore(TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5, string highscoreFile) {
//	// Opening the file, reading it and setting the text to that score
//
//	std::ifstream highscoreStats(highscoreFile);
//
//	std::string line;
//	std::string score[5];
//
//	for (int i = 0; i < 5; i++)
//	{
//		std::getline(highscoreStats, line);
//		score[i] = line;
//	}
//
//	highscoreText1.setText("Highscore 1: " + score[0]);
//	highscoreText2.setText("Highscore 2: " + score[1]);
//	highscoreText3.setText("Highscore 3: " + score[2]);
//	highscoreText4.setText("Highscore 4: " + score[3]);
//	highscoreText5.setText("Highscore 5: " + score[4]);
//
//	highscoreStats.close();
//}
//
//void SetPlayer(Character selectedCharacter, Character& player, TextObject& playerName, TextObject& playerHP, TextObject& playerAttack, TextObject& playerDefense, int characterSelected, SpriteObject playerSprites[], Scene& fightScene) {
//	// Set the stats of the player to the one of the chosen character	
//	player.setName(selectedCharacter.getName());
//	player.setHP(selectedCharacter.getHP());
//	player.setmaxHP(player.getHP());
//	player.setAttack(selectedCharacter.getAttack());
//	player.setDefense(selectedCharacter.getDefense());
//
//	// Set the stats of the player to the text on screen
//	playerName.setText(player.getName());
//	playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP()));
//	playerAttack.setText(std::to_string(player.getAttack()));
//	playerDefense.setText(std::to_string(player.getDefense()));
//
//	// Checks which character is selected and shows that sprite on screen
//	if (characterSelected == 1) {
//		playerSprites[0].setPosition(sf::Vector2f(20.0f, 36.0f));
//		fightScene.addGameObject(playerSprites[0]);
//	}
//	else if (characterSelected == 2) {
//		playerSprites[1].setPosition(sf::Vector2f(20.0f, 36.0f));
//		fightScene.addGameObject(playerSprites[1]);
//	}
//	else if (characterSelected == 3) {
//		playerSprites[2].setPosition(sf::Vector2f(20.0f, 36.0f));
//		fightScene.addGameObject(playerSprites[2]);
//	}
//}
//
//void LoadCharacterStats(std::ifstream& characterStats, Character& character, TextObject& characterName, TextObject& characterHP, TextObject& characterAttack, TextObject& characterDefense) {
//	// Opening the file and setting each line of the text file to the corresponding info of the player
//
//	std::string line;
//
//	std::getline(characterStats, line);
//	character.setName(line);
//	characterName.setText(line);
//
//	std::getline(characterStats, line);
//	character.setHP(std::stoi(line)); // stoi transfers string to int
//	character.setmaxHP(std::stoi(line)); // stoi transfers string to int
//	characterHP.setText("HP: " + std::to_string(character.getHP()));
//
//	std::getline(characterStats, line);
//	character.setAttack(std::stoi(line)); // stoi transfers string to int
//	characterAttack.setText("Attack: " + std::to_string(character.getAttack()));
//
//	std::getline(characterStats, line);
//	character.setDefense(std::stoi(line)); // stoi transfers string to int
//	characterDefense.setText("Defense: " + std::to_string(character.getDefense()));
//
//	characterStats.close();
//}
//
//void PlaceCharacterStats(TextObject& characterName, sf::Vector2f namePosition, sf::Color nameColor, int nameSize, SpriteObject& characterSprite, sf::Vector2f spritePosition, TextObject& characterHP, sf::Vector2f HPPosition, sf::Color HPColor, int HPSize, TextObject& characterAttack, sf::Vector2f attackPosition, sf::Color attackColor, int attackSize, TextObject& characterDefense, sf::Vector2f defensePosition, sf::Color defenseColor, int defenseSize) {
//	// Place the character stats on the given positions
//
//	characterName.setPosition(namePosition);
//	characterName.setFillColor(nameColor);
//	characterName.setCharacterSize(nameSize);
//
//	characterSprite.setPosition(spritePosition);
//
//	characterHP.setPosition(HPPosition);
//	characterHP.setFillColor(HPColor);
//	characterHP.setCharacterSize(HPSize);
//
//	characterAttack.setPosition(attackPosition);
//	characterAttack.setFillColor(attackColor);
//	characterAttack.setCharacterSize(attackSize);
//
//	characterDefense.setPosition(defensePosition);
//	characterDefense.setFillColor(defenseColor);
//	characterDefense.setCharacterSize(defenseSize);
//}
//
//void GenerateRandomEnemy(int& enemySelected, Character enemyCharacters[], SpriteObject enemySprites[], TextObject& enemyName, TextObject& enemyHP, TextObject& enemyAttack, TextObject& enemyDefense, Scene& fightScene, TextObject& descriptionText, string previousEnemy) {
//	//Generates random number between 0 and 9
//	enemySelected = rand() % 10;
//
//	// Checks if the selected enemy is the previous enemy. If so, generate a new one. If not, set the info of the selected enemy to the enemy character
//	if (enemyCharacters[enemySelected].getName() == previousEnemy) {
//		GenerateRandomEnemy(enemySelected, enemyCharacters, enemySprites, enemyName, enemyHP, enemyAttack, enemyDefense, fightScene, descriptionText, previousEnemy);
//	}
//	else if (enemyCharacters[enemySelected].getName() != previousEnemy) {
//		enemyCharacters[enemySelected].setHP(enemyCharacters[enemySelected].getmaxHP());
//
//		enemyName.setText(enemyCharacters[enemySelected].getName());
//		enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP()));
//		enemyAttack.setText(std::to_string(enemyCharacters[enemySelected].getAttack()));
//		enemyDefense.setText(std::to_string(enemyCharacters[enemySelected].getDefense()));
//
//		// Shows the name of the enemy on screen in the description
//		descriptionText.setFillColor(blueColor);
//		descriptionText.setText("A wild " + enemyCharacters[enemySelected].getName() + " appeared!");
//
//		// Checks which enemy is selected and shows that image on screen
//		if (enemySelected == 0) {
//			enemySprites[0].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[0]);
//		}
//		else if (enemySelected == 1) {
//			enemySprites[1].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[1]);
//		}
//		else if (enemySelected == 2) {
//			enemySprites[2].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[2]);
//		}
//		else if (enemySelected == 3) {
//			enemySprites[3].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[3]);
//		}
//		else if (enemySelected == 4) {
//			enemySprites[4].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[4]);
//		}
//		else if (enemySelected == 5) {
//			enemySprites[5].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[5]);
//		}
//		else if (enemySelected == 6) {
//			enemySprites[6].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[6]);
//		}
//		else if (enemySelected == 7) {
//			enemySprites[7].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[7]);
//		}
//		else if (enemySelected == 8) {
//			enemySprites[8].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[8]);
//		}
//		else if (enemySelected == 9) {
//			enemySprites[9].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[9]);
//		}
//		else if (enemySelected == 10) {
//			enemySprites[10].setPosition(sf::Vector2f(718.0f, 36.0f));
//			fightScene.addGameObject(enemySprites[10]);
//		}
//	}
//}

//void RemoveImages(Scene& fightScene, Character& player, SpriteObject playerSprites[], SpriteObject enemySprites[], int enemySelected) {
//	// Checks which player is selected. Removes the image of the selected player and the enemy
//	int characterSelected = 0;
//
//	if (player.getName() == "Han Solo")
//		characterSelected = 0;
//	else if (player.getName() == "Luke Skywalker")
//		characterSelected = 1;
//	else if (player.getName() == "C-3PO")
//		characterSelected = 2;
//
//	fightScene.removeGameObject(playerSprites[characterSelected].getIdentifier());
//	fightScene.removeGameObject(enemySprites[enemySelected].getIdentifier());
//}

//void Attack(string attackWho, Character& player, Character enemyCharacters[], int enemySelected, int& damageDone, TextObject& playerHP, TextObject& enemyHP, TextObject& descriptionText, TextObject& specialDescription, bool& playerTurn, int score, sf::Sound& victorySound, sf::Sound& gameoverSound, sf::Sound& attackSound, sf::Music& fightMusic) {
//	attackSound.play(); // Plays attack sound
//
//	// Checks who is being attacked
//	if (attackWho == "Player") {
//
//		int attackPower = enemyCharacters[enemySelected].getAttack() + rand() % 6; // Grabs attack of the enemy and adds a random value between 0 and 5
//		int defensePower = player.getDefense() + (-2 + rand() % 4); // Grabs defense of the player and adds a random value between -1 and 3
//
//		damageDone = max(attackPower - defensePower, 0); // Final damage is attackPower - defensePower, smallest number is 0
//
//		player.setHP(player.getHP() - damageDone); // Set the new HP of the player
//		playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP())); // Update the HP text
//		UpdateDescription(attackWho, "-", descriptionText, player, enemyCharacters, enemySelected, damageDone, 0); // Update the description with what happend
//		playerTurn = true; // Player's turn
//
//		// If the player if below 0 HP, set the HP to 0, update the text and give a game over text with the score of the player
//		if (player.getHP() <= 0) {
//			player.setHP(0);
//			playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP()));
//			specialDescription.setFillColor(blueColor);
//			specialDescription.setText("You died with a score of " + std::to_string(score) + "!");
//			playerTurn = false;
//			gameoverSound.play();
//			fightMusic.stop();
//		}
//	}
//	else if (attackWho == "Enemy") {
//
//		int attackPower = player.getAttack() + rand() % 6; // Grabs attack of the player and adds a random value between 0 and 5
//		int defensePower = enemyCharacters[enemySelected].getDefense() + (-2 + rand() % 4);  // Grabs defense of the enemy and adds a random value between -1 and 3
//
//		damageDone = max(attackPower - defensePower, 0); // Final damage is attackPower - defensePower, smallest number is 0
//
//		enemyCharacters[enemySelected].setHP(enemyCharacters[enemySelected].getHP() - damageDone); // Set the new HP of the enemy
//		enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP())); // Update the HP text
//		UpdateDescription(attackWho, "-", descriptionText, player, enemyCharacters, enemySelected, damageDone, 0); // Update the description with what happend
//
//		// If the enemy if below 0 HP, set the HP to 0, update the text and give a message that the player is being killed.
//		if (enemyCharacters[enemySelected].getHP() <= 0) {
//			enemyCharacters[enemySelected].setHP(0);
//			enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP()));
//			specialDescription.setFillColor(blueColor);
//			specialDescription.setText("You killed " + enemyCharacters[enemySelected].getName() + "!");
//			victorySound.play();
//		}
//		// If the player kills an enemy, the player can start with the action with the next enemy
//		else if (enemyCharacters[enemySelected].getHP() > 0) {
//			playerTurn = false; // Enemy's turn
//		}
//	}
//}
//
//void Heal(string healWho, Character& player, Character enemyCharacters[], int enemySelected, int& healDone, TextObject& playerHP, TextObject& enemyHP, TextObject& descriptionText, bool& playerTurn, sf::Sound& healSound) {
//	healSound.play(); // Plays heal sound
//
//	// Checks who is being healed
//	if (healWho == "Player") {
//		healDone = rand() % 5; // Generates a random number between 0 and 4
//
//		player.setHP(player.getHP() + healDone); // Update the HP of the player
//		playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP())); // Update the HP text of the player
//		UpdateDescription("-", healWho, descriptionText, player, enemyCharacters, enemySelected, 0, healDone); // Update the description with how many HP is being recovered
//
//		// If the player hp is above his max HP, the HP is set to max HP and the HP text is updated.
//		if (player.getHP() > player.getmaxHP()) {
//			player.setHP(player.getmaxHP());
//			playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP()));
//		}
//		playerTurn = false; // Enemy's turn
//	}
//	else if (healWho == "Enemy") {
//		healDone = rand() % 5; // Generates a random number between 0 and 4
//
//		enemyCharacters[enemySelected].setHP(enemyCharacters[enemySelected].getHP() + healDone);  // Update the HP of the enemy
//		enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP())); // Update the HP text of the enemy
//		UpdateDescription("-", healWho, descriptionText, player, enemyCharacters, enemySelected, 0, healDone); // Update the description with how many HP is being recovered
//
//		// If the player hp is above his max HP, the HP is set to max HP and the HP text is updated.
//		if (enemyCharacters[enemySelected].getHP() > enemyCharacters[enemySelected].getmaxHP()) {
//			enemyCharacters[enemySelected].setHP(enemyCharacters[enemySelected].getmaxHP());
//			enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP()));
//		}
//		playerTurn = true; // Player's turn
//	}
//}

//void DoNothing(TextObject& descriptionText, Character enemyCharacters[], int enemySelected, bool& playerTurn, SoundHandler& donothingSound) {
//	// Update the description text, plays the sound and gives the turn to the player
//	descriptionText.setFillColor(redColor);
//	descriptionText.setText(enemyCharacters[enemySelected].getName() + " did nothing!");
//	donothingSound.PlaySound();
//	playerTurn = true;
//}

//void UpdateDescription(string attackedWho, string healedWho, TextObject& descriptionText, Character player, Character enemyCharacters[], int enemySelected, int damageDone, int healDone) {
//	// Checks who is attacked or who is healed and displays that in the description
//	if (attackedWho == "Player") {
//		descriptionText.setFillColor(redColor);
//		descriptionText.setText(enemyCharacters[enemySelected].getName() + " attacked you and did " + std::to_string(damageDone) + " damage!");
//	}
//	else if (attackedWho == "Enemy") {
//		descriptionText.setFillColor(greenColor);
//		descriptionText.setText("You attacked " + enemyCharacters[enemySelected].getName() + " and did " + std::to_string(damageDone) + " damage!");
//	}
//
//	if (healedWho == "Player") {
//		descriptionText.setFillColor(greenColor);
//		descriptionText.setText("You healed yourself with " + std::to_string(healDone) + " HP!");
//	}
//	else if (healedWho == "Enemy") {
//		descriptionText.setFillColor(redColor);
//		descriptionText.setText(enemyCharacters[enemySelected].getName() + " healed himself with " + std::to_string(healDone) + " HP!");
//	}
//}

//void EnemyTurn(Character& player, Character enemyCharacters[], int enemySelected, int& healDone, int& damageDone, TextObject& playerHP, TextObject& enemyHP, TextObject& descriptionText, TextObject& specialDescriptionText, bool& playerTurn, int score, bool youngling, bool apprentice, bool master, sf::Sound& victorySound, sf::Sound& gameoverSound, sf::Sound& attackSound, sf::Sound& healSound, SoundHandler& donothingSound, sf::Music& fightMusic) {
//	// Generated a random number between 0 and 10
//	int randomAttack = rand() % 10;
//
//	// Different difficulty systems
//	if (youngling) {
//		// Attack has 30% chance of being chosen, heal 30% and do nothing 40%
//		if (randomAttack == 0 || randomAttack == 1 || randomAttack == 2) {
//			Attack("Player", player, enemyCharacters, enemySelected, damageDone, playerHP, enemyHP, descriptionText, specialDescriptionText, playerTurn, score, victorySound, gameoverSound, attackSound, fightMusic);
//		}
//		else if (randomAttack == 3 || randomAttack == 4 || randomAttack == 5) {
//			if (enemyCharacters[enemySelected].getHP() >= enemyCharacters[enemySelected].getmaxHP()) {
//				EnemyTurn(player, enemyCharacters, enemySelected, healDone, damageDone, playerHP, enemyHP, descriptionText, specialDescriptionText, playerTurn, score, youngling, apprentice, master, victorySound, gameoverSound, attackSound, healSound, donothingSound, fightMusic);
//			}
//			else if (enemyCharacters[enemySelected].getHP() < enemyCharacters[enemySelected].getmaxHP()) {
//				Heal("Enemy", player, enemyCharacters, enemySelected, healDone, playerHP, enemyHP, descriptionText, playerTurn, healSound);
//			}
//		}
//		else if (randomAttack == 6 || randomAttack == 7 || randomAttack == 8 || randomAttack == 9) {
//			DoNothing(descriptionText, enemyCharacters, enemySelected, playerTurn, donothingSound);
//		}
//	}
//	else if (apprentice) {
//		// Attack has 40% chance of being chosen, heal 30% and do nothing 30%
//		if (randomAttack == 0 || randomAttack == 1 || randomAttack == 2 || randomAttack == 3) {
//			Attack("Player", player, enemyCharacters, enemySelected, damageDone, playerHP, enemyHP, descriptionText, specialDescriptionText, playerTurn, score, victorySound, gameoverSound, attackSound, fightMusic);
//		}
//		else if (randomAttack == 4 || randomAttack == 5 || randomAttack == 6) {
//			if (enemyCharacters[enemySelected].getHP() >= enemyCharacters[enemySelected].getmaxHP()) {
//				EnemyTurn(player, enemyCharacters, enemySelected, healDone, damageDone, playerHP, enemyHP, descriptionText, specialDescriptionText, playerTurn, score, youngling, apprentice, master, victorySound, gameoverSound, attackSound, healSound, donothingSound, fightMusic);
//			}
//			else if (enemyCharacters[enemySelected].getHP() < enemyCharacters[enemySelected].getmaxHP()) {
//				Heal("Enemy", player, enemyCharacters, enemySelected, healDone, playerHP, enemyHP, descriptionText, playerTurn, healSound);
//			}
//		}
//		else if (randomAttack == 7 || randomAttack == 8 || randomAttack == 9) {
//			DoNothing(descriptionText, enemyCharacters, enemySelected, playerTurn, donothingSound);
//		}
//	}
//	else if (master) {
//		// Attack has 60% chance of being chosen, heal 30% and do nothing 10%
//		if (randomAttack == 0 || randomAttack == 1 || randomAttack == 2 || randomAttack == 3 || randomAttack == 4 || randomAttack == 5) {
//			Attack("Player", player, enemyCharacters, enemySelected, damageDone, playerHP, enemyHP, descriptionText, specialDescriptionText, playerTurn, score, victorySound, gameoverSound, attackSound, fightMusic);
//		}
//		else if (randomAttack == 6 || randomAttack == 7 || randomAttack == 8) {
//			if (enemyCharacters[enemySelected].getHP() >= enemyCharacters[enemySelected].getmaxHP()) {
//				EnemyTurn(player, enemyCharacters, enemySelected, healDone, damageDone, playerHP, enemyHP, descriptionText, specialDescriptionText, playerTurn, score, youngling, apprentice, master, victorySound, gameoverSound, attackSound, healSound, donothingSound, fightMusic);
//			}
//			else if (enemyCharacters[enemySelected].getHP() < enemyCharacters[enemySelected].getmaxHP()) {
//				Heal("Enemy", player, enemyCharacters, enemySelected, healDone, playerHP, enemyHP, descriptionText, playerTurn, healSound);
//			}
//		}
//		else if (randomAttack == 9) {
//			DoNothing(descriptionText, enemyCharacters, enemySelected, playerTurn, donothingSound);
//		}
//	}
//}
//
//void SetValuesFightScene(Scene& fightScene, bool& playerTurn, int& score, Button& proceedButton, Button& attackButton, Button& healButton, TextObject& specialDescriptionText) {
//	// Resets the values for the fighting scene
//	playerTurn = true;
//	score = 0;
//	fightScene.removeGameObject(proceedButton.getIdentifier());
//	fightScene.removeGameObject(attackButton.getIdentifier());
//	fightScene.removeGameObject(healButton.getIdentifier());
//	fightScene.addGameObject(attackButton);
//	fightScene.addGameObject(healButton);
//	specialDescriptionText.setText("");
//}
