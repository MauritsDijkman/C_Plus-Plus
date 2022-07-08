#pragma once

#include <SFML/Audio.hpp>
#include <string>

class SoundHandler {
private:
	sf::SoundBuffer buffer;
	std::string soundFile;
	sf::Sound sound;
private:
	const std::string identifier; // Not changable
public:
	SoundHandler(std::string identifier, sf::SoundBuffer buffer, std::string soundFile, sf::Sound sound);
	~SoundHandler();
public:
	void update();

	void PlaySound();
	void StopSound();
	void PauseSound();

	std::string getIdentifier() const;
};
