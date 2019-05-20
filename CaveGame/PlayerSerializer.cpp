#include "PlayerSerializer.h"

#include <rapidjson\filewritestream.h>
#include <rapidjson\istreamwrapper.h>
#include <rapidjson\writer.h>
#include <cstdio>
#include <windows.h>
#include <string>
#include <rapidjson\document.h>
#include <iostream>
#include <fstream>



PlayerSerializer::PlayerSerializer()
{
}


PlayerSerializer::~PlayerSerializer()
{
}

void PlayerSerializer::serialize(PlayerProfile * player) {
	char result[128];
	std::string currentDir = std::string(result, GetCurrentDirectoryA(MAX_PATH, result));
	std::string filepath = currentDir + "\\data\\" + player->getName() + ".json";

	rapidjson::StringBuffer strBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
	writer.StartObject();
	writer.Key("name");
	writer.String(player->getName().c_str());
	writer.Key("money");
	writer.Int(player->getMoney());
	writer.Key("caves_explored");
	writer.Int(player->getCavesExplored());
	writer.EndObject();

	std::ofstream out(filepath);
	out << strBuffer.GetString();
	out.close();

}

void PlayerSerializer::initPlayerFromFile(PlayerProfile * player) {
	char result[128];
	std::string currentDir = std::string(result, GetCurrentDirectoryA(MAX_PATH, result));
	std::string filepath = currentDir + "\\data\\" + player->getName() + ".json";

	std::ifstream stream(filepath);
	rapidjson::IStreamWrapper wrapper(stream);
	rapidjson::Document document;
	document.ParseStream(wrapper);

	player->setName(document["name"].GetString());
	player->setMoney(document["money"].GetInt());
	player->setCavesExplored(document["caves_explored"].GetInt());

}
