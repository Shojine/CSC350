#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Tracer.h"
#include "Random.h"
#include <iostream>

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples, int depth)
{
	for (int y = 0; y < framebuffer.m_height; y++)
	{
		for (int x = 0; x < framebuffer.m_width; x++)
		{
			color3_t color{ 0 };
			// multi-sample for each pixel
			for (int i = 0; i < numSamples; i++)
			{
				glm::vec2 pixel{ x, y };
				// add a random value to the pixel (0-1)
				pixel += glm::vec2{ random(1), random(1)};
				// normalize the pixel value
				glm::vec2 point = pixel / glm::vec2{ framebuffer.m_width, framebuffer.m_height };
				// flip the y value (bottom = 0, top = 1)
				point.y = 1 - point.y;

				ray_t ray = camera.GetRay(point);
				// accumulate colors from tracer
				color += Tracer::Trace(*this, ray, 0.001f, 100.0f, depth);//<add the color from the Trace function to the color>
			}
			// average the color
			color /= static_cast<float>(numSamples) ;//<color average is color / number samples, remember to do float division>
			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}
	}

}