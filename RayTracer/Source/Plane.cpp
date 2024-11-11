#include "Plane.h"
#include "MathUtils.h"

bool Plane::Hit(const ray_t& ray, raycastHit_t& raycasthit, float minDistance, float maxDistance)
{
    float t;

    if (!Raycast(ray, m_transform.position, m_transform.GetUp(), minDistance, maxDistance, t)) return false;

    raycasthit.distance = t;
    raycasthit.normal = glm::normalize(raycasthit.point - m_transform.position);
    raycasthit.point = ray.At(t);
    raycasthit.material = GetMaterial();

    return true;
    
}

bool Plane::Raycast(const ray_t& ray, const glm::vec3& point, const glm::vec3 normal, float minDistance, float maxDistance, float& t)
{

    float denominator = glm::dot(ray.direction, normal);

    if (approximately(denominator, 0.0f))
    {
        return false;
    }

    t = glm::dot(point - ray.origin, normal) / denominator;

    //if (t < 0) return false;
    if (t <= minDistance || t >= maxDistance) return false;

    return true;
}
