#include "PlayerProfile.h"

#include <cereal\types\unordered_map.hpp>
#include <cereal\types\memory.hpp>
#include <cereal\types\concepts/pair_associative_container.hpp>
#include <cereal\archives\json.hpp>
#include <cereal\types\vector.hpp>
#include <fstream>
#include <iostream>


PlayerProfile::PlayerProfile() {
	// empty
}


PlayerProfile::~PlayerProfile() {
	// empty
}

void PlayerProfile::init(const char * name, const int & initialMoney) {
	m_name = name;
	m_money = initialMoney;
}

void PlayerProfile::serialize() {
	std::stringstream os;
	cereal::JSONOutputArchive archive(os);
	archive(CEREAL_NVP(m_name, m_money, m_cavesExplored));
	std::string jsonString = os.str();
	std::cout << jsonString << std::endl;
}
