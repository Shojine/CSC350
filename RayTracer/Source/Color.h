#pragma once
#include "MathUtils.h"
#include <SDL.h>
#include <algorithm>
#include <glm/glm.hpp>

using color_t = SDL_Color;
using color3_t = glm::vec3;
using color4_t = glm::vec4;

inline color_t ColorConvert(const color4_t& color4)
{
	color_t color;

	color.r = static_cast<uint8_t>(Clamp(color4.r, 1.0f, 0.0f) * 255);
	color.g = static_cast<uint8_t>(Clamp(color4.g, 1.0f, 0.0f) * 255);
	color.b = static_cast<uint8_t>(Clamp(color4.b, 1.0f, 0.0f) * 255);
	color.a = static_cast<uint8_t>(Clamp(color4.r, 1.0f, 0.0f) * 255);

	return color;
}
inline color_t ColorConvert(const color3_t& color3)
{
	color_t color;

	color.r = static_cast<uint8_t>(Clamp(color3.r, 1.0f, 0.0f) * 255);
	color.g = static_cast<uint8_t>(Clamp(color3.g, 1.0f, 0.0f) * 255);
	color.b = static_cast<uint8_t>(Clamp(color3.b, 1.0f, 0.0f) * 255);
	color.a = 255;

	return color;
}

inline color4_t ColorConvert(color_t color)
{
	color4_t color4;

	color4.r = color.r / 255.0f;
	color4.g = color.r / 255.0f;
	color4.b = color.b / 255.0f;

	return color4;
}



enum class BlendMode
{
	Normal,
	Alpha,
	Additive,
	Multiply
};

 color_t NormalBlend(const color_t& src, const color_t& dest);
 color_t AlphaBlend(const color_t& src, const color_t& dest);
 color_t AdditiveBlend(const color_t& src, const color_t& dest);
 color_t MultiplyBlend(const color_t& src, const color_t& dest);
 void SetBlendMode(BlendMode blendmode);
 color_t ColorBlend(const color_t& src, const color_t& dest);

