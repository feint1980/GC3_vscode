#version 130
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

uniform sampler2D mySampler;


void main() {

    vec4 textureColor = texture(mySampler, fragmentUV);
   
	if(fragmentPosition.x >25.0)
   	{

		textureColor.rgb = textureColor.rgb - vec3(100,100,100);
 		 
 		
   	}
   	else
   	{
   		 textureColor.rgb = textureColor.rgb + vec3(100,100,100);
   		
   	}
  	color = fragmentColor * textureColor ;
}