#pragma once

#include "IAnimation.h"
#include "Engine/Includes/MeshRenderer.h"
#include "ObjectAnimation.h"

class MonsterExampleAnimation : public IAnimation
{
public:
	MonsterExampleAnimation();
	~MonsterExampleAnimation();

	virtual void play(int id);

private:
	MeshRenderer* createMesh(GameObject* object, const char* mesh_path, Material* material);

	void playSpawnAnimation();
	void playAttackAnimation();
	void playHitAnimation();
	void playDeathAnimation();

private:
	MeshRenderer* m_body_renderer;
	ObjectAnimation* m_body_animation;

	MeshRenderer* m_left_eye_renderer;
	ObjectAnimation* m_left_eye_animation;

	MeshRenderer* m_right_eye_renderer;
	ObjectAnimation* m_right_eye_animation;
};