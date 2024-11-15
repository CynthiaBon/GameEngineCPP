#pragma once

#include <vector>
#include "Card.h"

class Deck
{
public:
	Deck(std::vector<Card*> cards, std::vector<GameObject*> targets);
	~Deck();

	Card* popCard(int index);
	int getCardsCount();
	virtual void addCard(Card* card);

protected:
	std::vector<Card*> m_cards;
	std::vector<GameObject*> m_targets;
};