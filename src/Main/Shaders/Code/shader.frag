#version 450

in vec3 FragNormal;
in vec3 FragPos;

out vec4 FragColor;

const int MAX_POINT_LIGHTS = 16;
const int MAX_SPOT_LIGHTS = 16;
const int MAX_PLANETS_COUNT = 128;
const int MAX_STAR_COUNT = 4;

uniform vec3 EyePosition;

struct Light
{
	vec4 colorWithIntensity;
};

struct AmbientLight
{
	Light light;
};

struct DirectionalLight
{
	Light diffuse;
	Light specular;
	vec3 direction;
};

struct PointLight
{
	vec3 position;
	Light ambient;
	Light diffuse;
	Light specular;
	vec3 k;
	float radius;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float angle;
};

struct Lights
{
	AmbientLight ambient;
	DirectionalLight directional;
	PointLight pointLights[MAX_POINT_LIGHTS];
	SpotLight spotLights[MAX_SPOT_LIGHTS];
	uint pointLightsCount;
	uint spotLightsCount;
};

uniform Lights lights;

struct CelestialBody
{
	vec4 positionAndRadius;
	bool useToCalculateLight;
};

struct Space
{
	CelestialBody planets[MAX_PLANETS_COUNT];
	uint planetsCount;
};

uniform Space space;

struct Material
{
	vec4 albedo;
	float metallic;
	float roughness;
};

uniform Material material;

float GetNearest(vec3 position, CelestialBody celestialBody)
{
	return length(celestialBody.positionAndRadius.xyz - position) - celestialBody.positionAndRadius.w;
}

float GetNearest(vec3 position)
{
	float result = 3.402823466e+38;
	for(int i = 0; i < space.planetsCount; ++i)
	{
		if (space.planets[i].useToCalculateLight)
		{
			float distance = GetNearest(position, space.planets[i]);
			result = min(distance, result);
		}
	}
	return result;
}

float CalculateShadowFactor(vec3 rayOrigin, vec3 normalizedDirection, float distance, float lightRadius)
{
	if (space.planetsCount == 0)
	{
		return 0.0;
	}

	vec3 ray = rayOrigin + normalizedDirection * lightRadius;
	float estimatedDistance = distance - lightRadius;
	float shadow = 1.0;
	if (lightRadius < 1.0)
	{
		lightRadius = 1.0;
	}

	float nearest = 1.0;
	while (estimatedDistance > 0.1)
	{
		if (nearest < 0.00001)
		{
			return shadow;
		}
		nearest = GetNearest(ray);
		estimatedDistance -= nearest;
		shadow = min(shadow, ((distance - estimatedDistance)/distance));
		ray += normalizedDirection * nearest;
	}

	return 0.0;
}

vec3 CalculateLight(Light light)
{
	return light.colorWithIntensity.rgb * light.colorWithIntensity.w;
}

vec3 CalculateLightByDirection(Light diffuse, Light specular, vec3 direction)
{
    float diffuseFactor = max(dot(normalize(FragNormal), normalize(direction)), 0.0f);
    vec3 diffuseColor = CalculateLight(diffuse) * diffuseFactor;
    vec3 specularColor = vec3(0, 0, 0);
    if (diffuseFactor > 0.0f)
    {
        //vec3 fragToEye = normalize(EyePosition - FragPos);
        //vec3 reflectedVertex = normalize(reflect(direction, normalize(FragNormal)));
        //float specularFactor = dot(fragToEye, reflectedVertex);
        //if(specularFactor > 0.0f)
        //{
            //specularFactor = pow(specularFactor, material.shininess);
            //specularColor = CalculateLight(specular) * specularFactor;
        //}
    }

    return diffuseColor;
}

vec3 CalculateLightByDirection(Light ambient, Light diffuse, Light specular, vec3 direction)
{
	return (CalculateLight(ambient) + CalculateLightByDirection(diffuse, specular, direction));
}

vec3 CalculateAmbientLight(AmbientLight ambient)
{
	return CalculateLight(ambient.light);
}

vec3 CalculateDirectionalLight(DirectionalLight directional)
{
    return CalculateLightByDirection(directional.diffuse, directional.specular, directional.direction);
}

vec3 CalculatePointLight(PointLight point)
{
	vec3 ambient = CalculateLight(point.ambient);
    vec3 direction = FragPos - point.position;
    float distance = length(direction);
	if (distance < point.radius)
	{
		return vec3(0.0, 0.0, 0.0);
	}

    direction = normalize(direction);
	vec3 color = CalculateLightByDirection(point.diffuse, point.specular, direction);
	float attenuation = 1.0f / (point.k.x * distance * distance + point.k.y * distance + point.k.z);
	float shadowFactor = CalculateShadowFactor(point.position, direction, distance, point.radius);
	return ambient + (1.0 - shadowFactor) * (color * attenuation);
}

vec3 CalculateSpotLight(SpotLight spot)
{
    vec3 rayDirection = normalize(FragPos - spot.base.position);
    float slFactor = dot(rayDirection, spot.direction);
    if (slFactor > spot.angle)
    {
        vec3 color = CalculatePointLight(spot.base);
        return color * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - spot.angle)));
    }
    else
    {
        return vec3(0, 0, 0);
    }
}

vec3 CalculatePointLights()
{
	vec3 totalColor = vec3(0, 0, 0);
    for(int i = 0; i < lights.pointLightsCount; i++)
    {
        totalColor += CalculatePointLight(lights.pointLights[i]);
    }
    return totalColor;
}

vec3 CalculateSpotLights()
{
	vec3 totalColor = vec3(0, 0, 0);
    for(int i = 0; i < lights.spotLightsCount; i++)
    {
        totalColor += CalculateSpotLight(lights.spotLights[i]);
    }
    return totalColor;
}

vec3 CalculateLight()
{
	vec3 finalColor = CalculateAmbientLight(lights.ambient);
	finalColor += CalculateDirectionalLight(lights.directional);
	finalColor += CalculatePointLights();
	finalColor += CalculateSpotLights();
	return finalColor;
}

void main()
{
	vec4 light = vec4(CalculateLight(), 1.0);
	FragColor = light * material.albedo;
}