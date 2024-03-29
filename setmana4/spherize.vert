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
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;
    //Per fer la projecció del vertex en una esfero de radi unitat, simplement hem de normalitzar
    //les coordenades del vertex
    /*float modul = sqrt(pow(vertex.x, 2) + pow(vertex.y, 2) + pow(vertex.z, 2));
    vec3 V = vertex.xyz/ modul;*/
    vec3 V = normalize(vertex);
    gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
}
