#ifndef  COLLISION_H
#define COLLISION_H

#include "../ECS/Component.h"
#include "../Core/EventSystem.h"
#include "Transform.h"

class Collision : public Renderer2DLayer,public Component {
private:
	const float positions[16] = {
	-0.5f, -0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f};
	const unsigned int indeces[6] = { 0,1,2,3,2,0 };

	Collision* col = nullptr;
	Transform* trans = nullptr;

	struct Position {
		float x = 0;
		float y = 0;
	};
	struct Displacement {
		float x = 0;
		float y = 0;
	};

	bool draw_once = false;
	float* arrver1 = nullptr;
	double* arrpos1 = nullptr;
	double left, right, top, bottom;
	double diffbt, difftb, diffrl, difflr;

	glm::vec4 Color = COLORS::White;
	glm::mat4 scale = glm::mat4(1.f);
	glm::mat4 pos = glm::mat4(1.f);
	glm::mat4 MVP = glm::mat4(1.f);
	glm::mat4 view = glm::mat4(1.f);
	glm::mat4 scaleXview = glm::mat4(1.f);
	glm::vec2 NormalVector(glm::vec2 vec2);

	GLuint vao;
	VertexBufferLayout* layout = new VertexBufferLayout;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	VertexArray* va = new VertexArray;
	IndexBuffer* ib = new IndexBuffer(indeces, 6);
	Shader* shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/newshader.shader");

	virtual void OnRunning(OrthographicCamera& camera) override;
	virtual bool IsCollisionEnabled() override { return Enable; }
	void UpdateCollision(double x, double y, glm::mat4 pos, glm::mat4 view, glm::mat4 scale);
	virtual Renderer2DLayer* GetCollisionReference() override { return this; }
	void RealVerPos();
	float* GetVertexPositions();
	double* GetPositions() {
		double* arr = new double[2];
		arr[0] = position.x;
		arr[1] = position.y;
		return arr;
	};
	float AngleToRotate(glm::vec2 v1, glm::vec2 v2);

	double GetDistance(float x1, float y1,float x2,float y2) {
		return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	}
	
	friend class GameObject;
	friend class Transform;
	friend class Editor;
	friend class Renderer;

	Position position;
	Displacement displacement;
	Collision* _collidedObj = nullptr;

	float offsetX, offsetY;
	float* ScaledVerPos = new float[16];
	std::vector<glm::vec2> p;
	std::vector<glm::vec2> pNormals;
	std::vector<glm::vec2> pLocal;
	std::string tag = "General";

	bool Collided_side_left = false;
	bool Collided_side_right = false;
	bool Collided_side_top = false;
	bool Collided_side_bottom = false;
public:
	std::string GetTag() { return tag; }
	virtual void SetId(int id)override { this->id = id; }
	virtual int GetId()override { return id; }

	bool _isCollided = false;
	static bool IsVisible;
	bool IsTrigger = false;

	Collision(double x, double y);
	Collision();

	void Scale(float x, float y);
	void Translate(float x, float y);
	bool Static = false;
	bool Enable = true;
	void SetOffset(float x, float y);
	bool IsCollidedSAT();
	void IsCollidedDIAGS();
};
#endif