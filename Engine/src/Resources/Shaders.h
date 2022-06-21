#pragma once
#include <Engine/Containers/String.h>

Engine::String g_UnlitTextureVertexShader = R"glsl(
#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUv;

out vec2 f_Uv;

uniform mat4 v_Mvp;

void main()
{
	gl_Position = v_Mvp*vec4(aPosition,1.0f);
	f_Uv = aUv;
}
)glsl";

Engine::String g_UnlitTextureFragmentShader = R"glsl(
#version 450 core

out vec4 f_ColorOut;

in vec2 f_Uv;

uniform sampler2D f_Texture;
uniform float f_Tiling;
void main()
{
	vec4 texColor = texture2D(f_Texture,f_Uv*f_Tiling);
	f_ColorOut = texColor;
}
)glsl";

Engine::String g_UIVertexShader = R"glsl(
#version 450 core
layout(location = 0) in vec2 aPosition;

uniform mat4 v_Ortho;
uniform vec2 v_Position;
void main()
{
	gl_Position = v_Ortho*vec4(aPosition + v_Position,0.0f,1.0f);
}
)glsl";

Engine::String g_UIFragmentShader = R"glsl(
#version 450 core

out vec4 f_ColorOut;

uniform vec3 f_Color;
void main()
{
	f_ColorOut = vec4(f_Color,1.0f);
}
)glsl";

Engine::String g_LitTextureVertexShader = R"glsl(
#version 450 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUv;

out vec2 f_Uv;
out vec3 f_Normal;
out vec3 f_WorldPos;

uniform mat4 v_Mvp;
uniform mat4 v_Model;

void main()
{
	gl_Position = v_Mvp*vec4(aPosition,1.0f);
	f_Uv = aUv;
	f_WorldPos = (v_Model*vec4(aPosition,1.0f)).xyz;
	f_Normal = mat3(transpose(inverse(v_Model)))*aNormal;
}
)glsl";

Engine::String g_LitTextureFragmentShader = R"glsl(
#version 450 core

out vec4 f_ColorOut;

in vec2 f_Uv;
in vec3 f_Normal;
in vec3 f_WorldPos;

#define MEAN_AMBIENT 0.2f
#define MAX_LIGHT 6

uniform vec3 f_ViewPos;

uniform sampler2D f_Texture;

uniform float f_Tiling;

uniform int f_PointLightCount;
uniform vec3 f_PointLightPositions[MAX_LIGHT];
uniform vec3 f_PointLightColors[MAX_LIGHT];
uniform float f_PointLightRanges[MAX_LIGHT];

uniform int f_SpotLightCount;
uniform vec3 f_SpotLightPositions[MAX_LIGHT];
uniform vec3 f_SpotLightColors[MAX_LIGHT];
uniform float f_SpotLightRanges[MAX_LIGHT];
uniform float f_SpotLightAngles[MAX_LIGHT];
uniform vec3 f_SpotLightDirections[MAX_LIGHT];

void main()
{
	vec4 ambient = vec4(0,0,0,0);
	for(int i = 0;i<f_PointLightCount;i++)
	{
		vec3 pos = f_PointLightPositions[i];
		vec3 color = f_PointLightColors[i];
		float range = f_PointLightRanges[i];
		
		vec3 lightDir = normalize(pos- f_WorldPos);
		vec3 viewDir = normalize(f_ViewPos-f_WorldPos);
		vec3 halfwayDir = normalize(lightDir + viewDir);

		float power = max(0.0f,pow(range/distance(pos,f_WorldPos),2));

		float spec = pow(max(dot(f_Normal,halfwayDir),0.0f),0.35f);
		
		ambient += vec4(color,1.0f)*spec*power;
	}
	
	for(int i = 0;i<f_SpotLightCount;i++)
	{
		vec3 pos = f_SpotLightPositions[i];
		vec3 dir = f_SpotLightDirections[i];
		vec3 color = f_SpotLightColors[i];
		float range = f_SpotLightRanges[i];
		float angle = f_SpotLightAngles[i];

		vec3 lightDir = normalize(pos- f_WorldPos);
		vec3 viewDir = normalize(f_ViewPos-f_WorldPos);
		vec3 halfwayDir = normalize(lightDir + viewDir);

		float cutoff = dot(lightDir, normalize(-dir));
		cutoff = cutoff > radians(angle) ? 1.0f : 0.0f;

		float power = max(0.0f,pow(range/distance(pos,f_WorldPos),2));
		float spec = pow(max(dot(f_Normal,halfwayDir),0.0f),0.35f);

		ambient += vec4(color,1.0f)*spec*power*cutoff;
	}

	vec4 finalColor = texture2D(f_Texture,f_Uv*f_Tiling);
	f_ColorOut = finalColor*ambient;
}
)glsl";