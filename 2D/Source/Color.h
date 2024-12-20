#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "MathUtils.h"
#include <SDL.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtx/color_space.hpp>
using color_t = SDL_Color;
using color_t = SDL_Color;
using color3_t = glm::vec3;
using color4_t = glm::vec4;

inline color3_t HSVtoRGB(const glm::vec3& hsv)
{
	return glm::rgbColor(hsv);
}

inline color3_t HSVtoRGB(float hue, float saturation, float value)
{
	return glm::rgbColor(glm::vec3{ hue, saturation, value });
}

inline float LinearToGamma(float linear)
{
	if (linear > 0)
		return std::sqrt(linear);

	return 0;
}
inline color_t ColorConvert(const color4_t& color4)
{
	color_t color;

	color.r = static_cast<uint8_t>(Clamp(LinearToGamma(color4.r), 1.0f, 0.0f) * 255);
	color.g = static_cast<uint8_t>(Clamp(LinearToGamma(color4.g), 1.0f, 0.0f) * 255);
	color.b = static_cast<uint8_t>(Clamp(LinearToGamma(color4.b), 1.0f, 0.0f) * 255);
	color.a = static_cast<uint8_t>(Clamp(LinearToGamma(color4.a), 1.0f, 0.0f) * 255);

	return color;
}


inline color_t ColorConvert(const color3_t& color3)
{
	color_t color;

	color.r = static_cast<uint8_t>(Clamp(LinearToGamma(color3.r), 1.0f, 0.0f) * 255);
	color.g = static_cast<uint8_t>(Clamp(LinearToGamma(color3.g), 1.0f, 0.0f) * 255);
	color.b = static_cast<uint8_t>(Clamp(LinearToGamma(color3.b), 1.0f, 0.0f) * 255);
	color.a = 255;

	return color;
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

