#include "FragmentShader.h"
#include "Shader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
  
    glm::vec3 light_direction = Shader::uniforms.light.direction;
    glm::vec3 light_position = Shader::uniforms.light.position;

    light_direction = Shader::uniforms.view * glm::vec4{ light_direction, 0 };
    //glm::vec3 vposition = mv * glm::vec4{ fragment.position, 1 };
    glm::vec3 light_dir = glm::normalize(light_direction);





    float intensity = std::max(0.0f, glm::dot(-light_dir, fragment.normal));


    color3_t diffuse = Shader::uniforms.light.color * intensity;
    color3_t specular = color3_t(0.0f);

    if (intensity > 0.0f)
    {
        glm::vec3 reflection = glm::reflect(light_direction, fragment.normal);
        glm::vec3 view_direction = glm::normalize(-fragment.position);

        float spec_intensity = std::max(glm::dot(reflection, view_direction), 0.0f);
        spec_intensity = std::pow(spec_intensity, Shader::uniforms.material.shininess); // Apply shininess factor

        specular = Shader::uniforms.material.specular * Shader::uniforms.light.color * spec_intensity;
    }
    color3_t color = ((Shader::uniforms.ambient + diffuse) * Shader::uniforms.material.albedo) + specular;

    return color4_t{ color, 1 };//color
}


