#pragma once

#include "Engine/Includes/GameEngine.h"
#include "Interpolator.h"

class ObjectAnimation : public MonoBehaviour
{
public:
	ObjectAnimation(GameObject* object);
	~ObjectAnimation();

	void moveTo(glm::vec3 position, float duration, float(*interp)(float));
	void moveXTo(float x, float duration, float(*interp)(float));
	void moveYTo(float y, float duration, float(*interp)(float));
	void moveZTo(float z, float duration, float(*interp)(float));

	void rotateTo(glm::vec3 rotation, float duration, float(*interp)(float));
	void rotateXTo(float x, float duration, float(*interp)(float));
	void rotateYTo(float y, float duration, float(*interp)(float));
	void rotateZTo(float z, float duration, float(*interp)(float));

	void scaleTo(glm::vec3 scale, float duration, float(*interp)(float));
	void scaleXTo(float x, float duration, float(*interp)(float));
	void scaleYTo(float y, float duration, float(*interp)(float));
	void scaleZTo(float z, float duration, float(*interp)(float));

	glm::vec3 updateInterpolator(glm::vec3 value, Interpolator** x, Interpolator** y, Interpolator** z);
	void update() override;

private:
	Interpolator* m_position_x;
	Interpolator* m_position_y;
	Interpolator* m_position_z;

	Interpolator* m_rotation_x;
	Interpolator* m_rotation_y;
	Interpolator* m_rotation_z;

	Interpolator* m_scale_x;
	Interpolator* m_scale_y;
	Interpolator* m_scale_z;
};

