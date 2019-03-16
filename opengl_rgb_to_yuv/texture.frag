#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
float y;
vec4 rgb;
uniform sampler2DRect    ourTexture;
void main()
{
	rgb = texture2DRect(ourTexture, TexCoord);
	y = (0.257 * rgb.r) + (0.504 * rgb.g) + (0.098 * rgb.b) + 0.0625;
	FragColor = vec4(y, 0, 0, 0);
}
