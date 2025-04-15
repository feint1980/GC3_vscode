#version 130

uniform mat4 P;

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;


out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main() {

     gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    //the z position is zero since we are in 2D
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vec4(vec3(vertexColor.x , vertexColor.y , vertexColor.z ) , vertexColor.w) ;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}