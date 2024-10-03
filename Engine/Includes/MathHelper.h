#pragma once

#include <glm.hpp>

float lerp(float a, float b, float t);
glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float t);
glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t);
glm::vec4 lerp(glm::vec4 a, glm::vec4 b, float t);
float easeInQuad(float x);
float easeOutQuad(float x);
float easeInOutQuad(float x);