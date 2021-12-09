#include "soundHandler.hpp"

SoundHandler::SoundHandler(std::string identifier, sf::SoundBuffer buffer, std::string soundFile, sf::Sound sound) : identifier(identifier), buffer(buffer), soundFile(soundFile), sound(sound)
{
	// Loads the sound from the file and sets the sound buffer
	this->buffer.loadFromFile(this->soundFile);
	this->sound.setBuffer(this->buffer);
}

// Deletes everything after code has been runned
SoundHandler::~SoundHandler() {}

void SoundHandler::update() {}

// Returns a string with the identifier of the soundhandler
std::string SoundHandler::getIdentifier() const {
	return this->identifier;
}

// Sets up the sound and plays it
void SoundHandler::PlaySound() {
	this->sound.play();
}

// Stops the sound from playing
void SoundHandler::StopSound() {
	this->sound.stop();
}

// Pauses the sound
void SoundHandler::PauseSound() {
	this->sound.pause();
}
