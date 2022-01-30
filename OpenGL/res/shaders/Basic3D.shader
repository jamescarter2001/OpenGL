#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertexColor;

out vec4 u_Color;

uniform mat4 u_Projection;
uniform mat4 u_Translation;
uniform mat4 u_Rotation;

void main() {
	u_Color = vec4(vertexColor, 1.0);
	gl_Position = u_Projection * u_Translation * u_Rotation * position;
}

#shader fragment
#version 330 core

in vec4 u_Color;

out vec4 color;

void main() {

	color = u_Color;
}