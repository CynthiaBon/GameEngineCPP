#include "Deck.h"

Deck::Deck(std::vector<Card*> cards, std::vector<GameObject*> targets)
{
	m_cards = cards;
	m_targets = targets;
}

Deck::~Deck()
{
}

Card* Deck::popCard(int index)
{
	int count = 0;
	Card* card = nullptr;
	for (std::vector<Card*>::iterator it = m_cards.begin(); it < m_cards.end(); it++)
	{
		if (count == index)
		{
			card = m_cards[count];
			m_cards.erase(it);
			break;
		}
		count += 1;
	}
	return card;
}

int Deck::getCardsCount()
{
	return m_cards.size();
}

void Deck::addCard(Card* card)
{
	card->moveAndRotateTo(m_targets[0], 1.0f);
	m_cards.push_back(card);
}
