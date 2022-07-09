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

// A vector that is used for importing the score from a file and sort it
// A vector is used to make it simpler to add a number to that array (a normal arrray of integers is not that easy)
std::vector<int> vectorScore;

// Font that is not used but is needed for the buttons and text
sf::Font font;

// SceneHandler
SceneHandler handler = SceneHandler();

// Enemy
string previousEnemy = "";

// Player
Character player = Character("Player", "playerSprite", 0, 0, 0);

TextObject playerName = TextObject("playerName", font, "Name");
TextObject playerHP = TextObject("playerHP", font, "HP");
TextObject playerAttack = TextObject("playerAttack", font, "Attack");
TextObject playerDefense = TextObject("playerDefense", font, "Defense");
//const TextObject playerDefense = TextObject("playerDefense", font, "Defense");
//playerDefense.setPosition();

SpriteObject player1Sprite = SpriteObject("player1Sprite", "Assets/PlayerCharacters/Character1.png");
SpriteObject player2Sprite = SpriteObject("player2Sprite", "Assets/PlayerCharacters/Character2.png");
SpriteObject player3Sprite = SpriteObject("player3Sprite", "Assets/PlayerCharacters/Character3.png");

SpriteObject playerSprites[3] = { player1Sprite, player2Sprite, player3Sprite };


// Highscore
TextObject highscoreText1 = TextObject("highscoreText1", font, "Highscore 1: ...");
TextObject highscoreText2 = TextObject("highscoreText2", font, "Highscore 2: ...");
TextObject highscoreText3 = TextObject("highscoreText3", font, "Highscore 3: ...");
TextObject highscoreText4 = TextObject("highscoreText4", font, "Highscore 4: ...");
TextObject highscoreText5 = TextObject("highscoreText5", font, "Highscore 5: ...");

// Backgrounds
SpriteObject backgroundMainMenu("backgroundMainMenu", "Assets/Backgrounds/Background_MainMenu.png");
SpriteObject backgroundSelectMenu("backgrounSelectMenu", "Assets/Backgrounds/Background_SelectMenu.png");
SpriteObject backgroundFightMenu("backgroundFightMenu", "Assets/Backgrounds/Background_FightScene.png");

// Scenes
MainMenu mainMenu = MainMenu(vectorScore, handler, backgroundMainMenu, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
SelectMenu selectMenu = SelectMenu(handler, backgroundSelectMenu);
FightMenu fightMenu = FightMenu(handler, backgroundFightMenu, player, playerName, playerHP, playerAttack, playerDefense);

int main()
{
	bool playerSet = false;

	// Initialize a random seed for the random function
	srand(time(NULL));

	// Values used for the dificulty setting
	bool youngling = false;
	bool apprentice = true;
	bool master = false;

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

	fightMenu.Setup_AttackButton(fightMusic, player, playerHP);
	fightMenu.Setup_HealButton(healSound, player, playerHP);
	fightMenu.Setup_ProceedButton(highscoreFile, vectorScore, youngling, apprentice, master, fightMusic, player, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5, playerHP);
	fightMenu.Setup_BackButton(handler, mainMenu.scene, backSound, menuMusic, fightMusic, vectorScore, highscoreFile, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);

#pragma endregion


	while (window.isOpen())
	{
		sf::Event newEvent;
		while (window.pollEvent(newEvent))
		{
			if (newEvent.type == sf::Event::Closed)
				window.close();
			else {
				if (handler.GetCurrentScene() == "MainMenu_Scene") {
					mainMenu.scene.handleEvent(newEvent, window);
					playerSet = false;
				}
				else if (handler.GetCurrentScene() == "SelectMenu_Scene") {
					selectMenu.scene.handleEvent(newEvent, window);
					playerSet = false;
				}
				else if (handler.GetCurrentScene() == "FightMenu_Scene") {
					fightMenu.scene.handleEvent(newEvent, window);

					if (!playerSet) {
						fightMenu.SetValuesFightScene(player, playerSprites);
						fightMenu.SetPlayer(player, playerName, playerHP, playerAttack, playerDefense, playerSprites);
						fightMenu.GenerateRandomEnemy();
						playerSet = true;
					}
				}
			}
		}

		window.clear(sf::Color::White);
		handler.update();
		handler.render(window);
		window.display();
	}

	// Returns 0 because main is an int that requires a return
	return 0;
}
