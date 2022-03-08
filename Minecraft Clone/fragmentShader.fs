#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float Brightness;

// texture samplers
uniform sampler2D texture1;


void main()
{
	FragColor = texture(texture1, TexCoord) * Brightness;
}