#pragma once

#include "Player.h"

class GameManager
{
public:
	~GameManager();
	GameManager(GameManager& other) = delete;
	void operator=(GameManager& other) = delete;
	static GameManager* getInstance();

	void initialize();

private:
	std::vector<GameObject*> createDeckTargets(bool player1, float z_offset);
	std::vector<GameObject*> createHandTargets(bool player1, float z_offset);

	void addDebugMesh(GameObject* target, bool player1, bool deck);

private:
	GameManager();
	static GameManager* m_instance;

	Player* m_player_1;
	Player* m_player_2;
};