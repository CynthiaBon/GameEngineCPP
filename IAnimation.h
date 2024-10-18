#pragma once

class IAnimation
{
public:
	virtual ~IAnimation() {};

	virtual void play(int id) = 0;
};