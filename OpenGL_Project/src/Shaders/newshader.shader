#shader vertex
#version 330 core

layout(location = 0) in vec4 positions;


uniform mat4 u_MVP;

void main() {
	gl_Position = u_MVP * positions;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 U_Color;

void main() {
	color = U_Color;
};