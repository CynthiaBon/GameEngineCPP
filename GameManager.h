#pragma once

#include "Player.h"
#include "Engine/Includes/GameEngine.h"
#include <random>

class GameManager
{
public:
	~GameManager();
	GameManager(GameManager& other) = delete;
	void operator=(GameManager& other) = delete;
	static GameManager* getInstance();

	void initialize();
	void gameLoop();

private:
	std::vector<GameObject*> createDeckTargets(bool player1, float z_offset);
	std::vector<GameObject*> createHandTargets(bool player1, float z_offset);

	Card* createCard();

	void addDebugMesh(GameObject* target, bool player1, bool deck);

	void discardCard();
	void hand();
	void attack();

	void playSpawnAnimation();

	void player2ActionTimer();
	int getPlayer2RandomIndex(int max);
	bool isKeyPressed(int key);

	void manageAttack(int attack_card_index, int target_index);

	GameManager();
private:
	static GameManager* m_instance;

	Player* m_player_1;
	Player* m_player_2;

	bool m_player_1_turn;
	int m_turn_state;
	int m_selected_card;

	int m_current_key_pressed;

	float m_player2_action_timer;
	bool m_can_player2_play;

	float m_spawn_animation_timer;
	Card* m_card_to_spawn;

	float m_exit_timer;

	std::mt19937 m_rng;
	std::uniform_int_distribution<uint32_t> m_rand1;
	std::uniform_int_distribution<uint32_t> m_rand2;
	std::uniform_int_distribution<uint32_t> m_rand3;
	std::uniform_int_distribution<uint32_t> m_rand4;
	std::uniform_int_distribution<uint32_t> m_rand5;
	std::uniform_int_distribution<uint32_t> m_rand9;
};