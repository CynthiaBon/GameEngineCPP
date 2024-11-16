#include "MonsterExampleAnimation.h"

MonsterExampleAnimation::MonsterExampleAnimation()
{
	Shader* shader = Shader::Find("Base Shader");
	Material* body_material = new Material(shader, glm::vec3(0.7f, 1.0f, 0.85f));
	Material* eye_material = new Material(shader, glm::vec3(0.2f, 0.2f, 0.2f));

	GameObject* body = GameEngine::createGameObject("Body", glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.3f, 0.2f, 0.3f));
	m_body_renderer = createMesh(body, "Meshes/Sphere.obj", body_material);
	m_body_animation = new ObjectAnimation(body);

	GameObject* left_eye = GameEngine::createGameObject("Left Eye", glm::vec3(-0.11f, 0.1f, 0.15f), glm::vec3(0.0f), glm::vec3(0.07f));
	m_left_eye_renderer = createMesh(left_eye, "Meshes/Sphere.obj", eye_material);
	m_left_eye_animation = new ObjectAnimation(left_eye);

	GameObject* right_eye = GameEngine::createGameObject("Right Eye", glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f), glm::vec3(0.1f));
	m_right_eye_renderer = createMesh(right_eye, "Meshes/Sphere.obj", eye_material);
	m_right_eye_animation = new ObjectAnimation(right_eye);
}

MonsterExampleAnimation::~MonsterExampleAnimation()
{
}

void MonsterExampleAnimation::play(int id)
{
	if (id == 0)
		playSpawnAnimation();
	else if (id == 1)
		playAttackAnimation();
	else if (id == 2)
		playHitAnimation();
	else if (id == 3)
		playDeathAnimation();
}

MeshRenderer* MonsterExampleAnimation::createMesh(GameObject* object, const char* mesh_path, Material* material)
{
	Mesh* mesh = OBJLoader::loadObj(mesh_path);
	MeshRenderer* renderer = new MeshRenderer(object, mesh, material);
	renderer->setActive(false);
	return renderer;
}

void MonsterExampleAnimation::playSpawnAnimation()
{
	m_body_renderer->setActive(true);
	m_left_eye_renderer->setActive(true);
	m_right_eye_renderer->setActive(true);

	float duration = 1.0f;

	//Body
	m_body_animation->getGameObject()->getTransform()->setScale(0.0f, 0.0f, 0.0f);
	m_body_animation->scaleTo(glm::vec3(0.3f, 0.2f, 0.3f), duration * 0.7f, easeOutQuad);

	m_body_animation->getGameObject()->getTransform()->setPosition(0.0f, 0.0f, 0.0f);
	m_body_animation->moveYTo(0.5f, duration, easeSin);

	//Left eye
	m_left_eye_animation->getGameObject()->getTransform()->setScale(0.0f, 0.0f, 0.0f);
	m_left_eye_animation->scaleTo(glm::vec3(0.07f), duration, easeOutQuad);

	m_left_eye_animation->getGameObject()->getTransform()->setPosition(-0.11f, 0.1f, 0.15f);
	m_left_eye_animation->moveYTo(0.6f, duration, easeSin);

	//Right eye
	m_right_eye_animation->getGameObject()->getTransform()->setScale(0.0f, 0.0f, 0.0f);
	m_right_eye_animation->scaleTo(glm::vec3(0.1f), duration, easeOutQuad);

	m_right_eye_animation->getGameObject()->getTransform()->setPosition(0.1f, 0.1f, 0.1f);
	m_right_eye_animation->moveYTo(0.6f, duration, easeSin);
}

void MonsterExampleAnimation::playAttackAnimation()
{
	float duration = 0.5f;

	//Body
	m_body_animation->getGameObject()->getTransform()->setPosition(0.0f, 0.0f, 0.0f);
	m_body_animation->moveYTo(0.4f, duration, jump);
	m_body_animation->moveZTo(0.2f, duration, easeSin);

	//Left eye
	m_left_eye_animation->getGameObject()->getTransform()->setPosition(-0.11f, 0.1f, 0.15f);
	m_left_eye_animation->moveYTo(0.5f, duration, jump);
	m_left_eye_animation->moveZTo(0.3f, duration, easeSin);

	//Right eye
	m_right_eye_animation->getGameObject()->getTransform()->setPosition(0.1f, 0.1f, 0.1f);
	m_right_eye_animation->moveYTo(0.5f, duration, jump);
	m_right_eye_animation->moveZTo(0.3f, duration, easeSin);
}

void MonsterExampleAnimation::playHitAnimation()
{
	float duration = 0.7f;

	//Body
	m_body_animation->getGameObject()->getTransform()->setScale(0.3f, 0.2f, 0.3f);
	m_body_animation->scaleTo(glm::vec3(0.25f, 0.1f, 0.25f), duration, shake);

	//Left eye
	m_left_eye_animation->getGameObject()->getTransform()->setPosition(-0.11f, 0.1f, 0.15f);
	m_left_eye_animation->moveYTo(0.05f, duration, shake);

	m_left_eye_animation->getGameObject()->getTransform()->setScale(0.07f, 0.07f, 0.07f);
	m_left_eye_animation->scaleTo(glm::vec3(0.05f), duration, easeSin);


	//Right eye
	m_right_eye_animation->getGameObject()->getTransform()->setPosition(0.1f, 0.1f, 0.1f);
	m_right_eye_animation->moveYTo(0.05f, duration, shake);

	m_right_eye_animation->getGameObject()->getTransform()->setScale(0.1f, 0.1f, 0.1f);
	m_right_eye_animation->scaleTo(glm::vec3(0.08f), duration, easeSin);
}

void MonsterExampleAnimation::playDeathAnimation()
{
	float duration = 0.5f;

	//Body
	m_body_animation->getGameObject()->getTransform()->setScale(0.3f, 0.2f, 0.3f);
	m_body_animation->scaleXTo(0.0f, duration, easeInQuad);
	m_body_animation->scaleYTo(0.0f, duration, easeOutQuad);
	m_body_animation->scaleZTo(0.0f, duration, easeInQuad);

	duration *= 0.5f;

	//Left eye
	m_left_eye_animation->getGameObject()->getTransform()->setPosition(-0.11f, 0.1f, 0.15f);
	m_left_eye_animation->moveYTo(0.0f, duration, easeInQuad);

	m_left_eye_animation->getGameObject()->getTransform()->setScale(0.07f, 0.07f, 0.07f);
	m_left_eye_animation->scaleTo(glm::vec3(0.0f), duration, easeInQuad);

	//Right eye
	m_right_eye_animation->getGameObject()->getTransform()->setPosition(0.1f, 0.1f, 0.1f);
	m_right_eye_animation->moveYTo(0.0f, duration, easeInQuad);

	m_right_eye_animation->getGameObject()->getTransform()->setScale(0.1f, 0.1f, 0.1f);
	m_right_eye_animation->scaleTo(glm::vec3(0.0f), duration, easeInQuad);
}
