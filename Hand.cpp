#include "Hand.h"

Hand::Hand(std::vector<Card*> cards, std::vector<GameObject*> targets) : Deck(cards, targets)
{
}

Hand::~Hand()
{
}

void Hand::addCard(Card* card)
{
	int card_count = getCardsCount();
	card->moveAndRotateTo(m_targets[card_count], 10.0f);
	m_cards.push_back(card);
}
