#include "../pch.h"
#include "Renderer.h"
#include <iostream>
#include "../Core/Collision.h"


void Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DeleteObject(Renderer2D& obj) {
	for (unsigned int i = 0; i < Renderer2D::objects2d.size(); i++)
	{	
		if (&Renderer2D::objects2d[i].get() == &obj) {
			std::cout << Renderer2D::objects2d[i].get().name << " is deleted" << std::endl;
			
			for (unsigned int j = 0; j < Renderer2D::collision2d.size(); j++)
			{
				if (&Renderer2D::collision2d[j].get() == Renderer2D::objects2d[i].get().GetCollisionReference()) {
					Renderer2D::collision2d.erase(Renderer2D::collision2d.begin() + j);
					break;
				}
			}
			Renderer2D::objects2d.erase(Renderer2D::objects2d.begin() + i);
			return;
		}
	}
}


void Renderer::Render(glm::mat4 proj)
{
	for (unsigned int i = 0; i < Renderer2D::objects2d.size(); i++) {
		Renderer2D::objects2d[i].get().OnRunning(proj);
	}
	if (Collision::IsVisible == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (unsigned int i = 0; i < Renderer2D::collision2d.size(); i++) {
			if (Renderer2D::collision2d[i].get().GetCollisionReference() != nullptr) {
				if (Renderer2D::collision2d[i].get().IsCollisionEnabled()) {
					Renderer2D::collision2d[i].get().OnRunning(proj);
				}
			}
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}