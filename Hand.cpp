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
	card->moveAndRotateTo(m_targets[card_count], 1.0f);
	m_cards.push_back(card);
}

void Hand::shiftCards()
{
	for (int i = 0; i < getCardsCount(); i++)
	{
		m_cards[i]->moveAndRotateTo(m_targets[i], 0.5f);
	}
}
