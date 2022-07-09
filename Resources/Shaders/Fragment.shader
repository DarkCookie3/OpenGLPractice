#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec4 addColor;

void main()
{
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord) * addColor, 0.7 * addColor.x + 0.2) ;
}