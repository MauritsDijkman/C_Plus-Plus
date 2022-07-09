#pragma once

#include "fightMenu.hpp"
#include "selectMenu.hpp"
#include <fstream>
#include <stdio.h>
#include <vector>
#include <iostream>

FightMenu::FightMenu(SceneHandler& sceneHandler, SpriteObject& background, Character& player, TextObject& playerName, TextObject& playerHP, TextObject& playerAttack, TextObject& playerDefense)
{
	sceneHandler.addScene(this->scene);
	SetupScene(sceneHandler, background, player, playerName, playerHP, playerAttack, playerDefense);
}

FightMenu::~FightMenu() {}


void FightMenu::SetupScene(SceneHandler& sceneHandler, SpriteObject& background, Character& player, TextObject& playerName, TextObject& playerHP, TextObject& playerAttack, TextObject& playerDefense) {

	// Positions
	background.setPosition(sf::Vector2f(0.0f, 0.0f));

	attackButton.setPosition(sf::Vector2f(57.63f, 399.69f));
	healButton.setPosition(sf::Vector2f(403.0f, 399.69f));
	proceedButton.setPosition(sf::Vector2f(231.0f, 556.0f));
	backButton.setPosition(sf::Vector2f(951.25f, 620.94f));

	descriptionText.setFillColor(whiteColor);
	descriptionText.setCharacterSize(15);
	descriptionText.setPosition(sf::Vector2f(736.35f, 430.35f));

	specialDescriptionText.setFillColor(whiteColor);
	specialDescriptionText.setCharacterSize(15);
	specialDescriptionText.setPosition(sf::Vector2f(736.35f, 460.35f));

	playerName.setCharacterSize(23);
	playerName.setFillColor(whiteColor);
	playerName.setPosition(sf::Vector2f(272.0f + 15, 60.88f));

	playerHP.setCharacterSize(23);
	playerHP.setFillColor(whiteColor);
	playerHP.setPosition(sf::Vector2f(244.0f + 10, 99.57f));

	playerAttack.setCharacterSize(23);
	playerAttack.setFillColor(whiteColor);
	playerAttack.setPosition(sf::Vector2f(278.0f + 45, 137.57f));

	playerDefense.setCharacterSize(23);
	playerDefense.setFillColor(whiteColor);
	playerDefense.setPosition(sf::Vector2f(298.0f + 45, 179.57f));

	enemyName.setCharacterSize(25);
	enemyName.setFillColor(whiteColor);
	enemyName.setPosition(sf::Vector2f(970.75f + 15, 60.88f));

	enemyHP.setCharacterSize(25);
	enemyHP.setFillColor(whiteColor);
	enemyHP.setPosition(sf::Vector2f(941.79f + 10, 99.57f));

	enemyAttack.setCharacterSize(25);
	enemyAttack.setFillColor(whiteColor);
	enemyAttack.setPosition(sf::Vector2f(975.75f + 45, 137.57f));

	enemyDefense.setCharacterSize(25);
	enemyDefense.setFillColor(whiteColor);
	enemyDefense.setPosition(sf::Vector2f(995.73f + 45, 179.57f));

	victoryBuffer.loadFromFile("Assets/Music_Sounds/VictorySound.ogg");
	victorySound.setBuffer(victoryBuffer);

	gameoverBuffer.loadFromFile("Assets/Music_Sounds/GameOverSound.ogg");
	gameoverSound.setBuffer(gameoverBuffer);

	attackBuffer.loadFromFile("Assets/Music_Sounds/AttackSound.ogg");
	attackSound.setBuffer(attackBuffer);

	healBuffer.loadFromFile("Assets/Music_Sounds/HealSound.ogg");
	healSound.setBuffer(healBuffer);

	donothingBuffer.loadFromFile("Assets/Music_Sounds/DoNothingSound.ogg");
	donothingSound.setBuffer(donothingBuffer);

	// Adding objects to the scene
	scene.addGameObject(background);

	scene.addGameObject(backButton);
	scene.addGameObject(attackButton);
	scene.addGameObject(healButton);
	scene.addGameObject(proceedButton);

	scene.addGameObject(descriptionText);
	scene.addGameObject(specialDescriptionText);

	scene.addGameObject(playerName);
	scene.addGameObject(playerHP);
	scene.addGameObject(playerAttack);
	scene.addGameObject(playerDefense);

	scene.addGameObject(enemyName);
	scene.addGameObject(enemyHP);
	scene.addGameObject(enemyAttack);
	scene.addGameObject(enemyDefense);
}


void FightMenu::Setup_AttackButton(sf::Music& fightMusic, Character& player, TextObject& playerHP) {
	attackButton.setButtonAction([=, &fightMusic, &player, &playerHP]() {

		if (playerTurn) {
			Attack("Enemy", player, playerHP, fightMusic);

			this->scene.addGameObject(proceedButton);
			this->scene.removeGameObject(attackButton.getIdentifier());
			this->scene.removeGameObject(healButton.getIdentifier());
		}
		});
}

void FightMenu::Setup_HealButton(sf::Sound& healSound, Character& player, TextObject& playerHP) {
	healButton.setButtonAction([=, &healSound, &player, &playerHP]() {
		if (playerTurn) {
			Heal("Player", player, playerHP);

			this->scene.addGameObject(proceedButton);
			this->scene.removeGameObject(attackButton.getIdentifier());
			this->scene.removeGameObject(healButton.getIdentifier());
		}
		});
}

void FightMenu::Setup_ProceedButton(std::string highscoreFile, std::vector<int>& vectorScore, bool& youngling, bool& apprentice, bool& master, sf::Music& fightMusic, Character& player, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5, TextObject& playerHP) {
	proceedButton.setButtonAction([=, &vectorScore, &fightMusic, &player, &highscoreText1, &highscoreText2, &highscoreText3, &highscoreText4, &highscoreText5, &playerHP]() {

		this->scene.removeGameObject(proceedButton.getIdentifier());
		specialDescriptionText.setText("");

		if (enemyCharacters[enemySelected].getHP() > 0) {
			EnemyTurn(youngling, apprentice, master, fightMusic, player, playerHP);
		}
		else if (enemyCharacters[enemySelected].getHP() <= 0) {
			previousEnemy = enemyCharacters[enemySelected].getName();
			this->scene.removeGameObject(enemySprites[enemySelected].getIdentifier());
			GenerateRandomEnemy();
			score += 1;
			playerTurn = true;
		}

		if (player.getHP() > 0) {
			this->scene.addGameObject(attackButton);
			this->scene.addGameObject(healButton);
		}
		else if (player.getHP() <= 0) {
			this->scene.removeGameObject(attackButton.getIdentifier());
			this->scene.removeGameObject(healButton.getIdentifier());
			this->scene.removeGameObject(proceedButton.getIdentifier());
			vectorScore.push_back(score);
			SortScore(vectorScore, highscoreFile, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
		}
		});
}

void FightMenu::Setup_BackButton(SceneHandler& sceneHandler, Scene& previousScene, sf::Sound& backSound, sf::Music& menuMusic, sf::Music& fightMusic, std::vector<int>& vectorScore, std::string& highscoreFile, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5) {
	backButton.setButtonAction([=, &sceneHandler, &previousScene, &backSound, &menuMusic, &fightMusic, &vectorScore, &highscoreFile, &highscoreText1, &highscoreText2, &highscoreText3, &highscoreText4, &highscoreText5]() {

		backSound.play();
		menuMusic.play();
		fightMusic.stop();

		sceneHandler.addScene(previousScene);
		sceneHandler.stackScene(previousScene.getIdentifier());
		});
}

void FightMenu::SetValuesFightScene(Character& player, SpriteObject playerSprites[]) {
	// Resets the values for the fighting scene
	playerTurn = true;
	score = 0;

	this->scene.removeGameObject(proceedButton.getIdentifier());
	this->scene.removeGameObject(attackButton.getIdentifier());
	this->scene.removeGameObject(healButton.getIdentifier());

	this->scene.removeGameObject(enemySprites[enemySelected].getIdentifier());

	int characterSelected = 0;

	if (player.getName() == "Han Solo")
		characterSelected = 0;
	else if (player.getName() == "Luke Skywalker")
		characterSelected = 1;
	else if (player.getName() == "C-3PO")
		characterSelected = 2;

	this->scene.removeGameObject(playerSprites[characterSelected].getIdentifier());

	this->scene.addGameObject(attackButton);
	this->scene.addGameObject(healButton);
	specialDescriptionText.setText("");
}

void FightMenu::SetPlayer(Character& player, TextObject& playerName, TextObject& playerHP, TextObject& playerAttack, TextObject& playerDefense, SpriteObject playerSprites[]) {
	// Set the stats of the player to the text on screen
	playerName.setText(player.getName());
	playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP()));
	playerAttack.setText(std::to_string(player.getAttack()));
	playerDefense.setText(std::to_string(player.getDefense()));

	printf("Player name is set");
	std::cout << player.getName();

	// Checks which character is selected and shows that sprite on screen
	if (player.getName() == "Han Solo") {
		playerSprites[0].setPosition(sf::Vector2f(20.0f, 36.0f));
		this->scene.addGameObject(playerSprites[0]);
	}
	else if (player.getName() == "Luke Skywalker") {
		playerSprites[1].setPosition(sf::Vector2f(20.0f, 36.0f));
		this->scene.addGameObject(playerSprites[1]);
	}
	else if (player.getName() == "C-3PO") {
		playerSprites[2].setPosition(sf::Vector2f(20.0f, 36.0f));
		this->scene.addGameObject(playerSprites[2]);
	}
}

void FightMenu::GenerateRandomEnemy() {
	//Generates random number between 0 and 9
	//enemySelected = rand() % 10;
	enemySelected = rand() % (sizeof(enemyCharacters) / sizeof(Character));

	std::cout << "\nNumber of characters: " << sizeof(enemyCharacters) / sizeof(Character) << std::endl;

	// Checks if the selected enemy is the previous enemy. If so, generate a new one. If not, set the info of the selected enemy to the enemy character
	if (enemyCharacters[enemySelected].getName() == previousEnemy) {
		GenerateRandomEnemy();
	}
	else if (enemyCharacters[enemySelected].getName() != previousEnemy) {
		enemyCharacters[enemySelected].setHP(enemyCharacters[enemySelected].getmaxHP());

		enemyName.setText(enemyCharacters[enemySelected].getName());
		enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP()));
		enemyAttack.setText(std::to_string(enemyCharacters[enemySelected].getAttack()));
		enemyDefense.setText(std::to_string(enemyCharacters[enemySelected].getDefense()));

		// Shows the name of the enemy on screen in the description
		descriptionText.setFillColor(blueColor);
		descriptionText.setText("A wild " + enemyCharacters[enemySelected].getName() + " appeared!");
		previousEnemy = enemyCharacters[enemySelected].getName();

		// Checks which enemy is selected and shows that image on screen
		if (enemySelected == 0) {
			enemySprites[0].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[0]);
		}
		else if (enemySelected == 1) {
			enemySprites[1].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[1]);
		}
		else if (enemySelected == 2) {
			enemySprites[2].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[2]);
		}
		else if (enemySelected == 3) {
			enemySprites[3].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[3]);
		}
		else if (enemySelected == 4) {
			enemySprites[4].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[4]);
		}
		else if (enemySelected == 5) {
			enemySprites[5].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[5]);
		}
		else if (enemySelected == 6) {
			enemySprites[6].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[6]);
		}
		else if (enemySelected == 7) {
			enemySprites[7].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[7]);
		}
		else if (enemySelected == 8) {
			enemySprites[8].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[8]);
		}
		else if (enemySelected == 9) {
			enemySprites[9].setPosition(enemySpritePosition);
			this->scene.addGameObject(enemySprites[9]);
		}
	}
}

void FightMenu::Attack(std::string attackWho, Character& player, TextObject& playerHP, sf::Music& fightMusic) {
	attackSound.play(); // Plays attack sound

	// Checks who is being attacked
	if (attackWho == "Player") {
		int attackPower = enemyCharacters[enemySelected].getAttack() + rand() % 6; // Grabs attack of the enemy and adds a random value between 0 and 5
		int defensePower = player.getDefense() + (-2 + rand() % 4); // Grabs defense of the player and adds a random value between -1 and 3

		damageDone = std::max(attackPower - defensePower, 0); // Final damage is attackPower - defensePower, smallest number is 0

		player.setHP(player.getHP() - damageDone); // Set the new HP of the player
		playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP())); // Update the HP text
		UpdateDescription(attackWho, "-"); // Update the description with what happend
		playerTurn = true; // Player's turn

		// If the player if below 0 HP, set the HP to 0, update the text and give a game over text with the score of the player
		if (player.getHP() <= 0) {
			player.setHP(0);
			playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP()));
			specialDescriptionText.setFillColor(blueColor);
			specialDescriptionText.setText("You died with a score of " + std::to_string(score) + "!");
			playerTurn = false;
			gameoverSound.play();
			fightMusic.stop();
		}
	}
	else if (attackWho == "Enemy") {
		int attackPower = player.getAttack() + rand() % 6; // Grabs attack of the player and adds a random value between 0 and 5
		int defensePower = enemyCharacters[enemySelected].getDefense() + (-2 + rand() % 4);  // Grabs defense of the enemy and adds a random value between -1 and 3

		damageDone = std::max(attackPower - defensePower, 0); // Final damage is attackPower - defensePower, smallest number is 0

		enemyCharacters[enemySelected].setHP(enemyCharacters[enemySelected].getHP() - damageDone); // Set the new HP of the enemy
		enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP())); // Update the HP text
		UpdateDescription(attackWho, "-"); // Update the description with what happend

		// If the enemy if below 0 HP, set the HP to 0, update the text and give a message that the player is being killed.
		if (enemyCharacters[enemySelected].getHP() <= 0) {
			enemyCharacters[enemySelected].setHP(0);
			enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP()));
			specialDescriptionText.setFillColor(blueColor);
			specialDescriptionText.setText("You killed " + enemyCharacters[enemySelected].getName() + "!");
			victorySound.play();
		}
		// If the player kills an enemy, the player can start with the action with the next enemy
		else if (enemyCharacters[enemySelected].getHP() > 0) {
			playerTurn = false; // Enemy's turn
		}
	}
}

void FightMenu::Heal(std::string healWho, Character& player, TextObject& playerHP) {
	healSound.play(); // Plays heal sound

	// Checks who is being healed
	if (healWho == "Player") {
		healDone = rand() % 5; // Generates a random number between 0 and 4

		player.setHP(player.getHP() + healDone); // Update the HP of the player
		playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP())); // Update the HP text of the player
		UpdateDescription("-", healWho); // Update the description with how many HP is being recovered

		// If the player hp is above his max HP, the HP is set to max HP and the HP text is updated.
		if (player.getHP() > player.getmaxHP()) {
			player.setHP(player.getmaxHP());
			playerHP.setText(std::to_string(player.getHP()) + "/" + std::to_string(player.getmaxHP()));
		}
		playerTurn = false; // Enemy's turn
	}
	else if (healWho == "Enemy") {
		healDone = rand() % 5; // Generates a random number between 0 and 4

		enemyCharacters[enemySelected].setHP(enemyCharacters[enemySelected].getHP() + healDone);  // Update the HP of the enemy
		enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP())); // Update the HP text of the enemy
		UpdateDescription("-", healWho); // Update the description with how many HP is being recovered

		// If the player hp is above his max HP, the HP is set to max HP and the HP text is updated.
		if (enemyCharacters[enemySelected].getHP() > enemyCharacters[enemySelected].getmaxHP()) {
			enemyCharacters[enemySelected].setHP(enemyCharacters[enemySelected].getmaxHP());
			enemyHP.setText(std::to_string(enemyCharacters[enemySelected].getHP()) + "/" + std::to_string(enemyCharacters[enemySelected].getmaxHP()));
		}
		playerTurn = true; // Player's turn
	}
}

void FightMenu::DoNothing() {
	// Update the description text, plays the sound and gives the turn to the player
	descriptionText.setFillColor(redColor);
	descriptionText.setText(enemyCharacters[enemySelected].getName() + " did nothing!");
	donothingSound.play();
	playerTurn = true;
}

void FightMenu::EnemyTurn(bool youngling, bool apprentice, bool master, sf::Music& fightMusic, Character& player, TextObject& playerHP) {
	// Generated a random number between 0 and 10
	int randomAttack = rand() % 10;

	// Different difficulty systems
	if (youngling) {
		// Attack has 30% chance of being chosen, heal 30% and do nothing 40%
		if (randomAttack == 0 || randomAttack == 1 || randomAttack == 2) {
			Attack("Player", player, playerHP, fightMusic);
		}
		else if (randomAttack == 3 || randomAttack == 4 || randomAttack == 5) {
			if (enemyCharacters[enemySelected].getHP() >= enemyCharacters[enemySelected].getmaxHP()) {
				EnemyTurn(youngling, apprentice, master, fightMusic, player, playerHP);
			}
			else if (enemyCharacters[enemySelected].getHP() < enemyCharacters[enemySelected].getmaxHP()) {
				Heal("Enemy", player, playerHP);
			}
		}
		else if (randomAttack == 6 || randomAttack == 7 || randomAttack == 8 || randomAttack == 9) {
			DoNothing();
		}
	}
	else if (apprentice) {
		// Attack has 40% chance of being chosen, heal 30% and do nothing 30%
		if (randomAttack == 0 || randomAttack == 1 || randomAttack == 2 || randomAttack == 3) {
			Attack("Player", player, playerHP, fightMusic);
		}
		else if (randomAttack == 4 || randomAttack == 5 || randomAttack == 6) {
			if (enemyCharacters[enemySelected].getHP() >= enemyCharacters[enemySelected].getmaxHP()) {
				EnemyTurn(youngling, apprentice, master, fightMusic, player, playerHP);
			}
			else if (enemyCharacters[enemySelected].getHP() < enemyCharacters[enemySelected].getmaxHP()) {
				Heal("Enemy", player, playerHP);
			}
		}
		else if (randomAttack == 7 || randomAttack == 8 || randomAttack == 9) {
			DoNothing();
		}
	}
	else if (master) {
		// Attack has 60% chance of being chosen, heal 30% and do nothing 10%
		if (randomAttack == 0 || randomAttack == 1 || randomAttack == 2 || randomAttack == 3 || randomAttack == 4 || randomAttack == 5) {
			Attack("Player", player, playerHP, fightMusic);
		}
		else if (randomAttack == 6 || randomAttack == 7 || randomAttack == 8) {
			if (enemyCharacters[enemySelected].getHP() >= enemyCharacters[enemySelected].getmaxHP()) {
				EnemyTurn(youngling, apprentice, master, fightMusic, player, playerHP);
			}
			else if (enemyCharacters[enemySelected].getHP() < enemyCharacters[enemySelected].getmaxHP()) {
				Heal("Enemy", player, playerHP);
			}
		}
		else if (randomAttack == 9) {
			DoNothing();
		}
	}
}

void FightMenu::UpdateDescription(std::string attackedWho, std::string healedWho) {
	// Checks who is attacked or who is healed and displays that in the description
	if (attackedWho == "Player") {
		descriptionText.setFillColor(redColor);
		descriptionText.setText(enemyCharacters[enemySelected].getName() + " attacked you and did " + std::to_string(damageDone) + " damage!");
	}
	else if (attackedWho == "Enemy") {
		descriptionText.setFillColor(greenColor);
		descriptionText.setText("You attacked " + enemyCharacters[enemySelected].getName() + " and did " + std::to_string(damageDone) + " damage!");
	}

	if (healedWho == "Player") {
		descriptionText.setFillColor(greenColor);
		descriptionText.setText("You healed yourself with " + std::to_string(healDone) + " HP!");
	}
	else if (healedWho == "Enemy") {
		descriptionText.setFillColor(redColor);
		descriptionText.setText(enemyCharacters[enemySelected].getName() + " healed himself with " + std::to_string(healDone) + " HP!");
	}
}

void FightMenu::SortScore(std::vector<int>& vectorScore, std::string highscoreFile, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5) {
	std::ifstream highscoreStats(highscoreFile);

	std::string line; // String that is used for importing the lines

	// Checks if the file has ended, if not, import the lines and convert it to ints and push it to the vectorScore
	while (highscoreStats.peek() != EOF) {
		std::getline(highscoreStats, line);
		vectorScore.push_back(stoi(line));
	}

	// Iterators used to point at the memort addresses of the vectorscore
	// Iterators reduce the complexity and execution time of the program
	std::vector<int>::iterator ptr = vectorScore.begin();
	std::vector<int>::iterator ftr = vectorScore.end();

	// Sorts the list from big to small numbers
	sort(ptr, ftr, std::greater<int>());

	// Opening the file so that it can be edited
	std::ofstream phighscoreStats(highscoreFile);

	// Editing the file with the sorted score
	for (int i = 0; i < 5; i++) {
		phighscoreStats << std::to_string(vectorScore[i]) + "\n";
	}

	// Closing the file after it has beed edited
	phighscoreStats.close();

	// Updating the score to be displayed on screen
	UpdateScore(highscoreFile, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
}

void FightMenu::UpdateScore(std::string& highscoreFile, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5) {
	// Opening the file, reading it and setting the text to that score
	std::ifstream highscoreStats(highscoreFile);

	std::string line;
	std::string score[5];

	for (int i = 0; i < 5; i++)
	{
		std::getline(highscoreStats, line);
		score[i] = line;
	}

	highscoreText1.setText("Highscore 1: " + score[0]);
	highscoreText2.setText("Highscore 2: " + score[1]);
	highscoreText3.setText("Highscore 3: " + score[2]);
	highscoreText4.setText("Highscore 4: " + score[3]);
	highscoreText5.setText("Highscore 5: " + score[4]);

	highscoreStats.close();
}
