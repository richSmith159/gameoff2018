#pragma once

#include "PlayerProfile.h"

class PlayerSerializer
{
public:
	PlayerSerializer();
	~PlayerSerializer();
	void serialize(PlayerProfile* player);
	void initPlayerFromFile(PlayerProfile* player);
};

