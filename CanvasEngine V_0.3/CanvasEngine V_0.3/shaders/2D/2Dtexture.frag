#version 330 core

out vec4 frag_color;

in vec2 uv;

uniform sampler2D myTexture;

void main(void){
	frag_color = texture(myTexture, uv);
}