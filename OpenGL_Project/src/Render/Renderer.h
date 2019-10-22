#pragma once

#include "glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "../vendor/glm/gtc/type_ptr.hpp"

class Renderer {
protected:
	static std::vector <std::reference_wrapper<Renderer>> objects2d;
	virtual void OnRunning(glm::mat4 proj);
	static void Draw(const VertexArray& va, const IndexBuffer& ib,const Shader& shader) ;
	void PushObj(Renderer& obj) { objects2d.push_back(obj); };
public:
	static void Render(glm::mat4 proj);
	static void Clear();
};