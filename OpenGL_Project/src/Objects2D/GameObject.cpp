#include "../pch.h"
#include "GameObject.h"

GameObject::GameObject(const std::string name,float x, float y) {
	*Renderer2DLayer::name = name;
	*Renderer2DLayer::type = "GameObject";
	id = Renderer2DLayer::obj_id;
	Renderer2DLayer::obj_id++;
	component_manager = new ComponentManager(this, *this->name);
	component_manager->AddComponent<Transform>();
	component_manager->GetComponent<Transform>()->position.x = position.x = x;
	component_manager->GetComponent<Transform>()->position.y = position.y = y;
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	if (rendertype == Render2D) {
		this->layout->Push<float>(2);
		this->layout->Push<float>(2);
	}
	else if (rendertype == Render3D)
	{
		this->layout->Push<float>(2);
		this->layout->Push<float>(2);
	}
	this->va->AddBuffer(*this->vb, *this->layout);
	InitShader();
	this->va->UnBind();
	this->shader->UnBind();
	this->vb->UnBind();
	this->ib->UnBind();
	Renderer2DLayer::PushObj(*this);
}
GameObject::GameObject() {
	*Renderer2DLayer::name = "Unnamed";
	*Renderer2DLayer::type = "GameObject";
	id = Renderer2DLayer::obj_id;
	Renderer2DLayer::obj_id++;
	component_manager = new ComponentManager(this,*this->name);
	component_manager->AddComponent<Transform>();
	component_manager->GetComponent<Transform>()->position.x = position.x = 0;
	component_manager->GetComponent<Transform>()->position.y = position.y = 0;
	this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
	this->viewXscale = scale * view;
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	if (rendertype == Render2D) {
		this->layout->Push<float>(2);
		this->layout->Push<float>(2);
	}
	else if (rendertype == Render3D)
	{
		this->layout->Push<float>(2);
		this->layout->Push<float>(2);
	}
	this->va->AddBuffer(*this->vb, *this->layout);
	InitShader();
	this->va->UnBind();
	this->shader->UnBind();
	this->vb->UnBind();
	this->ib->UnBind();
	Renderer2DLayer::PushObj(*this);
}

void GameObject::SetName(const char * _name)
{
	delete name;
	name = new std::string(_name);
}

void GameObject::OnRunning(OrthographicCamera& camera) {
	if (Static == false) {
		this->shader->Bind();
		this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
		this->viewXscale = scale * view;
		this->MVP = camera.GetProjectionMatrix() * pos * viewXscale;
		camera.RecalculateViewMatrix();
		this->shader->UploadUnifromMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		this->shader->SetUniformMat4f("u_MVP", this->MVP);
		if (shadertype == SHADER_TEXTURE)
			this->texture->Bind(this->texture->m_RendererID);
	}
	else if (Static == true && draw_once == false) {
		this->shader->Bind();
		this->pos = translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0));
		this->viewXscale = scale * view;
		this->MVP = camera.GetProjectionMatrix() * pos * viewXscale;
		camera.RecalculateViewMatrix();
		this->shader->UploadUnifromMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		this->shader->SetUniformMat4f("u_MVP", this->MVP);
		if (shadertype == SHADER_TEXTURE)
			this->texture->Bind(this->texture->m_RendererID);
		draw_once = true;
	}
	Renderer2DLayer::Draw(*this->va, *this->ib, *this->shader);
}


void GameObject::SetTexture(const std::string& path) {
	if (this->texture != (void*)0xCCCCCCCC || this->texture != nullptr) {
		delete(texture);
		texture = nullptr;
	}
	*pathToTexture = path;
	texture = new Texture(path);
	if(ShaderType::SHADER_TEXTURE != shadertype)
		SetShader(GameObject::SHADER_TEXTURE);
}

void GameObject::InitShader() {
	if (texture == (void*)0xCCCCCCCC && shadertype == SHADER_TEXTURE || texture == nullptr && shadertype == SHADER_TEXTURE) {
		std::cout << yellow << "InitShader" << " : " << red << "Texture doesn't exist!" << white << std::endl;
		shadertype = SHADER_COLOR;
	}
	if (shader != (void*)0xCCCCCCCC || shader != nullptr) {
		shader->UnBind();
		delete(shader);
		shader = nullptr;
	}
	if (shadertype == SHADER_TEXTURE) {
		shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/Basic.shader");
		shader->Bind();
		this->texture->Bind(this->texture->m_RendererID);
		this->shader->SetUniform1i("u_Texture", this->texture->m_RendererID);
	}
	else if (shadertype == SHADER_COLOR) {
		shader = new Shader("C:/Users/Alexandr/source/repos/OpenGL/OpenGL_Project/src/Shaders/newshader.shader");
		shader->Bind();
		shader->SetUniform4fv("U_Color",this->color);
	}
}

void GameObject::SetShader(int _enum) {
	if (_enum == 1) {
		shadertype = SHADER_COLOR;
		if (this->texture != (void*)0xCCCCCCCC && this->texture != nullptr) {
			delete texture;
			texture = nullptr;
		}
		InitShader();
	}
	else if (_enum == 0) {
		shadertype = SHADER_TEXTURE;
		InitShader();
	}
}

void GameObject::SetRenderType(RenderType type)
{
	rendertype = type;
	delete va;
	delete vb;
	delete ib;
	layout->Clear();
	va = new VertexArray();
	if (rendertype == Render2D) {
		ib = new IndexBuffer(indeces2D,6);
		vb = new VertexBuffer(mesh2D, 4 * 4 * sizeof(float));
		this->layout->Push<float>(2);
		this->layout->Push<float>(2);
	}
	else if (rendertype == Render3D)
	{
		ib = new IndexBuffer(indeces3D, 36);
		vb = new VertexBuffer(mesh3D, 24 * sizeof(float));
		this->layout->Push<float>(3);
	}
	this->va->AddBuffer(*this->vb, *this->layout);
}

void GameObject::SetColor(vec4 color) {
	if (this->color == color)
		return;
	this->color = color;
	SetShader(GameObject::SHADER_COLOR);
}

double* GameObject::GetPositions(){
	double* arr = new double[3];
	if (component_manager->GetComponent<Transform>() != nullptr) {
		arr[0] = component_manager->GetComponent<Transform>()->position.x;
		arr[1] = component_manager->GetComponent<Transform>()->position.y;
		arr[2] = component_manager->GetComponent<Transform>()->position.z;
	}
	else {
		arr[0] = position.x;
		arr[1] = position.y;
		arr[2] = 0;
	}
	return arr;
}

std::string* GameObject::GetPathToTexture() { return this->pathToTexture; }

float* GameObject::GetColor() { 
	float* color = new float[4];
	for (unsigned int i = 0; i < 4; i++)
	{
		color[i] = this->color[i];
	}
	return color;
}

int GameObject::GetRenderType() { return rendertype; }

int GameObject::GetShaderType() { return shadertype; }

float* GameObject::GetScale() {	return scaleinfo;}

float GameObject::GetAngle() { return component_manager->GetComponent<Transform>()->angle; }
