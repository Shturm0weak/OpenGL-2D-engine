#pragma once

#include "glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "../vendor/glm/gtc/type_ptr.hpp"
class Renderer {
public:
	bool collide = false;
	std::vector <std::reference_wrapper<Renderer>> objects2d;
	void Render(glm::mat4 proj, double deltatime);
	virtual void OnRunning(glm::mat4 proj, Renderer& renderer, double deltatime);
	void OnCollision();
	glm::mat4 a;
	inline virtual glm::mat4& GetMVP() { return a; };
	inline virtual glm::mat4& GetNormals() { return a; };
	inline virtual void SetSpeed(float speed) {};
	inline virtual float GetSpeed() { return 0; }
	inline virtual void SetAngle(double angle) {};
	inline virtual double GetAngle() { return 0; }
	void Draw(const VertexArray& va, const IndexBuffer& ib,const Shader& shader) const;
	void Clear() const;
};