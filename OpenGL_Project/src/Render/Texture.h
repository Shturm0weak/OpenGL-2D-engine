#pragma once
#include "glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "../vendor/glm/gtc/type_ptr.hpp"

class Texture {
private:
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_width, m_height, m_BPP;
public:
	unsigned int m_RendererID;
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};
