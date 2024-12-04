#include "FragmentShader.h"
#include "Shader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
    //point
   /* glm::vec3 light_position = uniforms.light.position;
    light_position = uniforms.view * glm::vec4{ light_position, 1 };
    glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
    glm::vec3 light_dir = glm::normalize(light_position - vposition);*/
    //Direction
    glm::vec3 light_direction = Shader::uniforms.light.direction;
    glm::vec3 light_position = Shader::uniforms.light.position;

    light_direction = Shader::uniforms.view * glm::vec4{ light_direction, 0 };
    //glm::vec3 vposition = mv * glm::vec4{ fragment.position, 1 };
    glm::vec3 light_dir = glm::normalize(light_direction);


    float intensity = std::max(0.0f, glm::dot(-light_dir, fragment.normal));
    color3_t diffuse = Shader::uniforms.light.color * intensity;
    color3_t color = Shader::uniforms.ambient + diffuse;

	return color4_t{fragment.normal, 1};
}


