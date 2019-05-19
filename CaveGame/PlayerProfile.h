#pragma once

#include <map>
#include <vector>
#include "Character.h"

class PlayerProfile
{
public:
	PlayerProfile();
	~PlayerProfile();

	void init(const char* name, const int& initialMoney);
	
	int getMoney() { return m_money; }
	int getCavesExplored() { return m_cavesExplored; }
	
	void setMoney(const int& money) { m_money = money; }
	void offsetMoney(const int& offset) { m_money += offset; }

	void serialize();
	void deserialize();


private:
	const char* m_name;
	int m_cavesExplored;
	int m_money = 0;
	std::map<int, Character> m_characters;
	
};

