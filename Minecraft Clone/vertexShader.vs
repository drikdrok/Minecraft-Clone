#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aBlock;
layout (location = 3) in float aBrightness;

out vec2 TexCoord;
out float Brightness;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

float sheetSize = 4.0f;


void main()
{
    Brightness = aBrightness;

    float x = (aTexCoord.x + aBlock) / sheetSize;
    float y = (aTexCoord.y + floor(aBlock / sheetSize)) / sheetSize;

    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoord = vec2(x,  1.0f - y);

}