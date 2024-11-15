#pragma once

#include "Hand.h"

class Terrain : public Hand
{
public:
	Terrain(std::vector<Card*> cards, std::vector<GameObject*> targets);
	~Terrain();

	Card* getCard(int index);
};