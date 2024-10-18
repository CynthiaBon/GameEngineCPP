#include "ObjectAnimation.h"

ObjectAnimation::ObjectAnimation(GameObject* object) : MonoBehaviour(object)
{
	m_position_x = nullptr;
	m_position_y = nullptr;
	m_position_z = nullptr;

	m_rotation_x = nullptr;
	m_rotation_y = nullptr;
	m_rotation_z = nullptr;

	m_scale_x = nullptr;
	m_scale_y = nullptr;
	m_scale_z = nullptr;
}

ObjectAnimation::~ObjectAnimation()
{
}

void ObjectAnimation::moveTo(glm::vec3 position, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getPosition();
	m_position_x = new Interpolator(begin.x, position.x, duration, interp);
	m_position_y = new Interpolator(begin.y, position.y, duration, interp);
	m_position_z = new Interpolator(begin.z, position.z, duration, interp);
}

void ObjectAnimation::moveXTo(float x, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getPosition();
	m_position_x = new Interpolator(begin.x, x, duration, interp);
}

void ObjectAnimation::moveYTo(float y, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getPosition();
	m_position_y = new Interpolator(begin.y, y, duration, interp);
}

void ObjectAnimation::moveZTo(float z, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getPosition();
	m_position_z = new Interpolator(begin.z, z, duration, interp);
}

void ObjectAnimation::rotateTo(glm::vec3 rotation, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getEulerRotation();
	m_rotation_x = new Interpolator(begin.x, rotation.x, duration, interp);
	m_rotation_y = new Interpolator(begin.y, rotation.y, duration, interp);
	m_rotation_z = new Interpolator(begin.z, rotation.z, duration, interp);
}

void ObjectAnimation::rotateXTo(float x, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getEulerRotation();
	m_rotation_x = new Interpolator(begin.x, x, duration, interp);
}

void ObjectAnimation::rotateYTo(float y, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getEulerRotation();
	m_rotation_y = new Interpolator(begin.y, y, duration, interp);
}

void ObjectAnimation::rotateZTo(float z, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getEulerRotation();
	m_rotation_z = new Interpolator(begin.z, z, duration, interp);
}

void ObjectAnimation::scaleTo(glm::vec3 scale, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getScale();
	m_scale_x = new Interpolator(begin.x, scale.x, duration, interp);
	m_scale_y = new Interpolator(begin.y, scale.y, duration, interp);
	m_scale_z = new Interpolator(begin.z, scale.z, duration, interp);
}

void ObjectAnimation::scaleXTo(float x, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getScale();
	m_scale_x = new Interpolator(begin.x, x, duration, interp);
}

void ObjectAnimation::scaleYTo(float y, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getScale();
	m_scale_x = new Interpolator(begin.y, y, duration, interp);
}

void ObjectAnimation::scaleZTo(float z, float duration, float(*interp)(float))
{
	glm::vec3 begin = getGameObject()->getTransform()->getScale();
	m_scale_x = new Interpolator(begin.z, z, duration, interp);
}

glm::vec3 ObjectAnimation::updateInterpolator(glm::vec3 value, Interpolator** x, Interpolator** y, Interpolator** z)
{
	if ((*x) != nullptr)
	{
		value.x = (*x)->update(GameEngine::getDeltaTime());
		if ((*x)->isFinished())
		{
			delete (*x);
			(*x) = nullptr;
		}
	}
	if ((*y) != nullptr)
	{
		value.y = (*y)->update(GameEngine::getDeltaTime());
		if ((*y)->isFinished())
		{
			delete (*y);
			(*y) = nullptr;
		}
	}
	if ((*z) != nullptr)
	{
		value.z = (*z)->update(GameEngine::getDeltaTime());
		if ((*z)->isFinished())
		{
			delete (*z);
			(*z) = nullptr;
		}
	}

	return value;
}

void ObjectAnimation::update()
{
	Transform* transform = getGameObject()->getTransform();

	glm::vec3 position = updateInterpolator(transform->getPosition(), &m_position_x, &m_position_y, &m_position_z);
	transform->setPosition(position);
	
	glm::vec3 rotation = updateInterpolator(transform->getEulerRotation(), &m_rotation_x, &m_rotation_y, &m_rotation_z);
	transform->setRotation(rotation);

	glm::vec3 scale = updateInterpolator(transform->getScale(), &m_scale_x, &m_scale_y, &m_scale_z);
	transform->setScale(scale);
}
