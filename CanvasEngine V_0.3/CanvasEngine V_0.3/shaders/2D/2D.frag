#version 330 core

layout (location = 0) vec3 frag_color;

uniform vec4 color;

void main(void){
	frag_color = color;
}
