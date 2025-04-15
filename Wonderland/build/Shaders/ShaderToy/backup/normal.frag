#version 330
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.

out vec4 color;

uniform sampler2D mySampler;

uniform vec3 dayLight;
#define MAX_LIGHT_COUNT 330
uniform vec2 lightPos[MAX_LIGHT_COUNT];
uniform vec4 lightColor[MAX_LIGHT_COUNT];
uniform vec3 lightAttenuation[MAX_LIGHT_COUNT];

uniform int lightCount;

void main() {

		vec4 textureColor = texture(mySampler, fragmentUV);
		vec4 finalColor = vec4(fragmentColor.r + dayLight.x -1.0f , fragmentColor.g + dayLight.y - 1.0f ,
		fragmentColor.b + dayLight.z -1.0f ,fragmentColor.a);
		int i;
		for(i = 0 ; i < lightCount ; i++)
		{

		float radius = 400 /lightAttenuation[i].z;
		vec2 aux= lightPos[i] - fragmentPosition;
		//vec3 lightAttenuation = vec3(0.025,0.025,0.025);
			if(distance(fragmentPosition,lightPos[i]) < radius)
	     	{
	     		float lapp = length(aux);
	     		float attenuation= 1/ (lightAttenuation[i].x + lightAttenuation[i].y * lapp  + lightAttenuation[i].z * lapp * (1.0f/lapp));	
	     		finalColor+= vec4(attenuation,attenuation,attenuation,1.0)*vec4(lightColor[i]);	
	     		finalColor.a = fragmentColor.a;
	     	}
     	}

 		color = (finalColor * textureColor);
 		
   

}