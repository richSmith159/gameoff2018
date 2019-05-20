#pragma once

#include <map>
#include <vector>
#include <string>
#include "Character.h"

class PlayerProfile
{
public:
	PlayerProfile();
	~PlayerProfile();

	void init(std::string name, const int& initialMoney);
	
	int getMoney() { return m_money; }
	int getCavesExplored() { return m_cavesExplored; }
	
	void setMoney(const int& money) { m_money = money; }
	void offsetMoney(const int& offset) { m_money += offset; }

	void serialize();
	void deserialize(std::string name);


private:
	std::string m_name;
	int m_cavesExplored;
	int m_money = 0;
	std::map<int, Character> m_characters;
	
};
