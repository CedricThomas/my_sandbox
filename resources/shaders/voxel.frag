#version 330 core

layout (location = 0) out vec4 o_Color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D v_Texture;

void main()
{
   o_Color = texture(v_Texture, v_TexCoord);
}