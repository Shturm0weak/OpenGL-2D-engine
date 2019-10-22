#include "Renderer.h"
#include <iostream>

 void Renderer::Render(glm::mat4 proj)
{
	 for (unsigned int i = 0; i < objects2d.size(); i++) {
		 objects2d[i].get().OnRunning(proj);
	 }
}

void Renderer::OnRunning(glm::mat4 proj){

}

/*void Renderer::OnCollision() {
	for (unsigned int i = 0; i < objects2d.size(); i++) {
		glm::vec2 v1(glm::value_ptr(objects2d[i].get().GetMVP())[12], glm::value_ptr(objects2d[i].get().GetMVP())[13]);
			if (v1.x > 1. || v1.x < -1.) {		
				objects2d[i].get().SetAngle(3.14159 - objects2d[i].get().GetAngle());	
			}
			else if (v1.y > 1. || v1.y < -1.) {
				objects2d[i].get().SetAngle(3.14159 - (objects2d[i].get().GetAngle() - 3.14159));
			}
		for (unsigned int j = 0; j < objects2d.size(); j++)
		{
			if (i != j && !objects2d[i].get().collide && !objects2d[j].get().collide) {
				glm::vec2 v2(glm::value_ptr(objects2d[j].get().GetMVP())[12], glm::value_ptr(objects2d[j].get().GetMVP())[13]);

				if (glm::distance(v1, v2) <= 0.04f)
				{
					objects2d[i].get().SetSpeed(0.f);
					objects2d[j].get().SetSpeed(0.f);
					objects2d[i].get().collide = true;
					objects2d[j].get().collide = true;
				}
			}
		}
	}
}*/

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
	shader.Bind(); 
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES,ib.GetCount(), GL_UNSIGNED_INT,nullptr);
}

void Renderer::Clear(){
	glClear(GL_COLOR_BUFFER_BIT);
}
