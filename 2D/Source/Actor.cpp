#include "Actor.h"

void Actor::Draw()
{
	VertexShader::uniforms.model = m_transform.GetMatrix();
	m_model->Draw();
}
