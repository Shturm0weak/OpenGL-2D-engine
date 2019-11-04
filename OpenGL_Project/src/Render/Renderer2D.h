#pragma once
#ifndef RENDERER2D_H
#define RENDERER2D_H

enum Layer {
	LAYER_1 = 1,
	LAYER_2 = 2,
	LAYER_3 = 3,
	LAYER_4 = 4,
	LAYER_5 = 5,
};

class Renderer2D  {
public:
	virtual void Setlayer(Layer layer);
protected:
	std::string name = "";
	static std::vector <std::reference_wrapper<Renderer2D>> collision2d;
	static std::vector <std::reference_wrapper<Renderer2D>> objects2d;
	static void Draw(const VertexArray& va, const IndexBuffer& ib,const Shader& shader);

	void PushObj(Renderer2D& obj) { objects2d.push_back(obj); }
	void PushCol(Renderer2D& col) { collision2d.push_back(col); }
	virtual void OnRunning(glm::mat4 proj);
	virtual float* GetVertexPositions() { return nullptr; }
	virtual double* GetPositions() { return nullptr; }
	friend class Renderer;
	friend class Collision;
	virtual bool IsCollisionEnabled() { return false; }
	virtual Renderer2D* GetCollisionReference() { return nullptr; }
	
};
#endif