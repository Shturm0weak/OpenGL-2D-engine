#pragma once
#include "../Render/Renderer2D.h"
class Renderer{
public:
	static void DeleteObject(Renderer2DLayer& obj);
	static void Render(glm::mat4 proj);
	static void Clear();
};