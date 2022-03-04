#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

in float texID;

uniform sampler2DArray textureArray;

//uniform sampler2D texture2;

uniform float brightness;

void main()
{
	FragColor = texture(textureArray, vec3(TexCoord, texID)) * brightness;
}