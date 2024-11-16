#include "Card.h"

Card::Card(GameObject* object, std::string name, int attack, int health, std::string texture_path) : MonoBehaviour(object)
{
	m_name = name;
	m_attack = attack;
	m_health = health;

	Shader* shader = Shader::Find("Base Shader");
	m_texture = new Texture(texture_path.c_str(), 0);
	m_material = new Material(shader, glm::vec3(1.0f), m_texture);
	Mesh* mesh = OBJLoader::loadObj("Meshes/Card.obj");
	m_mesh_renderer = new MeshRenderer(object, mesh, m_material);
	m_animation = new ObjectAnimation(object);

	Mesh* quad = OBJLoader::loadObj("Meshes/Quad.obj");

	GameObject* attack_object = GameEngine::createGameObject("Attack", glm::vec3(0.225f, 0.03f, 0.375f), glm::vec3(0.0f), glm::vec3(0.06f));
	Material* attack_material = new Material(shader, glm::vec3(0.0f, 0.0f, 1.0f));
	m_attack_mesh = new MeshRenderer(attack_object, quad, attack_material);
	m_attack_animation = new ObjectAnimation(attack_object);

	GameObject* health_object = GameEngine::createGameObject("Health", glm::vec3(-0.225f, 0.03f, 0.375f), glm::vec3(0.0f), glm::vec3(0.06f));
	Material* health_material = new Material(shader, glm::vec3(1.0f, 0.0f, 0.0f));
	m_health_mesh = new MeshRenderer(health_object, quad, health_material);
	m_health_animation = new ObjectAnimation(health_object);

	m_texture_paths = std::vector<std::string>();
	m_texture_paths.push_back("Images/Numbers/Zero.png");
	m_texture_paths.push_back("Images/Numbers/One.png");
	m_texture_paths.push_back("Images/Numbers/Two.png");
	m_texture_paths.push_back("Images/Numbers/Three.png");
	m_texture_paths.push_back("Images/Numbers/Four.png");
	m_texture_paths.push_back("Images/Numbers/Five.png");
	m_texture_paths.push_back("Images/Numbers/Six.png");
	m_texture_paths.push_back("Images/Numbers/Seven.png");
	m_texture_paths.push_back("Images/Numbers/Eight.png");
	m_texture_paths.push_back("Images/Numbers/Nine.png");

	setDisplay(m_health, m_health_mesh);
	setDisplay(m_attack, m_attack_mesh);

	m_effect = new EffectAnimation(getGameObject()->getTransform());
}

Card::~Card()
{
}

void Card::moveAndRotateTo(GameObject* target, float duration)
{
	glm::vec3 attack_offset = glm::vec3(0.225f, 0.03f, 0.375f);
	glm::vec3 health_offset = glm::vec3(-0.225f, 0.03f, 0.375f);
	glm::vec3 target_rotation = target->getTransform()->getEulerRotation();
	if (target_rotation.y == 180.0f)
	{
		attack_offset.z *= -1;
		health_offset.z *= -1;
	}
	if (target_rotation.z == 180.0f)
	{
		attack_offset.x *= -1;
		health_offset.x *= -1;
		attack_offset.y *= -1;
		health_offset.y *= -1;
	}

	m_animation->moveTo(target->getTransform()->getPosition(), duration, easeInOutQuad);
	m_animation->rotateTo(target->getTransform()->getEulerRotation(), duration, easeInOutQuad);
	m_attack_animation->moveTo(target->getTransform()->getPosition() + attack_offset, duration, easeInOutQuad);
	m_attack_animation->getGameObject()->getTransform()->setRotation(0.0f, target_rotation.y, 0.0f);
	m_health_animation->moveTo(target->getTransform()->getPosition() + health_offset, duration, easeInOutQuad);
	m_health_animation->getGameObject()->getTransform()->setRotation(0.0f, target_rotation.y, 0.0f);
}

void Card::takeDamage(int amount)
{
	m_health -= amount;
	if (m_health <= 0)
	{
		m_effect->play(1);
		m_health = 0;
	}

	setDisplay(m_health, m_health_mesh);
}

bool Card::isDead()
{
	return m_health == 0;
}

int Card::getAttack()
{
	return m_attack;
}

void Card::playSpawnEffect()
{
	m_effect->play(0);
}

void Card::setSelected(bool selected)
{
	if (selected)
		m_material->setBaseColor(glm::vec3(0.8f, 1.0f, 0.8f));
	else
		m_material->setBaseColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Card::setDisplay(int amount, MeshRenderer* renderer)
{
	std::string texture_path = m_texture_paths[amount];
	Texture* texture = new Texture(texture_path.c_str(), 0);
	Material* material = renderer->getMaterial();

	if (material->getTexture() != nullptr)
		delete material->getTexture();

	material->setBaseTexture(texture);
}
