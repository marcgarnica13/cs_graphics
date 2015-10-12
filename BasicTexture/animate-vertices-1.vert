#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float amplitude=0.1;
uniform float freq = 1; //Hz

uniform float time;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(normalize(normalMatrix * normal).z);
    vtexCoord = texCoord;
    float distance = 0.1*sin(2*3.1415*freq*time);
    vec3 movedVertex = vertex.xyz + distance*N.xyz;
    gl_Position = modelViewProjectionMatrix * vec4(movedVertex.xyz, 1.0);
}
