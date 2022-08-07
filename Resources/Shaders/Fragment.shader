#version 330 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

out vec4 FragColor;

struct Material 
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	float shininess;
};

struct SpotLight 
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutOff;
	float cutOffOuter;

	float constant;
	float linear;
	float quadratic;
};

struct DirLight 
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight 
{
	vec3 position;
	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct MaterialSampledTextures
{
	vec4 matDiffTexture;
	vec4 matSpecTexture;
};

#define NR_POINT_LIGHTS 4
#define NR_DIR_LIGHTS 1
#define NR_SPOT_LIGHTS 1

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirLight dirLights[NR_DIR_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform vec3 viewPos;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

MaterialSampledTextures sampledTextures;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	sampledTextures.matDiffTexture = texture(material.texture_diffuse1, TexCoords);
	sampledTextures.matSpecTexture = texture(material.texture_specular1, TexCoords);

	if (sampledTextures.matDiffTexture.a == 0.0)
	{
		discard;
	}

	vec3 result = vec3(0.0, 0.0, 0.0);

	for (int i = 0; i < NR_DIR_LIGHTS; i++)
	{
		result += CalcDirLight(dirLights[i], norm, viewDir);
	}
	
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}

	for (int i = 0; i < NR_SPOT_LIGHTS; i++)
	{
		result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
	}

	FragColor = vec4(result, sampledTextures.matDiffTexture.a);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	vec3 reflectDir = reflect(-lightDir, normal);

	float diff = max(dot(normal, lightDir), 0.0);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 ambient = light.ambient * sampledTextures.matDiffTexture.rgb;
	vec3 diffuse = light.diffuse * diff * sampledTextures.matDiffTexture.rgb;
	vec3 specular = light.specular * spec * sampledTextures.matSpecTexture.rgb;

	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	float diff = max(dot(normal, lightDir), 0.0);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	vec3 ambient = light.ambient * sampledTextures.matDiffTexture.rgb;
	vec3 diffuse = light.diffuse * diff * sampledTextures.matDiffTexture.rgb;
	vec3 specular = light.specular * spec * sampledTextures.matSpecTexture.rgb;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.cutOffOuter;
	float intensity = clamp((theta - light.cutOffOuter) / epsilon, 0.0, 1.0);

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 diffuse = vec3(0.0, 0.0, 0.0);
	vec3 specular = vec3(0.0, 0.0, 0.0);

	if (theta > light.cutOffOuter)
	{
		float diff = max(dot(norm, lightDir), 0.0);
		diffuse = light.diffuse * diff * sampledTextures.matDiffTexture.rgb * attenuation;
		diffuse *= intensity;

		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		specular = light.specular * spec * sampledTextures.matSpecTexture.rgb * attenuation;
		specular *= intensity;
	}

	vec3 ambient = light.ambient * sampledTextures.matDiffTexture.rgb * attenuation;

	return ambient + diffuse + specular;
}