#pragma once

#include "Deck.h"

class Hand : public Deck
{
public:
	Hand(std::vector<Card*> cards, std::vector<GameObject*> targets);
	~Hand();

	void addCard(Card* card) override;
	void shiftCards();
};