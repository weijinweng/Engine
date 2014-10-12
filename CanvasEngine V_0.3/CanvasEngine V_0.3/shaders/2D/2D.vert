#version 330 core

layout (location = 0) vec2 box_2D;
layout (location = 1) vec2 uv_2D;

void main(void)
{
	gl_Position = vec4(location + box_2D,0,1);
	
	uv = uv_2D;
}