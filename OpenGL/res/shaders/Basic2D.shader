#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 u_TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;

void main() {
	u_TexCoords = texCoords;
	gl_Position = u_Projection * u_Model * position;
}

#shader fragment
#version 330 core

in vec2 u_TexCoords;

out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {

	vec4 texColor = texture(u_Texture, u_TexCoords);
	color = texColor;
}