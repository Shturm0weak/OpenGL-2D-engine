#include "../pch.h"
#include "Renderer2D.h"

void Renderer2D::OnRunning(glm::mat4 proj){

}

void Renderer2D::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
	shader.Bind(); 
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES,ib.GetCount(), GL_UNSIGNED_INT,nullptr);
}

void Renderer2D::Setlayer(Layer layer)
{
	unsigned int size = Renderer2D::objects2d.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if ((std::addressof(Renderer2D::objects2d[i].get()) == std::addressof(*this))) {
			std::cout << Renderer2D::objects2d[i].get().name << " is set from layer " << i << " to " << layer << std::endl;
			for (int j = 0; j < size; j++)
			{
				std::iter_swap(Renderer2D::objects2d.begin() + i, Renderer2D::objects2d.end() - layer - j);
				std::iter_swap(Renderer2D::collision2d.begin() + i, Renderer2D::collision2d.end() - layer - j);
			}
			return;
		}
	}
	
}
