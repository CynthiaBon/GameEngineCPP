#pragma once

#include "Terrain.h"

class Player
{
public:
	Player(std::vector<Card*> cards,
		std::vector<GameObject*> deck_targets,
		std::vector<GameObject*> hand_targets,
		std::vector<GameObject*> terrain_targets,
		std::vector<GameObject*> graveyard_targets
	);
	~Player();

	void draw();
	void handToTerrain(int index);
	void terrainToGraveyard(int index);

private:
	Deck* m_deck;
	Hand* m_hand;
	Terrain* m_terrain;
	Deck* m_graveyard;
};