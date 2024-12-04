#pragma once
#include "Color.h"
#include "glm/glm.hpp"

struct fragment_input_t
{
	color4_t color;
	glm::vec3 position;
	glm::vec3 normal;
};

class FragmentShader
{
public:
	static color4_t Process(const fragment_input_t& fragment);
};