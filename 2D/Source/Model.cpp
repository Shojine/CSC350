#include "Model.h"
#include "Framebuffer.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>


void Model::Draw()
{

	Shader::Draw(m_vb);
	
}

bool Model::Load(const std::string& filename)
{
	std::ifstream stream(filename);

	if(!stream.is_open())
	{
		std::cerr << "File: " << filename << " could not be loaded" << std::endl;
		return false;
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.substr(0,2) == "v ") 
		{  
			std::istringstream iss{ line.substr(2) };
			glm::vec3 vertex;
			iss >> vertex.x;
			iss >> vertex.y;
			iss >> vertex.z;

			vertices.push_back(vertex);
		}
		//read in vertex normals
		else if (line.substr(0, 3) == "vn ")
		{
			std::istringstream iss{ line.substr(2) };
			glm::vec3 normal;
			iss >> normal.x;
			iss >> normal.y;
			iss >> normal.z;

			normals.push_back(normal);
		}
		else if (line.substr(0,2) == "f ") 
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
					
					vertex_t vertex;
					vertex.position  = vertices[index[0] - 1];
					vertex.normal = (index[2]) ? normals[index[2] - 1] : glm::vec3{ 1 };

					m_vb.push_back(vertex);
				}
			}
		}
		
	}

	stream.close();  
	return true;
}


