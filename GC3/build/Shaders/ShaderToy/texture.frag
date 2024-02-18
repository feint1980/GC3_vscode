#version 130
//The fragment shader operates on each pixel in a given polygon

// get input from vertext shader
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// the color will be output on the screen
out vec4 color;
// uniform variable for Texture

uniform sampler2D mySampler;

void main() {
	// get the color based on texture and UV
    vec4 textureColor = texture(mySampler, fragmentUV);
    // set the color will be output 

    color = fragmentColor * textureColor;

}