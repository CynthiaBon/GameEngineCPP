#include "Terrain.h"

Terrain::Terrain(std::vector<Card*> cards, std::vector<GameObject*> targets) : Hand(cards, targets)
{
}

Terrain::~Terrain()
{
}

Card* Terrain::getCard(int index)
{
	return m_cards[index];
}
