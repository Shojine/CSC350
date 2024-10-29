#include "Tracer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"


color3_t Tracer::Trace(Scene& scene, const ray_t& ray, float minDistance, float maxDistance, int depth)
{
	
	if (depth == 0) return color3_t{ 0 };
	raycastHit_t raycastHit;
	float closestDistance = maxDistance;
	bool isHit = false;

	for (auto& object : scene.m_objects)
	{
		if (object->Hit(ray, raycastHit, minDistance, closestDistance))
		{
			isHit = true;
			closestDistance = raycastHit.distance;
			
		}
	}

	if (isHit)
	{
		color3_t attentuation;
		ray_t scatter;
		if (raycastHit.material.lock()->Scatter(ray, raycastHit, attentuation, scatter))
		{
			return attentuation * Trace(scene, scatter, minDistance, maxDistance, depth - 1);
		}
	}

	
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f;
	color3_t color = Lerp(color3_t{ 1 , 1, 1 }, color3_t{0.5f, 0.7f, 1.0f }, t);

	return color;
}