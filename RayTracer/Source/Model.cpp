#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Triangle.h"

#include <iostream>
#include <fstream>
#include <sstream>



bool Model::Load(const std::string& filename)
{
	std::ifstream stream(filename);

	if (!stream.is_open())
	{
		std::cerr << "File: " << filename << " could not be loaded" << std::endl;
		return false;
	}

	vertices_t vertices;
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream iss{ line.substr(2) };
			glm::vec3 vertex;
			iss >> vertex.x;
			iss >> vertex.y;
			iss >> vertex.z;

			vertices.push_back(vertex);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream iss{ line.substr(2) };
			std::string str;
			while (std::getline(iss, str, ' '))
			{
				std::istringstream iss(str);
				std::string indexString;

				size_t i = 0;
				unsigned int index[3] = { 0, 0, 0 };
				while (std::getline(iss, indexString, '/'))
				{
					if (!indexString.empty())
					{
						std::istringstream indexStream{ indexString };
						indexStream >> index[i];
					}
					i++;
				}

				if (index[0])
				{
					glm::vec3 pos = vertices[index[0] - 1];
					m_vertices.push_back(pos);
				}
			}
		}

	}

	stream.close();
	return true;
}

bool Model::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
	// check cast ray with mesh triangles 
	for (size_t i = 0; i < m_vertices.size(); i += 3)
	{	//Create the triangle with the 3 vertex points;
		Triangle triangle(glm::vec3{ m_vertices[i]}, glm::vec3{ m_vertices[i + 1]}, glm::vec3{ m_vertices[i + 2]}, m_material);
		if (triangle.Hit(ray, raycastHit, minDistance, maxDistance))
		{
			return true;
		}
		//std::cout << i << " Of: " << m_vertices.size() << std::endl;
	}
	return false;
}


