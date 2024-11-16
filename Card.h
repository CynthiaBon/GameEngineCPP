#pragma once

#include <iostream>
#include "Engine/Includes/MeshRenderer.h"
#include "Engine/Includes/OBJLoader.h"
#include "ObjectAnimation.h"
#include "EffectAnimation.h"
#include <vector>
#include "MonsterExampleAnimation.h"

class Card : public MonoBehaviour
{
public:
	Card(GameObject* object, std::string name, int attack, int health, std::string texture_path);
	~Card();

	void moveAndRotateTo(GameObject* target, float duration);
	void takeDamage(int amount);
	bool isDead();
	int getAttack();
	void playSpawnEffect();
	void setSelected(bool selected);

private:
	void setDisplay(int amount, MeshRenderer* renderer);

private:
	std::string m_name;
	int m_attack;
	int m_health;

	MeshRenderer* m_mesh_renderer;
	Material* m_material;
	Texture* m_texture;
	ObjectAnimation* m_animation;

	MeshRenderer* m_attack_mesh;
	ObjectAnimation* m_attack_animation;
	MeshRenderer* m_health_mesh;
	ObjectAnimation* m_health_animation;

	std::vector<std::string> m_texture_paths;

	EffectAnimation* m_effect;
};