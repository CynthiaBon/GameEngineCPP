#include "EffectAnimation.h"

EffectAnimation::EffectAnimation()
{
	Shader* shader = Shader::Find("Base Shader");

	GameObject* spawn_object = GameEngine::createGameObject("Spawn effect");
	Mesh* spawn_mesh = OBJLoader::loadObj("Meshes/SpawnEffect.obj");
	Material* spawn_material = new Material(shader, glm::vec3(1.0f, 0.9f, 0.0f));
	spawn_material->setInt("use_emissive", 1);
	spawn_material->setVector3("emissive_color", glm::vec3(1.0f, 0.9f, 0.0f));
	m_spawn_renderer = new MeshRenderer(spawn_object, spawn_mesh, spawn_material);
	m_spawn_renderer->setActive(false);
	m_spawn_animation = new ObjectAnimation(spawn_object);

	Mesh* death_mesh = OBJLoader::loadObj("Meshes/Sphere.obj");
	Material* death_material = new Material(shader, glm::vec3(0.5f, 0.5f, 1.0f));
	death_material->setInt("use_emissive", 1);
	death_material->setVector3("emissive_color", glm::vec3(0.5f, 0.5f, 1.0f));

	GameObject* death_object_1 = GameEngine::createGameObject("Death effect 1");
	death_object_1->getTransform()->setPosition(glm::vec3(0.3f, 0.0f, 0.0f));
	m_death_renderer_1 = new MeshRenderer(death_object_1, death_mesh, death_material);
	m_death_renderer_1->setActive(false);
	m_death_animation_1 = new ObjectAnimation(death_object_1);

	GameObject* death_object_2 = GameEngine::createGameObject("Death effect 2");
	death_object_2->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.3f));
	m_death_renderer_2 = new MeshRenderer(death_object_2, death_mesh, death_material);
	m_death_renderer_2->setActive(false);
	m_death_animation_2 = new ObjectAnimation(death_object_2);

	GameObject* death_object_3 = GameEngine::createGameObject("Death effect 3");
	death_object_3->getTransform()->setPosition(glm::vec3(-0.15f, 0.0f, -0.15f));
	m_death_renderer_3 = new MeshRenderer(death_object_3, death_mesh, death_material);
	m_death_renderer_3->setActive(false);
	m_death_animation_3 = new ObjectAnimation(death_object_3);
}

EffectAnimation::~EffectAnimation()
{
}

void EffectAnimation::play(int id)
{
	if (id == 0)
	{
		m_spawn_renderer->setActive(true);
		m_spawn_animation->getGameObject()->getTransform()->setScale(glm::vec3(0.0f));
		m_spawn_animation->scaleTo(glm::vec3(1.0f), 0.5f, easeSin);
	}
	else if (id == 1)
	{
		float duration = 0.5f;

		m_death_renderer_1->setActive(true);
		m_death_renderer_2->setActive(true);
		m_death_renderer_3->setActive(true);

		m_death_animation_1->getGameObject()->getTransform()->setScale(glm::vec3(0.0f));
		m_death_animation_1->scaleTo(glm::vec3(0.2f), duration, easeSin);
		m_death_animation_1->getGameObject()->getTransform()->setPosition(glm::vec3(0.3f, 0.0f, 0.0f));
		m_death_animation_1->moveTo(glm::vec3(0.6f, 0.5f, 0.0f), duration, easeOutQuad);

		m_death_animation_2->getGameObject()->getTransform()->setScale(glm::vec3(0.0f));
		m_death_animation_2->scaleTo(glm::vec3(0.2f), duration, easeSin);
		m_death_animation_2->getGameObject()->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.3f));
		m_death_animation_2->moveTo(glm::vec3(0.0f, 0.5f, 0.6f), duration, easeOutQuad);

		m_death_animation_3->getGameObject()->getTransform()->setScale(glm::vec3(0.0f));
		m_death_animation_3->scaleTo(glm::vec3(0.2f), duration, easeSin);
		m_death_animation_3->getGameObject()->getTransform()->setPosition(glm::vec3(-0.15f, 0.0f, -0.15f));
		m_death_animation_3->moveTo(glm::vec3(-0.3f, 0.5f, -0.3f), duration, easeOutQuad);
	}
}
