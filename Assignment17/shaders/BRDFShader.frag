#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(binding = 2) uniform GlobalUniformBufferObject {
	// Direct lights parameters (for diffuse and specular)
	vec3 lightDir0;
	vec3 lightColor0;
	vec3 lightDir1;
	vec3 lightColor1;
	vec3 lightDir2;
	vec3 lightColor2;
	vec3 lightDir3;
	vec3 lightColor3;

	// Ambient light parameters
	vec3 AmbColor;	// also Bottom color for Hemispheric light,
					//      Constant term for Spherical Harmonics light
	vec3 TopColor;	// also DyColor for Spherical Harmonics light
	vec3 DzColor;
	vec3 DxColor;
	
	// Other parameters (not relevant for the exercise)
	vec3 eyePos;
	vec4 selector;
} gubo;

/**** Modify from here *****/

layout (location = 2) in vec2 fragTexCoord;
layout (location = 1) in vec3 fragNorm;
layout (location = 0) in vec3 fragPos;

layout (location = 0) out vec4 outColor;


/* 
Oren Nayar Diffuse + Ambient
No Specular
One directional light (lightDir0 and lightColor0)

Parameters are:

vec3 N : normal vector
vec3 V : view direction
vec3 Cd : main color (diffuse color)
vec3 Ca : ambient color
float sigma : roughness of the material 
*/
vec3 Case1_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca, float sigma) {
	vec3 lightIntensity = gubo.lightColor0;

	vec3 L = gubo.lightDir0;
	float sigmaI = acos(dot(L, N));
	float sigmaR = acos(dot(V, N));
	float alpha = max(sigmaI, sigmaR);
	float beta = min(sigmaI, sigmaR);
	float A = 1.0f - 0.5f * pow(sigma, 2) / (pow(sigma, 2) + 0.33f);
	float B = 0.45f * pow(sigma, 2) / (pow(sigma, 2) + 0.09f);
	vec3 vI = normalize(L - dot(L, N) * N);
	vec3 vR = normalize(V - dot(V, N) * N);
	float G = max(dot(vI, vR), 0.0f);
	vec3 l = Cd * clamp(dot(L, N), 0.0f, 1.0f);

	vec3 diffuseColor = l * (A + B * G * sin(alpha) * tan(beta));

	vec3 ambientColor = gubo.AmbColor * Ca;

	return lightIntensity * diffuseColor + ambientColor;
}


/* 
Lambert Diffuse + Hemispheric
No Specular
One directional light (lightDir0 and lightColor0)
Hemispheric light oriented along the y-axis

Parameters are:

vec3 N : normal vector
vec3 V : view direction
vec3 Cd : main color (diffuse color)
vec3 Ca : ambient color
*/
vec3 Case2_Color(vec3 N, vec3 V, vec3 Cd, vec3 Ca) {
	vec3 d = vec3(0.0f, 1.0f, 0.0f); // direction of the top ambient color
	
	vec3 lightIntensity = gubo.lightColor0;

	vec3 diffuseColor = Cd * max(dot(gubo.lightDir0, N), 0.0f);

	vec3 lU = gubo.TopColor;
	vec3 lD = gubo.AmbColor;
	vec3 ambientColor = (((dot(N, d) + 1) / 2.0f) * lU + ((1 - dot(N, d)) / 2.0f) * lD) * Ca;

	return lightIntensity * diffuseColor + ambientColor;
}


/*
Spherical Harmonics
Blinn Specular
Four directional lights (lightDir0 to lightDir3, and lightColor0 to lightColor3)

Parameters are:

vec3 N : normal vector
vec3 V : view direction
vec3 Cs : specular color
vec3 Ca : ambient color
float gamma : Blinn exponent
*/
vec3 Case3_Color(vec3 N, vec3 V, vec3 Cs, vec3 Ca, float gamma)  {
	
	return Ca;
}



/**** To here *****/




void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos.xyz - fragPos);
	
	float AmbFact = 0.025;
	
	vec3 DifCol = texture(texSampler, fragTexCoord).rgb * gubo.selector.w +
				  vec3(1,1,1) * (1-gubo.selector.w);

	vec3 CompColor = gubo.selector.x *
						Case1_Color(Norm, EyeDir, DifCol, DifCol, 1.2f) +
					 gubo.selector.y *
						Case2_Color(Norm, EyeDir, DifCol, DifCol) +
					 gubo.selector.z *
						Case3_Color(Norm, EyeDir, vec3(1.0f,1.0f,1.0f), DifCol, 200.0f);
	
	outColor = vec4(CompColor, 1.0f);	
}