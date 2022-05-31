#version 450

layout (binding=3) uniform sampler2D specularColors;

layout (binding=1) uniform sampler2D diffuseColors;

layout (binding=2) uniform Info {
	vec3 lightDir;
	vec3 lightPos;
	vec3 lightColor;
	vec4 lightParams;
	vec3 eyePos;
} info;

layout (location=0) in vec3 worldPos;
layout (location=1) in vec3 worldNormal;
layout (location=2) in vec2 texCoord;

layout (location=0) out vec4 outColor;


/*Calculates the relative direction between the light source and the considered point
x --> position of the point 
p --> position of the light source
*/
vec3 calculateSpotLightDirection(vec3 x, vec3 p) {
	return (p-x) / length(p-x);
}


/*Calculates the power (so basically the color) of the light hitting the point
x --> position of the point 
p --> position of the light source
l --> color of the light
sd --> direction of the spot light
cIn --> inner cone angle (where all the light arrives)
cOut --> outer cone angle (where the light starts dimming)
g --> nominal distance (see formula)
B --> beta decaying factor (see formula)
*/
vec3 calculateSpotLightPower(vec3 x, vec3 p, vec3 l, vec3 sd, float cIn, float cOut, float g, float B) {
	vec3 light = l * pow(g / length(p-x), B);
	float dimming = clamp((dot((p-x)/length(p-x), sd) - cOut) / (cIn - cOut), 0.0f, 1.0f);
	return light * dimming;
}


/*Calculates the diffuse color of the point by using Lambert formula
c --> nominal diffuse reflection color of the point
d --> relative direction between the point and the light source
n --> normal to the point
*/
vec3 calculateDiffuseLambert(vec3 c, vec3 d, vec3 n) {
	return c * max(dot(d, n), 0.0f);
}


/*Calculates the specular color of the considered point by using the Phong formula
c --> nominal speculat reflection color of the point
d --> relative direction between the point and the light source
n --> normal to the point
o --> direction of the observer in respect to the point 
gamma --> gamma --> power factor of the Phong formula
*/
vec3 calculateSpecularPhong(vec3 c, vec3 d, vec3 n, vec3 o, float gamma) {
	vec3 r = -reflect(d, n);
	return c * clamp(pow(dot(o, r), gamma), 0.0f, 1.0f);
}

void main() {
	vec3 lightDirection = calculateSpotLightDirection(worldPos, info.lightPos);
	vec3 lightPower = calculateSpotLightPower(worldPos, info.lightPos, info.lightColor, info.lightDir, info.lightParams.x, info.lightParams.y, info.lightParams.w, info.lightParams.z);
	vec3 diffuseColor = calculateDiffuseLambert(texture(diffuseColors, texCoord).rgb, lightDirection, worldNormal);
	vec3 specularColor = calculateSpecularPhong(texture(specularColors, texCoord).rgb, lightDirection, worldNormal, (info.eyePos-worldPos) / length(info.eyePos-worldPos), texture(specularColors, texCoord).a * 200.0f);

	outColor = vec4(clamp(lightPower * (diffuseColor + specularColor), 0.0f, 1.0f), 1.0f);
}