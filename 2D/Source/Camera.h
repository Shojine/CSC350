#pragma once
#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>
class Camera
{
public:
	Camera(int width, int height) : m_width{ width }, m_height{ height } {}
	
	void SetView(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up = { 0,1,0 });
	void SetProjection(float fov, float aspect, float near, float far);

	glm::vec3 ModelToView(const glm::vec3& position);
	glm::vec3 ViewToProjection(const glm::vec3& position);
	glm::ivec2 ToScreen(const glm::vec3& position);

	const glm::mat4& GetView() { return m_view; }
	const glm::mat4& GetProjection() { return m_projection; }

private:

	glm::mat4 m_view{ 0 };
	glm::mat4 m_projection{ 0 };

	int m_width{ 0 };
	int m_height{ 0 };
};