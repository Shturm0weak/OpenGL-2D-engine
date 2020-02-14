#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <mutex>
#include "OrthographicCamera.h"

class Renderer2DLayer  {
private:

public:
	virtual void Setlayer(int layer);
	virtual int GetId() { return 0; }
	static int GetAmountOfObjects() { return objects2d.size(); }
	static int GetAmountOfCollisions() { return collision2d.size(); }
	enum RenderType { Render2D, Render3D };
	int& GetLayer() { return layer; }
protected:
	friend class Renderer;
	friend class Collision;
	friend class ComponentManager;

	
	Renderer2DLayer() { layer = objects2d.size(); }
	int id = 0;
	int layer = 0;
	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	std::string* type = new std::string("");
	std::string* name = new std::string("");
	static std::vector <std::reference_wrapper<Renderer2DLayer>> collision2d;
	static std::vector <std::reference_wrapper<Renderer2DLayer>> objects2d;
	static int obj_id;
	static int col_id;
	RenderType rendertype = Render2D;
	void PushObj(Renderer2DLayer& obj) { objects2d.push_back(obj); }
	void PushCol(Renderer2DLayer& col) { collision2d.push_back(col); }
	virtual void OnRunning(OrthographicCamera& camera);
	virtual void SetId(int id) {}
	virtual float* GetVertexPositions() { return nullptr; }
	virtual float* GetColor() { return nullptr; }
	virtual float* GetScale() { return nullptr; }
	virtual float GetAngle() { return 0; }
	virtual double* GetPositions() { return nullptr; }
	virtual int GetRenderType() { return rendertype; }
	virtual int GetShaderType() { return 1; }
	virtual std::string* GetPathToTexture() { return nullptr; }
	virtual bool IsCollisionEnabled() { return false; }
	virtual Renderer2DLayer* GetCollisionReference() { return nullptr; }
	virtual ComponentManager* GetComponentManager() { return nullptr; };
};
#endif

