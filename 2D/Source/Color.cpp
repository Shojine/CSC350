#include "Color.h"

color_t(*blend_func)(const color_t& src, const color_t& dest);

void SetBlendMode(BlendMode blendmode)
{
	switch (blendmode)
	{
	case BlendMode::Normal:
		blend_func = NormalBlend;
		break;
	case BlendMode::Alpha:
		blend_func = AlphaBlend;
		break;
	case BlendMode::Additive:
		blend_func = AdditiveBlend;
		break;
	case BlendMode::Multiply:
		//blend_func = MultiplyBlend;
		break;
	default:
		break;
	}
}
color_t ColorBlend(const color_t& src, const color_t& dest)
{
	return blend_func(src, dest);
}

color_t NormalBlend(const color_t& src, const color_t& dest)
{
	return src;
}

color_t AlphaBlend(const color_t& src, const color_t& dest)
{
	uint8_t alpha = src.a;
	uint8_t inv_alpha = 255 - alpha;

	color_t color;
	color.r = ((src.r * alpha) + (dest.r * inv_alpha)) >> 8;
	color.g = ((src.g * alpha) + (dest.g * inv_alpha)) >> 8;
	color.b = ((src.b * alpha) + (dest.b * inv_alpha)) >> 8;
	color.a = src.a;

	return color;
}

color_t AdditiveBlend(const color_t& src, const color_t& dest)
{
	uint8_t alpha = src.a;
	uint8_t inv_alpha = 255 - alpha;

	color_t color;
	color.r = std::min(src.r + dest.r, 255);
	color.g = std::min(src.g + dest.g, 255);
	color.b = std::min(src.b + dest.b, 255);
	color.a = src.a;

	return color;
}

color_t MultiplyBlend(const color_t& src, const color_t& dest)
{
	uint8_t alpha = src.a;
	uint8_t inv_alpha = 255 - alpha;

	color_t color;
	color.r = std::min(src.r * dest.r, 255);
	color.g = std::min(src.g * dest.g, 255);
	color.b = std::min(src.b * dest.b, 255);
	color.a = src.a;

	return color;
}
