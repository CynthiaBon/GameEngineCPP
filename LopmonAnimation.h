#pragma once

#include "IAnimation.h"
#include "Engine/Includes/MeshRenderer.h"
#include "Engine/Includes/Debug.h"
#include "ObjectAnimation.h"

class LopmonAnimation : public IAnimation
{
public:
	LopmonAnimation();
	~LopmonAnimation();

	virtual void play(int id);

private:
	MeshRenderer* createMesh(const char* name, glm::vec3 position, glm::vec3 rotation, const char* mesh_path, Material* material);

	void playSpawnAnimation();
	void playSpawnAnimationTo(MeshRenderer* renderer, ObjectAnimation* animation);

private:
	MeshRenderer* m_lopmon_head_renderer;
	ObjectAnimation* m_lopmon_head_animation;

	MeshRenderer* m_lopmon_body_renderer;
	ObjectAnimation* m_lopmon_body_animation;

	MeshRenderer* m_lopmon_ear_1_renderer;
	ObjectAnimation* m_lopmon_ear_1_animation;

	MeshRenderer* m_lopmon_ear_2_renderer;
	ObjectAnimation* m_lopmon_ear_2_animation;

	MeshRenderer* m_lopmon_arm_1_renderer;
	ObjectAnimation* m_lopmon_arm_1_animation;

	MeshRenderer* m_lopmon_arm_2_renderer;
	ObjectAnimation* m_lopmon_arm_2_animation;

	bool has_spawn;
};
