#include "VertexShader.h"
#include "Shader.h"



void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
    glm::mat4 mvp = Shader::uniforms.projection * Shader::uniforms.view * Shader::uniforms.model;
    overtex.position = mvp * glm::vec4{ ivertex.position, 1 };
    glm::mat4 mv = Shader::uniforms.view * Shader::uniforms.model;
    overtex.normal = glm::vec3{ glm::normalize(glm::mat3{ mv } *ivertex.normal) };
    overtex.vposition = mv * glm::vec4{ ivertex.position, 1 };
    //defined is 0 so it's not defined
//#ifdef 0
//    //point
//    glm::vec3 light_position = uniforms.light.position;
//    light_position = uniforms.view * glm::vec4{ light_position, 1 };
//    glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
//    glm::vec3 light_dir = glm::normalize(light_position - vposition);
//    //Direction
//    glm::vec3 light_direction = Shader::uniforms.light.direction;
//    light_direction = Shader::uniforms.view * glm::vec4{ light_direction, 0 };
//    glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
//    glm::vec3 light_dir = glm::normalize(-light_direction);
//
//
//    float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));
//
//    color3_t diffuse = Shader::uniforms.light.color * intensity;
//    overtex.color =Shader:: uniforms.ambient + diffuse;
//#endif // 0
}