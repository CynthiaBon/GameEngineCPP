#pragma once

#include "Engine/Includes/MathHelper.h"

class Interpolator
{
public:
	Interpolator(float begin, float end, float duration, float(*interp)(float));
	~Interpolator();

	float update(float delta_time);
	bool isFinished();

private:
	float m_begin;
	float m_end;
	float m_duration;
	float m_current_time;
	float(*m_interp)(float);
};

