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
		cards[i]->getGameObject()->getTransform()->setPosition(deck_targets[0]->getTransform()->getPosition());
		cards[i]->getGameObject()->getTransform()->setRotation(deck_targets[0]->getTransform()->getEulerRotation());
	}
}

Player::~Player()
{
}

void Player::draw()
{
	Card* card = m_deck->popCard(0);
	m_hand->addCard(card);
}

void Player::handToTerrain(int index)
{
	Card* card = m_hand->popCard(index);
	m_terrain->addCard(card);
}

void Player::terrainToGraveyard(int index)
{
	Card* card = m_terrain->popCard(index);
	m_graveyard->addCard(card);
}
