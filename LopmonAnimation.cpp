#include "LopmonAnimation.h"

LopmonAnimation::LopmonAnimation()
{
	Shader* shader = Shader::Find("Base Shader");

	Texture* lopmon_texture = new Texture("Images/T_Lopmon.png", 0);
	Material* lopmon_material = new Material(shader, glm::vec3(1.0f), lopmon_texture);

	m_lopmon_head_renderer = createMesh("Head", glm::vec3(0.0f), glm::vec3(0.0f), "Meshes/Lopmon/SM_Lopmon_Head.obj", lopmon_material);
	m_lopmon_head_animation = new ObjectAnimation(m_lopmon_head_renderer->getGameObject());

	m_lopmon_body_renderer = createMesh("Body", glm::vec3(0.0f, -0.19f, 0.0f), glm::vec3(0.0f), "Meshes/Lopmon/SM_Lopmon_Body.obj", lopmon_material);
	m_lopmon_body_animation = new ObjectAnimation(m_lopmon_body_renderer->getGameObject());

	m_lopmon_ear_1_renderer = createMesh("Ear1", glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(10.0f, 0.0f, 10.0f), "Meshes/Lopmon/SM_Lopmon_Ear.obj", lopmon_material);
	m_lopmon_ear_1_animation = new ObjectAnimation(m_lopmon_ear_1_renderer->getGameObject());

	m_lopmon_ear_2_renderer = createMesh("Ear2", glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(10.0f, 180.0f, 10.0f), "Meshes/Lopmon/SM_Lopmon_Ear.obj", lopmon_material);
	m_lopmon_ear_2_animation = new ObjectAnimation(m_lopmon_ear_2_renderer->getGameObject());

	m_lopmon_arm_1_renderer = createMesh("Arm1", glm::vec3(0.09f, -0.1f, 0.0f), glm::vec3(-10.0f, 0.0f, 10.0f), "Meshes/Lopmon/SM_Lopmon_Arm.obj", lopmon_material);
	m_lopmon_arm_1_animation = new ObjectAnimation(m_lopmon_arm_1_renderer->getGameObject());

	m_lopmon_arm_2_renderer = createMesh("Arm2", glm::vec3(-0.09f, -0.1f, 0.0f), glm::vec3(-10.0f, 0.0f, -10.0f), "Meshes/Lopmon/SM_Lopmon_Arm.obj", lopmon_material);
	m_lopmon_arm_2_animation = new ObjectAnimation(m_lopmon_arm_2_renderer->getGameObject());

	Texture* cheru_texture = new Texture("Images/T_Cherubimon.png", 0);
	Material* cheru_material = new Material(shader, glm::vec3(1.0f), cheru_texture);

	has_spawn = false;
}

LopmonAnimation::~LopmonAnimation()
{
}

void LopmonAnimation::play(int id)
{
	if (id == 0 && !has_spawn)
		playSpawnAnimation();
}

MeshRenderer* LopmonAnimation::createMesh(const char* name, glm::vec3 position, glm::vec3 rotation, const char* mesh_path, Material* material)
{
	GameObject* object = GameEngine::createGameObject(name, position, rotation, glm::vec3(0.0f));
	Mesh* mesh = OBJLoader::loadObj(mesh_path);
	MeshRenderer* renderer = new MeshRenderer(object, mesh, material);
	renderer->setActive(false);
	return renderer;
}

void LopmonAnimation::playSpawnAnimation()
{
	playSpawnAnimationTo(m_lopmon_head_renderer, m_lopmon_head_animation);
	playSpawnAnimationTo(m_lopmon_body_renderer, m_lopmon_body_animation);
	playSpawnAnimationTo(m_lopmon_ear_1_renderer, m_lopmon_ear_1_animation);
	playSpawnAnimationTo(m_lopmon_ear_2_renderer, m_lopmon_ear_2_animation);
	playSpawnAnimationTo(m_lopmon_arm_1_renderer, m_lopmon_arm_1_animation);
	playSpawnAnimationTo(m_lopmon_arm_2_renderer, m_lopmon_arm_2_animation);

	float duration = 0.8f;
	m_lopmon_ear_1_animation->rotateXTo(-150.0f, duration, easeSin);
	m_lopmon_arm_1_animation->rotateXTo(-150.0f, duration, easeSin);

	has_spawn = true;
}

void LopmonAnimation::playSpawnAnimationTo(MeshRenderer* renderer, ObjectAnimation* animation)
{
	float duration = 0.5f;

	renderer->setActive(true);
	Transform* transform = renderer->getGameObject()->getTransform();
	glm::vec3 target_position = transform->getPosition() + glm::vec3(0.0f, 0.5f, 0.0f);
	animation->moveTo(target_position, duration, easeSin);
	animation->scaleTo(glm::vec3(1.0f), duration / 2.0f, easeOutQuad);
}
