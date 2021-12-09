#include "character.hpp"

#include <algorithm>

Character::Character(std::string name, std::string spriteFile, int hp, int attack, int defense) :
	name(name), spriteFile(spriteFile), hp(hp), attack(attack), defense(defense)
{
	maxHP = hp; // Sets the maxHP automaticly to the given HP when the character is created
}

// Deletes everything after code has been runned
Character::~Character() { }

// Sets the attack value to the given value
void Character::setAttack(int attack) {
	this->attack = attack;
}

// Returns an int with the value of attack
int Character::getAttack() const {
	return this->attack;
}

// Sets the defense to the given value
void Character::setDefense(int defense) {
	this->defense = defense;
}

// Returns an int with the value of defense
int Character::getDefense() const {
	return this->defense;
}

// Sets the HP to the given value
void Character::setHP(int hp) {
	this->hp = hp;
}

// Returns an int with the value of HP
int Character::getHP() const {
	return this->hp;
}

// Sets the max HP to the given value
void Character::setmaxHP(int maxHP) {
	this->maxHP = maxHP;
}

// Returns an int with the value of max HP
int Character::getmaxHP() const {
	return this->maxHP;
}

// Sets the name to the given string
void Character::setName(std::string name) {
	this->name = name;
}

// Returns a string with the name of the character
std::string Character::getName() const {
	return this->name;
}

// Returns a string with the sprite file
std::string Character::getSpriteFile() const {
	return this->spriteFile;
}
