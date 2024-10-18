#pragma once

#include <iostream>
#include "Engine/Includes/MeshRenderer.h"
#include "Engine/Includes/OBJLoader.h"
#include "ObjectAnimation.h"

class Card : public MonoBehaviour
{
public:
	Card(GameObject* object, std::string name, int attack, int health, std::string texture_path);
	~Card();

	void moveAndRotateTo(GameObject* target, float duration);

private:
	std::string m_name;
	int m_attack;
	int m_health;

	MeshRenderer* m_mesh_renderer;
	Material* m_material;
	Texture* m_texture;
	ObjectAnimation* m_animation;
};