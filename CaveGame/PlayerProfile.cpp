#include "PlayerProfile.h"
#include <rapidjson\filewritestream.h>
#include <rapidjson\writer.h>
#include <cstdio>
#include <windows.h>
#include <string>
#include <rapidjson\document.h>
#include <iostream>
#include <fstream>


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

void PlayerProfile::serialize() {
	char result[128];
	std::string currentDir = std::string(result, GetCurrentDirectoryA(MAX_PATH, result));
	std::cout << currentDir << std::endl;
	
	std::string filepath = currentDir + "\\data\\" + m_name + ".json";
	std::cout << filepath << std::endl;

	rapidjson::StringBuffer strBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
	writer.StartObject();
	writer.Key("name");
	writer.String(m_name.c_str());
	writer.Key("money");
	writer.Int(m_money);
	writer.Key("caves");
	writer.Int(m_cavesExplored);
	writer.EndObject();

	std::cout << strBuffer.GetString() << std::endl;
	// TODO: serialize characters

	std::ofstream out(filepath);
	out << strBuffer.GetString();
	out.close();
}
