#include "../pch.h"
#include "Renderer.h"
#include <iostream>
#include "../Core/Collision.h"


void Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DeleteObject(Renderer2DLayer& obj) {
	for (unsigned int i = 0; i < Renderer2DLayer::objects2d.size(); i++)
	{	
		if (&Renderer2DLayer::objects2d[i].get() == &obj) {
			std::cout << Renderer2DLayer::objects2d[i].get().name << " is deleted" << std::endl;
			
			for (unsigned int j = 0; j < Renderer2DLayer::collision2d.size(); j++)
			{
				if (&Renderer2DLayer::collision2d[j].get() == Renderer2DLayer::objects2d[i].get().GetCollisionReference()) {
					Renderer2DLayer::collision2d.erase(Renderer2DLayer::collision2d.begin() + j);
					break;
				}
			}
			Renderer2DLayer::objects2d.erase(Renderer2DLayer::objects2d.begin() + i);
			return;
		}
	}
}


void Renderer::Render(glm::mat4 proj)
{
	for (unsigned int i = 0; i < Renderer2DLayer::objects2d.size(); i++) {
		Renderer2DLayer::objects2d[i].get().OnRunning(proj);
	}
	if (Collision::IsVisible == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (unsigned int i = 0; i < Renderer2DLayer::collision2d.size(); i++) {
			if (Renderer2DLayer::collision2d[i].get().GetCollisionReference() != nullptr) {
				if (Renderer2DLayer::collision2d[i].get().IsCollisionEnabled()) {
					Renderer2DLayer::collision2d[i].get().OnRunning(proj);
				}
			}
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}