#pragma once
#include "Color.h"
#include "SceneObject.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

using vertex_t = glm::vec3;
using vertexbuffer_t = std::vector<vertex_t>;

class Model : public SceneObject
{
public:
	Model(std::shared_ptr<Material> material) : SceneObject{ material } {}
	Model(const Transform& transform, std::shared_ptr<Material> material) :
		SceneObject{ transform,material } {}
	Model(const vertexbuffer_t& vertices, std::shared_ptr<Material> material) : SceneObject{ material }, m_local_vertices{ vertices } {}

	void Update() override;

	bool Load(const std::string& filename);
	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;

private:
	vertexbuffer_t m_vb;
	vertexbuffer_t m_local_vertices;

	glm::vec3 m_center{ 0 };
	float m_radius{ 0 };
};