#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    vec4 position = modelViewProjectionMatrix * vec4(vertex.xyz, 1.0);
    position.z = -position.z;
    gl_Position = position;
}