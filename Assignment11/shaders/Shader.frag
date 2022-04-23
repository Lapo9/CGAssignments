#version 450

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform GlobalUniformBufferObject {
	float time;
} gubo;

void main() {
	outColor = vec4(cos(gubo.time), cos(0.7 + gubo.time*2), cos(1 + gubo.time*5), 1.0f);
}