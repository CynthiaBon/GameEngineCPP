#include "Player.h"

Player::Player(std::vector<Card*> cards,
	std::vector<GameObject*> deck_targets,
	std::vector<GameObject*> hand_targets,
	std::vector<GameObject*> terrain_targets,
	std::vector<GameObject*> graveyard_targets)
{
	m_deck = new Deck(cards, deck_targets);
	m_hand = new Hand(std::vector<Card*>(), hand_targets);
	m_terrain = new Terrain(std::vector<Card*>(), terrain_targets);
	m_graveyard = new Deck(std::vector<Card*>(), graveyard_targets);

	for (int i = 0; i < cards.size(); i++)
	{
		cards[i]->moveAndRotateTo(deck_targets[0], 1.0f);
	}
}

Player::~Player()
{
}

void Player::draw()
{
	if (m_deck->getCardsCount() == 0)
		return;

	Card* card = m_deck->popCard(0);
	m_hand->addCard(card);
}

void Player::handToTerrain(int index)
{
	if (m_hand->getCardsCount() <= index)
		return;

	Card* card = m_hand->popCard(index);
	m_hand->shiftCards();
	m_terrain->addCard(card);
}

void Player::terrainToGraveyard(int index)
{
	if (m_terrain->getCardsCount() <= index)
		return;

	Card* card = m_terrain->popCard(index);
	m_terrain->shiftCards();
	m_graveyard->addCard(card);
}

void Player::handToGraveyard(int index)
{
	if (m_hand->getCardsCount() <= index)
		return;

	Card* card = m_hand->popCard(index);
	m_hand->shiftCards();
	m_graveyard->addCard(card);
}

int Player::getHandCount()
{
	return m_hand->getCardsCount();;
}

int Player::getTerrainCount()
{
	return m_terrain->getCardsCount();
}

Card* Player::getTerrainCard(int index)
{
	return m_terrain->getCard(index);
}

bool Player::hasLost()
{
	return m_deck->getCardsCount() == 0 && m_hand->getCardsCount() == 0 && m_terrain->getCardsCount() == 0;
}
