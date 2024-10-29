#pragma once
#include "Color.h"
#include "Ray.h"

class Material
{
public:
	Material() = default;
	Material(const color3_t& albedo) : m_albedo{ albedo } {}

	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) const = 0;

protected:
	color3_t m_albedo{ 1 };
};

class Lambertian : public Material
{
public:
	Lambertian(const color3_t& albedo) : Material{ albedo } {}
    bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scatter) const override;
};
class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : Material{ albedo }, m_fuzz{ fuzz } {}
    bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, color3_t& attenuation, ray_t& scattered) const override;

protected:
	float m_fuzz = 0;
};




class Emmisive : public Material
{
	//Emissive(const color3_t& albedo, float inensity = 1): Material{albedo}, m_intensity{intensity}{}
	//bool Scatter(const ray_t& ray )
};