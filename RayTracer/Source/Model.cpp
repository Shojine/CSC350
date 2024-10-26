#include "Model.h"
#include "Framebuffer.h"
#include "Camera.h"

#include <iostream>
#include <fstream>
#include <sstream>


void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model, Camera& camera)
{
	
	
}

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


