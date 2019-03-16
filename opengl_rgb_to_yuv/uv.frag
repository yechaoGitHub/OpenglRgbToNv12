#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
float u; float v;
vec4 rgb;
uniform sampler2DRect    ourTexture;
void main()
{
	rgb = texture2DRect(ourTexture, TexCoord);
	v = (0.439 * rgb.r) - (0.368 * rgb.g) - (0.071 * rgb.b) + 0.500;
	u = -(0.148 * rgb.r) - (0.291 * rgb.g) + (0.439 * rgb.bs) + 0.500;
	FragColor = vec4(v, u, 0, 0);
}
