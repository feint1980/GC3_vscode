#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{

    gl_Position.xy = (projection * vec4(vertex.xy, 0.0, 1.0)).xy;
    TexCoords = vertex.zw;
}

