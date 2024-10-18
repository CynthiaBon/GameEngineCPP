#include "../Includes/MathHelper.h"

float lerp(float a, float b, float t)
{
	return a * (1.0 - t) + (b * t);
}

glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t)
{
	return glm::vec2(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
}

glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t)
{
	return glm::vec3(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t));
}

glm::vec4 lerp(glm::vec4 a, glm::vec4 b, float t)
{
	return glm::vec4(lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t), lerp(a.w, b.w, t));
}

float linear(float x)
{
	return x;
}

float easeInQuad(float x)
{
	return x * x;
}

float easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

float easeInOutQuad(float x)
{
	return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
}

float easeSin(float x)
{
	float result = sin(x * M_PI);
	if (result < 0.0f)
		result = 0.0f;
	return result;
}
