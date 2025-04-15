#version 330
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.

out vec4 color;

layout(std140) uniform Lights{
	vec2 lightPos;
	vec4 lightColor;
	vec3 lightAttenuation;
	float radius;
};
uniform float dayLight;

uniform int lightCount;

uniform sampler2D mySampler;



void main() {

    //cos(x) returns a number between -1 and 1. To convert it into the range 0 to 1
    //you simply do (cos(x) + 1.0) * 0.5


		vec4 textureColor = texture(mySampler, fragmentUV);
		vec4 finalColor = vec4(fragmentColor.r - dayLight , fragmentColor.g - dayLight ,
		fragmentColor.b - dayLight,fragmentColor.a);
		int i;
		for(i = 0 ; i < lightCount ; i++)
		{


		vec2 aux= lightPos - fragmentPosition;
		//vec3 lightAttenuation = vec3(0.025,0.025,0.025);
			if(distance(fragmentPosition,lightPos) < radius)
	     	{
	     		float lapp = length(aux);
	     		float attenuation= 1.0/ (lightAttenuation.x + lightAttenuation.y * lapp + lightAttenuation.z * lapp * lapp);	
	     		finalColor+= vec4(attenuation,attenuation,attenuation,1.0)*vec4(lightColor.rgb,1.0);	
	     	}
     	}

 		color = (finalColor * textureColor);
 		
	

  			  
    //Make crazy colors using time and position!
   

}