#version 450

layout (binding=0) uniform TransformMatrices {
	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} transformMatrices;

layout (location=0) in vec3 inPosition;
layout (location=1) in vec3 inNormal;
layout (location=2) in vec2 inTexCoord;

layout (location=0) out vec3 worldPos;
layout (location=1) out vec3 worldNormal;
layout (location=2) out vec2 texCoord;
	

void main() {
	gl_Position = transformMatrices.mvpMat * vec4(inPosition, 1.0f);
	worldPos = (transformMatrices.mMat * vec4(inPosition, 1.0f)).xyz;
	worldNormal = mat3(transformMatrices.nMat) * inNormal;
	texCoord = inTexCoord;
}