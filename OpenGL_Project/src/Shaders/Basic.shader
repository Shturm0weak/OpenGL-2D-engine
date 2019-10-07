#shader vertex
#version 330 core

layout(location = 0) in vec4 positions;
layout(location = 1) in vec2 texcoords;

out vec2 v_textcoords;


uniform mat4 u_MVP;

void main(){
	gl_Position = u_MVP * positions;
	v_textcoords = texcoords;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_textcoords;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){
	vec4 texColor = texture(u_Texture, v_textcoords);
	color = texColor;
};