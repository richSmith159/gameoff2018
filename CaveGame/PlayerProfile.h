#pragma once

#include <map>
#include <vector>
#include <string>
#include "Miner.h"

class PlayerProfile
{
public:
	PlayerProfile();
	~PlayerProfile();

	void init(std::string name, const int& initialMoney);
	
	std::string getName() { return m_name; }
	int getMoney() { return m_money; }
	int getCavesExplored() { return m_cavesExplored; }
	
	void setName(const std::string& newName) { m_name = newName; }
	void setCavesExplored(const int& newValue) { m_cavesExplored = newValue; }
	void setMoney(const int& money) { m_money = money; }
	void offsetMoney(const int& offset) { m_money += offset; }

	void serialize();
	void deserialize(std::string name);


private:
	std::string m_name;
	int m_cavesExplored;
	int m_money = 0;
	std::map<int, Miner> m_miners;
	
};
