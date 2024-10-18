#include "Interpolator.h"

Interpolator::Interpolator(float begin, float end, float duration, float(*interp)(float))
{
	m_begin = begin;
	m_end = end;
	m_duration = duration;
	m_current_time = 0.0f;
	m_interp = interp;
}

Interpolator::~Interpolator()
{
}

float Interpolator::update(float delta_time)
{
	m_current_time += delta_time;
	return lerp(m_begin, m_end, m_interp(m_current_time / m_duration));
}

bool Interpolator::isFinished()
{
	return m_current_time >= m_duration;
}
