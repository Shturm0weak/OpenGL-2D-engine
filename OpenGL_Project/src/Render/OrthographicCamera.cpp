#include "OrthographicCamera.h"
#include "../vendor/glm/gtc/matrix_transform.hpp"

OrthographicCamera::OrthographicCamera(float left,float right,float top,float bottom)
	: m_ProjectionMatrix(glm::ortho(left * zoomlevel,right * zoomlevel,bottom * zoomlevel,top * zoomlevel,-1.f,1.f)),m_ViewMatrix(1.0f)
{
	aspectration[0] = left;
	aspectration[1] = right;
	aspectration[2] = top;
	aspectration[3] = bottom;
}

void OrthographicCamera::RecalculateViewMatrix() {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
	* glm::rotate(glm::mat4(1.0f), m_Rotation,glm::vec3(0,0,1));
	
	m_ViewMatrix = glm::inverse(transform);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::Increase(float deltatime)
{
}

void OrthographicCamera::Decrease(float deltatime)
{
}

void OrthographicCamera::Zoom(float zoomlevel)
{
	m_ProjectionMatrix = glm::ortho(aspectration[0] * zoomlevel,aspectration[1] * zoomlevel,aspectration[3] * zoomlevel,aspectration[2] * zoomlevel,-1.0f,1.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
