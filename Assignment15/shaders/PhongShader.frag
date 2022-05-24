#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightDir;
	vec3 lightPos;
	vec3 lightColor;
	vec3 eyePos;
	vec4 coneInOutDecayExp;
	vec4 selector;
} gubo;




/**** Modify from here *****/

vec3 direct_light_dir(vec3 pos) {
	// Directional light direction
	return gubo.lightDir;
}

vec3 direct_light_color(vec3 pos) {
	// Directional light color
	return gubo.lightColor;
}

vec3 point_light_dir(vec3 pos) {
	// Point light direction
	return normalize(gubo.lightPos - pos);
}

vec3 point_light_color(vec3 pos) {
	// Point light color
	float g = gubo.coneInOutDecayExp.z;
	float beta = gubo.coneInOutDecayExp.w;
	vec3 p = gubo.lightPos;
	vec3 color = gubo.lightColor;

	return color * pow(g / length(p - pos), beta);
}

vec3 spot_light_dir(vec3 pos) {
	// Spot light direction
	return normalize(gubo.lightPos - pos);
}

vec3 spot_light_color(vec3 pos) {
	// Spot light color
	float g = gubo.coneInOutDecayExp.z; // base distance (where the light has the nominal power)
	float beta = gubo.coneInOutDecayExp.w; // distance decay factor
	vec3 p = gubo.lightPos; // position of the light
	vec3 color = gubo.lightColor; // color of the light
	vec3 d = gubo.lightDir; // direction of the light
	float inCone = gubo.coneInOutDecayExp.y; // inner cone (where light is at full power)
	float outCone = gubo.coneInOutDecayExp.x; // outer cone (where light decays)

	float cosine = dot(normalize(p - pos), d);
	vec3 pointLightFactor = color * pow(g / length(p - pos), beta);
	float clampingFactor = clamp((cosine - outCone) / (inCone - outCone), 0.0f, 1.0f);

	return pointLightFactor * clampingFactor;
}

/**** To from here *****/





void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	vec3 lD;	// light direction from the light model
	vec3 lC;	// light color and intensity from the light model
	
	lD = direct_light_dir(fragPos) * gubo.selector.x +
	     point_light_dir(fragPos)  * gubo.selector.y +
	     spot_light_dir(fragPos)   * gubo.selector.z;
	lC = direct_light_color(fragPos) * gubo.selector.x +
	     point_light_color(fragPos)  * gubo.selector.y +
	     spot_light_color(fragPos)   * gubo.selector.z;

	vec3 Diffuse = (texture(texSampler, fragTexCoord).rgb * gubo.selector.w + vec3(1,1,1) * (1-gubo.selector.w)) * (max(dot(Norm, lD),0.0f) );
	vec3 Specular = vec3(pow(max(dot(EyeDir, -reflect(lD, Norm)),0.0f), 64.0f));
	
	outColor = vec4((Diffuse + Specular) * lC, 1.0f);	
}