#ifndef  COLLISION_H
#define COLLISION_H
#include "../Render/Renderer2D.h"
#include "../ECS/Component.h"

class Collision : public Renderer2D,public Component {
private:
	const float positions[16] = {
	-0.5f, -0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f};
	float* ScaledVerPos = new float[16];
	const unsigned int indeces[6] = { 0,1,2,3,2,0 };
	struct Position {
		double x = 0;
		double y = 0;
	};
	float* arrver1 = nullptr;
	double* arrpos1 = nullptr;
	float offsetX, offsetY;
	double left, right, top, bottom;
	double diffbt, difftb, diffrl, difflr;
	Collision* col = nullptr;
	Position position;
	glm::vec4 Color = COLORS::White;
	glm::mat4 scale = glm::mat4(1.f);
	glm::mat4 pos = glm::mat4(1.f);
	glm::mat4 MVP = glm::mat4(1.f);
	glm::mat4 view = glm::mat4(1.f);
	glm::mat4 scaleXview = glm::mat4(1.f);

	GLuint vao;
	VertexBufferLayout* layout = new VertexBufferLayout;
	VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	VertexArray* va = new VertexArray;
	IndexBuffer* ib = new IndexBuffer(indeces, 6);
	Shader* shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/newshader.shader");

	virtual void OnRunning(glm::mat4 proj) override;
	
	virtual bool IsCollisionEnabled() override { return Enable; }
	void UpdateCollision(double x, double y, glm::mat4 pos, glm::mat4 view, glm::mat4 scale);
	virtual Renderer2D* GetCollisionReference() override { return this; }
	void RealVerPos();
	float* GetVertexPositions();
	double* GetPositions() {
		double* arr = new double[2];
		arr[0] = position.x;
		arr[1] = position.y;
		return arr;
	};
	double GetDistance(float x1, float y1,float x2,float y2) {
		return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	}

	friend class Basic2D;
	friend class Transform;
public:
	
	static bool IsVisible;
	bool Collided_side_left = false;
	bool Collided_side_right = false;
	bool Collided_side_top = false;
	bool Collided_side_bottom = false;
	double weight = 1;
	double G = -9.8 * weight;
	bool Static = true;
	bool Gravity = false;
	Collision(double x, double y);
	Collision();
	void Scale(float x, float y);
	bool Enable = true;
	void SetOffset(float x, float y);
	bool IsCollided();
};

#endif // ! COLLISION_H