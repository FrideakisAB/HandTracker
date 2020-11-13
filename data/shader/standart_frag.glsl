#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 main_color = vec3(0.28,0.23,0.97);

void main()
{   
	FragColor = vec4(main_color, 1.0);
}