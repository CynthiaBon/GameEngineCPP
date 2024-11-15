#include "GameManager.h"

GameManager* GameManager::m_instance = nullptr;

GameManager::GameManager()
{
	initialize();
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
	GameObject* card_1 = GameEngine::createGameObject("Card1");
	Card* card_component_1 = new Card(card_1, "Monster 1", 1, 3, "Images/Card.png");
	deck_1.push_back(card_component_1);

	std::vector<GameObject*> deck_targets_1 = createDeckTargets(true, 0.0f);
	std::vector<GameObject*> hand_targets_1 = createHandTargets(true, 0.0f);
	std::vector<GameObject*> terrain_targets_1 = createHandTargets(true, 2.0f);
	std::vector<GameObject*> graveryard_targets_1 = createDeckTargets(true, 2.0f);
	m_player_1 = new Player(deck_1, deck_targets_1, hand_targets_1, terrain_targets_1, graveryard_targets_1);

	//Player 2
	std::vector<Card*> deck_2 = std::vector<Card*>();
	GameObject* card_2 = GameEngine::createGameObject("Card2");
	Card* card_component_2 = new Card(card_2, "Monster 2", 2, 1, "Images/Card.png");
	deck_2.push_back(card_component_2);

	std::vector<GameObject*> deck_targets_2 = createDeckTargets(false, 0.0f);
	std::vector<GameObject*> hand_targets_2 = createHandTargets(false, 0.0f);
	std::vector<GameObject*> terrain_targets_2 = createHandTargets(false, 2.0f);
	std::vector<GameObject*> graveryard_targets_2 = createDeckTargets(false, 2.0f);
	m_player_2 = new Player(deck_2, deck_targets_2, hand_targets_2, terrain_targets_2, graveryard_targets_2);
}

std::vector<GameObject*> GameManager::createDeckTargets(bool player1, float z_offset)
{
	z_offset = player1 ? -z_offset : z_offset; //Inverse
	std::vector<GameObject*> targets = std::vector<GameObject*>();

	GameObject* deck_target = GameEngine::createGameObject("Deck target");
	glm::vec3 deck_target_pos = glm::vec3(5.0f, 0.0f, 3.0f); //Modify
	if (!player1)
		deck_target_pos = -deck_target_pos;
	deck_target_pos.z += z_offset; //Add
	deck_target->getTransform()->setPosition(deck_target_pos);
	if (z_offset == 0.0f)
		deck_target->getTransform()->setRotation(0.0f, 0.0f, 180.0f);

	targets.push_back(deck_target);

	//addDebugMesh(deck_target, player1, true);
	return targets;
}

std::vector<GameObject*> GameManager::createHandTargets(bool player1, float z_offset)
{
	z_offset = player1 ? -z_offset : z_offset; //Inverse
	std::vector<GameObject*> targets = std::vector<GameObject*>();

	for (int i = 0; i < 6; i++)
	{
		GameObject* hand_target = GameEngine::createGameObject("Hand target");
		float card_offset = i * 1.2f * (player1 ? 1.0f : -1.0f); //()
		float x = (player1 ? -2.4f : 2.4f) + card_offset; //()
		glm::vec3 hand_target_pos = glm::vec3(x, 0.0f, (player1 ? 3.5f : -3.5f) + z_offset); //Modify

		hand_target->getTransform()->setPosition(hand_target_pos);
		if (!player1)
			hand_target->getTransform()->setRotation(0.0f, 0.0f, 180.0f);
		targets.push_back(hand_target);
		//addDebugMesh(hand_target, player1, false);
	}

	return targets;
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
