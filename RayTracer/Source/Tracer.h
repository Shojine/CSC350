#pragma once
#include "Color.h"


class Tracer
{
public:
	Tracer() = default;

	static color3_t Trace(class Scene& scene, const class ray_t& ray);
	
private:

};