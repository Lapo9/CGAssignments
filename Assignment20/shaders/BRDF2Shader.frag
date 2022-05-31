#version 450

layout (binding=3) uniform sampler2D specularColors;

layout (binding=1) uniform sampler2D ambientColors;

layout (binding=2) uniform Info {
	vec3 lightDir;
	vec3 lightColor;
	vec3 eyePos;
} info;

layout (location=0) in vec3 worldPos;
layout (location=1) in vec3 worldNormal;
layout (location=2) in vec2 texCoord;

layout (location=0) out vec4 outColor;


//Calculates the direction of the directional light (basically useless)
vec3 calculateDirectionalLightDirection(vec3 d) {
	return d;
}


//Calculates the color of the directional light (basically useless)
vec3 calculateDirectionalLightPower(vec3 l) {
	return l;
}


/*Calculates the specular reflection based on the Blinn formula
c --> nominal specular reflection color of the point
d --> direction of the light source in respect to the point
n --> normal to the point 
o --> direction of the observer in respect to the point 
gamma --> power factor of the Blinn formula
*/
vec3 calculateSpecularBlinn(vec3 c, vec3 d, vec3 n, vec3 o, float gamma) {
	vec3 h = normalize(d + o);
	return c * clamp(pow(dot(n, h), gamma), 0.0f, 1.0f);
}


/*Calculates the ambient reflection by using the uniform ambient technique
a --> ambient light emission color
c --> nominal ambient reflection color of the point
*/
vec3 calculateUniformAmbient(vec3 a, vec3 c) {
	return a * c;
}


void main() {
	vec3 lightDirection = calculateDirectionalLightDirection(info.lightDir);
	vec3 lightPower = calculateDirectionalLightPower(info.lightColor);
	vec3 ambientColor = calculateUniformAmbient(vec3(1.0f, 1.0f, 1.0f), texture(ambientColors, texCoord).rgb);
	vec3 specularColor = calculateSpecularBlinn(texture(specularColors, texCoord).rgb, lightDirection, worldNormal, (info.eyePos-worldPos) / length(info.eyePos-worldPos), texture(specularColors, texCoord).a);

	outColor = vec4(clamp(lightPower * (specularColor + ambientColor), 0.0f, 1.0f), 1.0f);
}