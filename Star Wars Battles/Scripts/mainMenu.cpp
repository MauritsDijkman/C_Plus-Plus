#pragma once

#include "mainMenu.hpp"
#include <fstream>
#include <stdio.h>
#include <vector>
#include <iostream>

MainMenu::MainMenu(std::vector<int> vectorScore, SceneHandler& handler, SpriteObject& background, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5)
{
	handler.addScene(this->scene);
	SetupScene(vectorScore, background, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
}

MainMenu::~MainMenu() {}

void MainMenu::SetupScene(std::vector<int> vectorScore, SpriteObject& background, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5) {
	// Debug
	//std::cout << "SetupScene() from MainMenu is being executed\n" << std::endl;

	// File
	CheckForFile(vectorScore, "Assets/Input_Output_Files/highscores.cmgt", highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);

	// Positions
	background.setPosition(sf::Vector2f(0.0f, 0.0f));

	playButton.setPosition(sf::Vector2f(562.69f, 215.5f));
	eraseButton.setPosition(sf::Vector2f(445.47f, 325.0f));
	quitButton.setPosition(sf::Vector2f(562.69f, 434.5f));

	highscoreText1.setPosition(sf::Vector2f(100.0f, 280.0f));
	highscoreText2.setPosition(sf::Vector2f(100.0f, 300.0f));
	highscoreText3.setPosition(sf::Vector2f(100.0f, 320.0f));
	highscoreText4.setPosition(sf::Vector2f(100.0f, 340.0f));
	highscoreText5.setPosition(sf::Vector2f(100.0f, 360.0f));

	younglingButton.setPosition(sf::Vector2f(987.25f, 278.0f));
	apprenticeButton.setPosition(sf::Vector2f(987.25f, 336.59f));
	masterButton.setPosition(sf::Vector2f(987.25f, 395.69f));

	// Color
	highscoreText1.setFillColor(whiteColor);
	highscoreText2.setFillColor(whiteColor);
	highscoreText3.setFillColor(whiteColor);
	highscoreText4.setFillColor(whiteColor);
	highscoreText5.setFillColor(whiteColor);

	younglingButton.setButtonColor(redColor);
	apprenticeButton.setButtonColor(greenColor);
	masterButton.setButtonColor(redColor);

	// Adding objects to the scene
	scene.addGameObject(background);

	scene.addGameObject(highscoreText1);
	scene.addGameObject(highscoreText2);
	scene.addGameObject(highscoreText3);
	scene.addGameObject(highscoreText4);
	scene.addGameObject(highscoreText5);

	scene.addGameObject(younglingButton);
	scene.addGameObject(apprenticeButton);
	scene.addGameObject(masterButton);

	scene.addGameObject(playButton);
	scene.addGameObject(eraseButton);
	scene.addGameObject(quitButton);
}

void MainMenu::Setup_PlayButton(SceneHandler& handler, Scene& nextScene, sf::Sound& sound) {
	playButton.setButtonAction([&handler, &nextScene, &sound]() {
		sound.play();
		handler.addScene(nextScene);						// Add the next scene to the scene handler
		handler.stackScene(nextScene.getIdentifier());		// Push that new scene to the scene handler	
		//printf("%s", handler.GetCurrentScene().c_str());	// Debug
		});
}

void MainMenu::Setup_EraseButton(sf::Sound& sound, std::string& file, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5) {
	eraseButton.setButtonAction([=, &sound, &file, &highscoreText1, &highscoreText2, &highscoreText3, &highscoreText4, &highscoreText5]() { // = makes sure that the action has access to all variables / methods of the class
		// PLaying the sound
		sound.play();

		// Opening the file with scores
		std::ifstream ifStream_Highscore(file);

		//If opening the file doesn't fail, reset all the score to 0
		if (!ifStream_Highscore.fail())
		{
			std::ofstream ofStream_Highscore(file);

			for (int i = 0; i < 5; i++) {
				ofStream_Highscore << "0\n";
			}

			ofStream_Highscore.close();

			// Update the score text
			UpdateScore(file, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
		}
		});
}

void MainMenu::Setup_QuitButton(sf::RenderWindow& window, sf::Sound& sound) {
	quitButton.setButtonAction([&window, &sound]() {
		sound.play();
		window.close();
		});
}

void MainMenu::CheckForFile(std::vector<int> vectorScore, std::string highscoreFile, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5) {
	bool fileExists = false;

	// Opening the file so that it can be read
	std::ifstream ifStream_Highscore(highscoreFile);

	// Creating highscore file and adding five scores of zero if it doesn't exist. If the file exists, update the score.
	if (ifStream_Highscore.fail())
	{
		// Opening the file and edit it
		std::ofstream ofStream_Highscore(highscoreFile);

		ofStream_Highscore << "0\n";
		ofStream_Highscore << "0\n";
		ofStream_Highscore << "0\n";
		ofStream_Highscore << "0\n";
		ofStream_Highscore << "0\n";

		ofStream_Highscore.close();

		fileExists = true;
	}
	else
		fileExists = true;

	// Sort the score if the file of the scores exists
	if (fileExists) {
		SortScore(vectorScore, highscoreFile, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
		//std::cout << "\n" << "Vectorscore 0: " << vectorScore[0] << "Vectorscore 1: " << vectorScore[1] << "Vectorscore 2: " << vectorScore[2] << std::endl;
	}
}

void MainMenu::SortScore(std::vector<int> vectorScore, std::string highscoreFile, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5) {
	// Opening the file so that it can be read
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

	//std::cout << "\n" << "Vectorscore 0: " << vectorScore[0] << "Vectorscore 1: " << vectorScore[1] << "Vectorscore 2: " << vectorScore[2] << std::endl;

	// Updating the score to be displayed on screen
	UpdateScore(highscoreFile, highscoreText1, highscoreText2, highscoreText3, highscoreText4, highscoreText5);
}

void MainMenu::UpdateScore(std::string highscoreFile, TextObject& highscoreText1, TextObject& highscoreText2, TextObject& highscoreText3, TextObject& highscoreText4, TextObject& highscoreText5) {
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

void MainMenu::Setup_YounglingButton(bool& youngling, bool& apprentice, bool& master, sf::Sound& sound) {
	younglingButton.setButtonAction([=, &youngling, &apprentice, &master, &sound]() {

		youngling = true;
		apprentice = false;
		master = false;

		sound.play();

		younglingButton.setButtonColor(greenColor);
		apprenticeButton.setButtonColor(redColor);
		masterButton.setButtonColor(redColor);
		});
}

void MainMenu::Setup_ApprenticeButton(bool& youngling, bool& apprentice, bool& master, sf::Sound& sound) {
	apprenticeButton.setButtonAction([=, &youngling, &apprentice, &master, &sound]() {
		youngling = false;
		apprentice = true;
		master = false;

		sound.play();

		younglingButton.setButtonColor(redColor);
		apprenticeButton.setButtonColor(greenColor);
		masterButton.setButtonColor(redColor);
		});
}

void MainMenu::Setup_MasterButton(bool& youngling, bool& apprentice, bool& master, sf::Sound& sound) {
	masterButton.setButtonAction([=, &youngling, &apprentice, &master, &sound]() {
		youngling = false;
		apprentice = false;
		master = true;

		sound.play();

		younglingButton.setButtonColor(redColor);
		apprenticeButton.setButtonColor(redColor);
		masterButton.setButtonColor(greenColor);
		});
}
