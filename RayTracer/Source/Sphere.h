#pragma once
#include "SceneObject.h"
#include "glm/glm.hpp"
class Sphere : public SceneObject
{
public: 
	Sphere() = default;
	Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) :
		SceneObject{ material },
		m_radius{ radius },
		m_center{ center }
	{
	}
	bool Hit(const ray_t& ray) override;
		
private:
	glm::vec3 m_center;
	float m_radius;
};