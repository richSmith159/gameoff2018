#include "PlayerProfile.h"


PlayerProfile::PlayerProfile() {
	// empty
}


PlayerProfile::~PlayerProfile() {
	// empty
}

void PlayerProfile::init(std::string name, const int & initialMoney) {
	m_name = name;
	m_money = initialMoney;
}
