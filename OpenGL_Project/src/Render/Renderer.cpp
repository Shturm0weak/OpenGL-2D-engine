#include "../pch.h"
#include "Renderer.h"
#include <iostream>


void Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DeleteAll() {
	for (unsigned int i = 0; i < Renderer2DLayer::objects2d.size(); i++)
	{
		delete(&Renderer2DLayer::objects2d[i].get());
	}
	for (unsigned int i = 0; i < Renderer2DLayer::collision2d.size(); i++)
	{
		delete(&Renderer2DLayer::collision2d[i].get());
	}
	Renderer2DLayer::collision2d.clear();
	Renderer2DLayer::objects2d.clear();
	Renderer2DLayer::col_id = 0;
	Renderer2DLayer::obj_id = 0;
}

void Renderer::DeleteObject(int id) {
	if (Renderer2DLayer::objects2d[id].get().GetCollisionReference() != nullptr) {
		int _id = Renderer2DLayer::objects2d[id].get().GetCollisionReference()->GetId();
		Renderer2DLayer* col = Renderer2DLayer::objects2d[id].get().GetCollisionReference();
		
		std::unique_ptr<Renderer2DLayer> my_p_col(new Renderer2DLayer(std::move(*col)));
		Renderer2DLayer::collision2d.erase(_id + Renderer2DLayer::collision2d.begin());	

		Renderer2DLayer::col_id--;
		int size = Renderer2DLayer::collision2d.size();
		if (_id != size) {
			for (unsigned int i = _id; i < size; i++)
			{
				Renderer2DLayer::collision2d[i].get().SetId(i);
			}
		}
	}
	Renderer2DLayer* go = &Renderer2DLayer::objects2d[id].get();
	std::unique_ptr<Renderer2DLayer> my_p_obj(new Renderer2DLayer(std::move(*go)));

	Renderer2DLayer::objects2d.erase(Renderer2DLayer::objects2d.begin() + id);	
	Renderer2DLayer::obj_id--;
	int size = Renderer2DLayer::objects2d.size();
	if (id != size) {
		for (unsigned int i = 0; i < size; i++)
		{
			Renderer2DLayer::objects2d[i].get().SetId(i);
			Renderer2DLayer::objects2d[i].get().GetLayer() = i;
		}
	}
}

void Renderer::Save(const std::string filename) {
	std::ofstream out_file;
	out_file.open(filename, std::ofstream::trunc);
	if (out_file.is_open()) {
		for (unsigned int i = 0; i < Renderer2DLayer::objects2d.size(); i++)
		{
			if (Renderer2DLayer::objects2d[i].get().type->c_str() == "GameObject")
				continue;
			double* pos = Renderer2DLayer::objects2d[i].get().GetPositions();
			float* color = Renderer2DLayer::objects2d[i].get().GetColor();
			float* scale = Renderer2DLayer::objects2d[i].get().GetScale();
			out_file << *Renderer2DLayer::objects2d[i].get().name << "\n"
				<< *Renderer2DLayer::objects2d[i].get().type << "\n"
				<< Renderer2DLayer::objects2d[i].get().GetShaderType() << "\n"
				<< pos[0] << " " << pos[1] << "\n"
				<< Renderer2DLayer::objects2d[i].get().GetAngle() << "\n";
			if (static_cast<ComponentManager*>(Renderer2DLayer::objects2d[i].get().GetComponentManager())->GetComponent<Collision>() != nullptr) {
				out_file << 1 << "\n";
				out_file << static_cast<ComponentManager*>(Renderer2DLayer::objects2d[i].get().GetComponentManager())->GetComponent<Collision>()->offsetX
					<< " " << static_cast<ComponentManager*>(Renderer2DLayer::objects2d[i].get().GetComponentManager())->GetComponent<Collision>()->offsetY << "\n";
			}
			else {
				out_file << 0 << "\n";
				out_file << 0 << " " << 0 << "\n";
			}
			if (Renderer2DLayer::objects2d[i].get().GetShaderType() == 0){
				out_file << *Renderer2DLayer::objects2d[i].get().GetPathToTexture() << "\n";
				out_file << color[0] << " " << color[1] << " " << color[2] << " " << 255 << "\n";
			}
			else if (Renderer2DLayer::objects2d[i].get().GetShaderType() == 1) {
				out_file << "None" << "\n";
				out_file << color[0] << " " << color[1] << " " << color[2] << " " << color[3] << "\n";
			}
			out_file << scale[0] << " " << scale[1] << " " << scale[2];
			if (i + 1 != Renderer2DLayer::objects2d.size())
				out_file << "\n";
			delete pos;
			delete color;
		}
	}
	else {
		std::cout << "Error: filename doesn't exist";
	}

	out_file.close();
}

void Renderer::Load(const std::string filename)
{
	DeleteAll();
	std::string name = "";
	std::string type = "";
	std::string pathtotext = "";
	bool hascollision = 0;
	float angle = 0;
	double pos[2];
	float scale[3];
	float color[4];
	float offset[2];
	int shadertype = 1;
	std::ifstream in_file;
	in_file.open(filename);
	if (in_file.is_open()) {
		while (in_file.peek() != EOF) {
				in_file >> name;
				//std::cout << name << std::endl;
				in_file >> type;
				//std::cout << type << std::endl;
				in_file >> shadertype;
				//std::cout << shadertype << std::endl;
				in_file >> pos[0] >> pos[1];
				//std::cout << pos[0] << "	" << pos[1] << std::endl;
				in_file >> angle;
				//std::cout << angle << std::endl;
				in_file >> hascollision;
				//std::cout << hascollision << std::endl;
				in_file >> offset[0] >> offset[1];
				//std::cout << offset[0] << " " << offset[1] << std::endl;
				in_file >> pathtotext;
				//std::cout << pathtotext << std::endl;
				in_file >> color[0] >> color[1] >> color[2] >> color[3];
				//std::cout << color[0] << "	" << color[1] <<  "	" << color[2] << "	" << color[3] << std::endl;
				in_file >> scale[0] >> scale[1] >> scale[2];
				//std::cout << scale[0] << "	" << scale[1] << "	" << scale[2] << std::endl;
				if (type == "GameObject") {		
					LoadObj<GameObject>(name, pathtotext, angle, color, scale, pos, shadertype,hascollision,offset);
				}
		}
	}
	in_file.close();
}

void Renderer::Render(OrthographicCamera& camera)
{
	for (unsigned int i = 0; i < Renderer2DLayer::objects2d.size(); i++) {
		if(&Renderer2DLayer::objects2d[i].get() != nullptr)
			Renderer2DLayer::objects2d[i].get().OnRunning(camera);
	}
	if (Collision::IsVisible == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (unsigned int i = 0; i < Renderer2DLayer::collision2d.size(); i++) {
			if (Renderer2DLayer::collision2d[i].get().GetCollisionReference() != nullptr) {
				if (Renderer2DLayer::collision2d[i].get().IsCollisionEnabled()) {
					Renderer2DLayer::collision2d[i].get().OnRunning(camera);	
				}
			}
		}	
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}