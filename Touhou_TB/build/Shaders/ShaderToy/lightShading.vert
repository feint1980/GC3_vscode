#version 330
//The vertex shader operates on each vertex

layout(std140) uniform Matrices{
	mat4 P
}


//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

//uniform ;

void main() {
 
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
 
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;
    
    fragmentUV = vertexUV;
}