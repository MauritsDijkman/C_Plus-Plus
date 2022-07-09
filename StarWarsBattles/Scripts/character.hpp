#pragma once

#include <string>

class Character {
	// Standard private values that cannot be called
private:
	std::string name;
	std::string spriteFile;
	int hp;
	int attack;
	int defense;

	// Own made extra value that cannot be called
private:
	int maxHP;

	// These functions can be called when creating a character
public:
	Character(std::string name, std::string spriteFile,
		int hp, int attack, int defense);
	~Character();


	void setAttack(int attack);
	int getAttack() const;

	void setDefense(int defense);
	int getDefense() const;

	void setHP(int hp);
	int getHP() const;

	void setmaxHP(int maxHP);
	int getmaxHP() const;

	void setName(std::string name);
	std::string getName() const;

	std::string getSpriteFile() const;
};
