//define the version GLSL 
#version 130
//The vertex shader operates on each vertex

//input data from the VBO. Each position of vertex is 2 floats
in vec2 vertexPosition;
//input data from the VBO. Each color of vertex is 4 floats
in vec4 vertexColor;
//input data from the VBO. Each UV of vertex is 2 floats
in vec2 vertexUV;

// out put the data for fragment shader
out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

// A uniform variable for Camera 
uniform mat4 P;

void main() {
    //Set the x,y position on the screen
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;

    //the z position is zero since we are in 2D
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0f;
  
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;

    // In openGL the texture will be invert vertically so we use 1 - vertextUV.y . 	
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}