#pragma once

#include "IAnimation.h"
#include "Engine/Includes/MeshRenderer.h"
#include "ObjectAnimation.h"

class EffectAnimation : public IAnimation
{
public:
	EffectAnimation(Transform* root);
	~EffectAnimation();

	virtual void play(int id);

private:
	MeshRenderer* m_spawn_renderer;
	ObjectAnimation* m_spawn_animation;

	MeshRenderer* m_death_renderer_1;
	ObjectAnimation* m_death_animation_1;

	MeshRenderer* m_death_renderer_2;
	ObjectAnimation* m_death_animation_2;

	MeshRenderer* m_death_renderer_3;
	ObjectAnimation* m_death_animation_3;

	Transform* m_root;
};