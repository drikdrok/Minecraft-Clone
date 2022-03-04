#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float block;
layout (location = 3) in float aBrightness;

out vec2 TexCoord;
out float brightness;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform int block;

float sheetSize = 4.0f;


void main()
{
    brightness = aBrightness;

    float x = (aTexCoord.x + block) / sheetSize;
    float y = (aTexCoord.y + floor(block / sheetSize)) / sheetSize;

    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    //TexCoord = vec2(aTexCoord.x,  1.0f - aTexCoord.y );
    TexCoord = vec2(x,  1.0f - y);

}