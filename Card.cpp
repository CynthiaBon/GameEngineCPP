#include "Card.h"

//glm::vec3(0.225f, 0.03f, 0.375f), glm::vec3(0.0f), glm::vec3(0.06f)

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
}

Card::~Card()
{
}

void Card::moveAndRotateTo(GameObject* target, float duration)
{
	m_animation->moveTo(target->getTransform()->getPosition(), duration, easeInOutQuad);
	m_animation->rotateTo(target->getTransform()->getEulerRotation(), duration, easeInOutQuad);
}
