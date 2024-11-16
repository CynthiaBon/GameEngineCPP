#include "GameManager.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
{
	m_player_1 = nullptr;
	m_player_2 = nullptr;
	m_player_1_turn = true;
	m_turn_state = 0;
	m_selected_card = -1;
	m_current_key_pressed = -1;
	m_player2_action_timer = 0.0f;
	m_can_player2_play = true;
	m_exit_timer = 0.0f;
	m_spawn_animation_timer = 0.0f;
	m_card_to_spawn = nullptr;

	m_rng = std::mt19937();
	m_rng.seed((unsigned)time(0));
	m_rand1 = std::uniform_int_distribution<uint32_t>(0, 1);
	m_rand2 = std::uniform_int_distribution<uint32_t>(0, 2);
	m_rand3 = std::uniform_int_distribution<uint32_t>(0, 3);
	m_rand4 = std::uniform_int_distribution<uint32_t>(0, 4);
	m_rand5 = std::uniform_int_distribution<uint32_t>(0, 5);
	m_rand9 = std::uniform_int_distribution<uint32_t>(1, 9);
}

GameManager::~GameManager()
{
}

GameManager* GameManager::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new GameManager();
	return m_instance;
}

void GameManager::initialize()
{
	//Player 1
	std::vector<Card*> deck_1 = std::vector<Card*>();
	for (int i = 0; i < 15; i++)
	{
		deck_1.push_back(createCard());
	}

	std::vector<GameObject*> deck_targets_1 = createDeckTargets(true, 0.0f);
	std::vector<GameObject*> hand_targets_1 = createHandTargets(true, 0.0f);
	std::vector<GameObject*> terrain_targets_1 = createHandTargets(true, 2.0f);
	std::vector<GameObject*> graveryard_targets_1 = createDeckTargets(true, 2.0f);
	m_player_1 = new Player(deck_1, deck_targets_1, hand_targets_1, terrain_targets_1, graveryard_targets_1);
	for (int i = 0; i < 3; i++)
	{
		m_player_1->draw();
	}

	//Player 2
	std::vector<Card*> deck_2 = std::vector<Card*>();
	for (int i = 0; i < 15; i++)
	{
		deck_2.push_back(createCard());
	}

	std::vector<GameObject*> deck_targets_2 = createDeckTargets(false, 0.0f);
	std::vector<GameObject*> hand_targets_2 = createHandTargets(false, 0.0f);
	std::vector<GameObject*> terrain_targets_2 = createHandTargets(false, 2.0f);
	std::vector<GameObject*> graveryard_targets_2 = createDeckTargets(false, 2.0f);
	m_player_2 = new Player(deck_2, deck_targets_2, hand_targets_2, terrain_targets_2, graveryard_targets_2);
	for (int i = 0; i < 3; i++)
	{
		m_player_2->draw();
	}
}

void GameManager::gameLoop()
{
	if (m_player_1->hasLost() || m_player_2->hasLost())
	{
		m_exit_timer += GameEngine::getDeltaTime();
		if (m_exit_timer >= 2.0f)
			GameEngine::getInstance()->exit();
		return;
	}

	playSpawnAnimation();
	player2ActionTimer();

	if (m_turn_state == 0)
	{
		if (m_player_1_turn)
		{
			m_player_1->draw();
		}
		else
		{
			m_player_2->draw();
			m_can_player2_play = false;
			m_player2_action_timer = 0.0f;
		}
		m_turn_state += 1;
	}
	else if (m_turn_state == 1)
	{
		if (m_player_1_turn)
		{
			if (m_player_1->getHandCount() == 6)
				discardCard();
			else
				hand();
		}
		else if (m_can_player2_play)
		{
			if (m_player_2->getHandCount() == 6)
				m_player_2->handToGraveyard(m_rand5(m_rng));

			if (m_player_2->getTerrainCount() != 5 && m_player_2->getHandCount() != 0)
			{
				int index = getPlayer2RandomIndex(m_player_2->getHandCount());
				m_player_2->handToTerrain(index);
				m_card_to_spawn = m_player_2->getTerrainCard(m_player_2->getTerrainCount() - 1);
				m_can_player2_play = false;
				m_player2_action_timer = 0.0f;
			}
			m_turn_state += 1;
		}
	}
	else if (m_turn_state == 2)
	{
		if (m_player_1_turn)
		{
			attack();
		}
		else if (m_can_player2_play)
		{
			if (m_player_1->getTerrainCount() != 0 && m_player_2->getTerrainCount() != 0)
			{
				int attack_index = getPlayer2RandomIndex(m_player_2->getTerrainCount());
				int target_index = getPlayer2RandomIndex(m_player_1->getTerrainCount());
				manageAttack(attack_index, target_index);
			}
			m_turn_state += 1;
		}
	}
	else if (m_turn_state == 3)
	{
		m_player_1_turn = !m_player_1_turn;
		m_turn_state = 0;
	}
}

std::vector<GameObject*> GameManager::createDeckTargets(bool player1, float z_offset)
{
	z_offset = player1 ? -z_offset : z_offset;
	std::vector<GameObject*> targets = std::vector<GameObject*>();

	GameObject* deck_target = GameEngine::createGameObject("Deck target");
	glm::vec3 deck_target_pos = glm::vec3(5.0f, 0.0f, 3.0f);
	if (!player1)
		deck_target_pos = -deck_target_pos;
	deck_target_pos.z += z_offset;
	deck_target->getTransform()->setPosition(deck_target_pos);

	glm::vec3 rotation = glm::vec3(0.0f, player1 ? 0.0f : 180.0f, z_offset == 0.0f ? 180.0f : 0.0f);
	deck_target->getTransform()->setRotation(rotation);

	targets.push_back(deck_target);

	//addDebugMesh(deck_target, player1, true);

	return targets;
}

std::vector<GameObject*> GameManager::createHandTargets(bool player1, float z_offset)
{
	z_offset = player1 ? -z_offset : z_offset;
	std::vector<GameObject*> targets = std::vector<GameObject*>();

	for (int i = 0; i < 6; i++)
	{
		GameObject* hand_target = GameEngine::createGameObject("Hand target");
		float card_offset = i * 1.2f * (player1 ? 1.0f : -1.0f);
		float x = (player1 ? -2.4f : 2.4f) + card_offset;
		glm::vec3 hand_target_pos = glm::vec3(x, 0.0f, (player1 ? 3.5f : -3.5f) + z_offset);

		hand_target->getTransform()->setPosition(hand_target_pos);
		glm::vec3 rotation = glm::vec3(0.0f, player1 ? 0.0f : 180.0f, !player1 && z_offset == 0 ? 180.0f : 0.0f);
		hand_target->getTransform()->setRotation(rotation);
		targets.push_back(hand_target);

		//addDebugMesh(hand_target, player1, false);
	}

	return targets;
}

Card* GameManager::createCard()
{
	GameObject* card = GameEngine::createGameObject("Card");
	Card* card_component = new Card(card, "Monster", m_rand9(m_rng), m_rand9(m_rng), "Images/Card.png");
	return card_component;
}

void GameManager::addDebugMesh(GameObject* target, bool player1, bool deck)
{
	Shader* shader = Shader::Find("Base Shader");
	glm::vec3 color = player1 ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
	color.g = deck ? 1.0f : 0.0f;
	Material* material = new Material(shader, color);
	Mesh* mesh = OBJLoader::loadObj("Meshes/Sphere.obj");
	MeshRenderer* mesh_renderer = new MeshRenderer(target, mesh, material);
	target->getTransform()->setScale(glm::vec3(0.1f));
}

void GameManager::discardCard()
{
	if (isKeyPressed(GLFW_KEY_1))
	{
		m_player_1->handToGraveyard(0);
	}
	else if (isKeyPressed(GLFW_KEY_2))
	{
		m_player_1->handToGraveyard(1);
	}
	else if (isKeyPressed(GLFW_KEY_3))
	{
		m_player_1->handToGraveyard(2);
	}
	else if (isKeyPressed(GLFW_KEY_4))
	{
		m_player_1->handToGraveyard(3);
	}
	else if (isKeyPressed(GLFW_KEY_5))
	{
		m_player_1->handToGraveyard(4);
	}
	else if (isKeyPressed(GLFW_KEY_6))
	{
		m_player_1->handToGraveyard(5);
	}
}

void GameManager::hand()
{
	if (m_player_1->getTerrainCount() == 5 || m_player_1->getHandCount() == 0)
	{
		m_turn_state += 1;
		return;
	}

	if (isKeyPressed(GLFW_KEY_ENTER))
	{
		m_turn_state += 1;
		return;
	}

	if (isKeyPressed(GLFW_KEY_1))
	{
		m_player_1->handToTerrain(0);
		m_card_to_spawn = m_player_1->getTerrainCard(m_player_1->getTerrainCount() - 1);
		m_turn_state += 1;
	}
	else if (isKeyPressed(GLFW_KEY_2))
	{
		m_player_1->handToTerrain(1);
		m_turn_state += 1;
	}
	else if (isKeyPressed(GLFW_KEY_3))
	{
		m_player_1->handToTerrain(2);
		m_turn_state += 1;
	}
	else if (isKeyPressed(GLFW_KEY_4))
	{
		m_player_1->handToTerrain(3);
		m_turn_state += 1;
	}
	else if (isKeyPressed(GLFW_KEY_5))
	{
		m_player_1->handToTerrain(4);
		m_turn_state += 1;
	}
}

void GameManager::attack()
{
	if (m_player_1->getTerrainCount() == 0 || m_player_2->getTerrainCount() == 0)
	{
		m_turn_state += 1;
		return;
	}

	if (isKeyPressed(GLFW_KEY_ENTER))
	{
		m_turn_state += 1;
		m_player_1->getTerrainCard(m_selected_card)->setSelected(false);
		m_selected_card = -1;
		return;
	}

	if (m_selected_card == -1)
	{
		if (isKeyPressed(GLFW_KEY_1) && m_player_1->getTerrainCount() > 0)
			m_selected_card = 0;
		else if (isKeyPressed(GLFW_KEY_2) && m_player_1->getTerrainCount() > 1)
			m_selected_card = 1;
		else if (isKeyPressed(GLFW_KEY_3) && m_player_1->getTerrainCount() > 2)
			m_selected_card = 2;
		else if (isKeyPressed(GLFW_KEY_4) && m_player_1->getTerrainCount() > 3)
			m_selected_card = 3;
		else if (isKeyPressed(GLFW_KEY_5) && m_player_1->getTerrainCount() > 4)
			m_selected_card = 4;

		if (m_selected_card != -1)
			m_player_1->getTerrainCard(m_selected_card)->setSelected(true);
	}
	else
	{
		if (isKeyPressed(GLFW_KEY_1) && m_player_2->getTerrainCount() > 0)
		{
			manageAttack(m_selected_card, 0);
			m_player_1->getTerrainCard(m_selected_card)->setSelected(false);
			m_selected_card = -1;
			m_turn_state += 1;
		}
		else if (isKeyPressed(GLFW_KEY_2) && m_player_2->getTerrainCount() > 1)
		{
			manageAttack(m_selected_card, 1);
			m_player_1->getTerrainCard(m_selected_card)->setSelected(false);
			m_selected_card = -1;
			m_turn_state += 1;
		}
		else if (isKeyPressed(GLFW_KEY_3) && m_player_2->getTerrainCount() > 2)
		{
			manageAttack(m_selected_card, 2);
			m_player_1->getTerrainCard(m_selected_card)->setSelected(false);
			m_selected_card = -1;
			m_turn_state += 1;
		}
		else if (isKeyPressed(GLFW_KEY_4) && m_player_2->getTerrainCount() > 3)
		{
			manageAttack(m_selected_card, 3);
			m_player_1->getTerrainCard(m_selected_card)->setSelected(false);
			m_selected_card = -1;
			m_turn_state += 1;
		}
		else if (isKeyPressed(GLFW_KEY_5) && m_player_2->getTerrainCount() > 4)
		{
			manageAttack(m_selected_card, 4);
			m_player_1->getTerrainCard(m_selected_card)->setSelected(false);
			m_selected_card = -1;
			m_turn_state += 1;
		}
	}
}

void GameManager::playSpawnAnimation()
{
	if (m_card_to_spawn == nullptr)
		return;

	m_spawn_animation_timer += GameEngine::getDeltaTime();
	if (m_spawn_animation_timer >= 1.0f)
	{
		m_card_to_spawn->playSpawnEffect();
		m_card_to_spawn = nullptr;
		m_spawn_animation_timer = 0.0f;
	}
}

void GameManager::player2ActionTimer()
{
	if (m_player_1_turn || m_can_player2_play)
		return;

	m_player2_action_timer += GameEngine::getDeltaTime();
	if (m_player2_action_timer >= 1.0f)
		m_can_player2_play = true;
}

int GameManager::getPlayer2RandomIndex(int max)
{
	if (max == 1)
		return 0;
	else if (max == 2)
		return m_rand1(m_rng);
	else if (max == 3)
		return m_rand2(m_rng);
	else if (max == 4)
		return m_rand3(m_rng);
	return m_rand4(m_rng);
}

bool GameManager::isKeyPressed(int key)
{
	if (m_current_key_pressed != -1)
	{
		if (GameEngine::getInstance()->isKeyPressed(m_current_key_pressed))
			return false;
		else
			m_current_key_pressed = -1;
	}

	if (GameEngine::getInstance()->isKeyPressed(key))
	{
		m_current_key_pressed = key;
		return true;
	}

	return false;
}

void GameManager::manageAttack(int attack_card_index, int target_index)
{
	if (m_player_1_turn)
	{
		Card* attack_card = m_player_1->getTerrainCard(attack_card_index);
		Card* target_card = m_player_2->getTerrainCard(target_index);
		target_card->takeDamage(attack_card->getAttack());
		if (target_card->isDead())
			m_player_2->terrainToGraveyard(target_index);
	}
	else
	{
		Card* attack_card = m_player_2->getTerrainCard(attack_card_index);
		Card* target_card = m_player_1->getTerrainCard(target_index);
		target_card->takeDamage(attack_card->getAttack());
		if (target_card->isDead())
			m_player_1->terrainToGraveyard(target_index);
	}
}
