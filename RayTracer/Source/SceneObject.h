#pragma once
#include "Material.h"
#include "Ray.h"
#include "Transform.h"
#include <memory>
class SceneObject
{
public:
	
	SceneObject() = default; 
	SceneObject(const Transform& transform, std::shared_ptr<Material> material) : m_transform{ transform }, m_material{ material } {}
	SceneObject(std::shared_ptr<Material> material) {
		m_material = material;
	}

	virtual bool Hit(const ray_t& ray,raycastHit_t& raycasthit,float minDistance, float maxDistance) = 0;
	virtual void Update() {}

	std::weak_ptr<Material> GetMaterial() { return m_material;}
	Transform& GetTransform() { return m_transform; }
	const Transform& GetTransform() const { return m_transform; }


protected:
	std::shared_ptr<Material> m_material;
	Transform m_transform;
}; 