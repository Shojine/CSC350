#include "Plane.h"
#include "MathUtils.h"

bool Plane::Hit(const ray_t& ray, raycastHit_t& raycasthit, float minDistance, float maxDistance)
{
    float denominator = dot(ray.direction, m_normal);
    
    if (approximately(denominator, 0.0f))
    {
        return false;
    }

    float t = glm::dot(m_center - ray.origin, m_normal) / denominator;

    //if (t < 0) return false;
    if (t <= minDistance || t >= maxDistance) return false;

    raycasthit.distance = t;
    raycasthit.normal = m_normal;
    raycasthit.point = ray.At(t);
    raycasthit.material = this->m_material;

    return true;
    
}
