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
#define MAX_LIGHT_COUNT 300 // total is 330, 30 for light ray , 300 is for spotlight 
#define MAX_RAY_COUNT 30
uniform vec2 lightPos[MAX_LIGHT_COUNT];
uniform vec4 lightColor[MAX_LIGHT_COUNT];
uniform vec3 lightAttenuation[MAX_LIGHT_COUNT];

uniform int lightCount;


uniform vec2 rayLightPos[MAX_RAY_COUNT];
uniform vec4 rayLightColor[MAX_RAY_COUNT];
uniform vec3 rayLightAtten[MAX_RAY_COUNT];
uniform float rayRotation[MAX_RAY_COUNT];
uniform int rayCount;

void main() {

		vec4 textureColor = texture(mySampler, fragmentUV);
		vec4 finalColor = vec4(fragmentColor.r + dayLight.x -1.0f , fragmentColor.g + dayLight.y - 1.0f ,
		fragmentColor.b + dayLight.z -1.0f ,fragmentColor.a);
		int i;

		for(i = 0 ; i < rayCount ; i++)
     	{
     		float radius = 300.0f / rayLightAtten[i].z;
     		float aux =  (rayLightPos[i].x - fragmentPosition.x) * cos(rayRotation[i] + 1.57079632679f) + (rayLightPos[i].y - fragmentPosition.y) * sin(rayRotation[i] + 1.57079632679);
     		
     		//if(cos(angle) * (position.y - pos1.y) >= sin(angle) * (position.x - pos1.x) - 0.001 &&
	  		//cos(angle) * (position.y - pos1.y) <= sin(angle) * (position.x - pos1.x) + 0.001 )   
     		
	     			// if((mod(rayRotation[i],6.28318530718f) >= 0.0f && 
	     			//     mod(rayRotation[i],6.28318530718f) < 3.14159265359f &&
	     			// 	fragmentPosition.x < rayLightPos[i].x) 
	     			// 	||
	     			// 	(mod(rayRotation[i],6.28318530718f) >= 3.14159265359f && 
	     			//     mod(rayRotation[i],6.28318530718f) < 6.28318530718f &&
	     			// 	fragmentPosition.x > rayLightPos[i].x)) 

     			if((mod(rayRotation[i],6.28318530718f) > 0.0f && 
				     mod(rayRotation[i],6.28318530718f) < 1.57079632679f 
				     &&  fragmentPosition.x > rayLightPos[i].x 
				 
				     && fragmentPosition.y > rayLightPos[i].y) 
				     ||
				    (mod(rayRotation[i],6.28318530718f) > 1.57079632679f && 
				     mod(rayRotation[i],6.28318530718f) < 3.14159265359f
				      && fragmentPosition.x < rayLightPos[i].x 
				     && fragmentPosition.y > rayLightPos[i].y)
				     
				     ||
				    (mod(rayRotation[i],6.28318530718f) > 3.14159265359f && 
				     mod(rayRotation[i],6.28318530718f) < 4.71238898038f
				      && fragmentPosition.x < rayLightPos[i].x 
				     && fragmentPosition.y < rayLightPos[i].y ) 
				     
				     ||
				    (mod(rayRotation[i],6.28318530718f) > 4.71238898038f && 
				     mod(rayRotation[i],6.28318530718f) < 6.28318530718f 
				     && fragmentPosition.x > rayLightPos[i].x 
				      && fragmentPosition.y < rayLightPos[i].y) )
	     			{

	     				if(    sin(rayRotation[i]) * ( fragmentPosition.y - rayLightPos[i].y)  >= cos(rayRotation[i]) * (fragmentPosition.x - rayLightPos[i].x) - radius
     						&& sin(rayRotation[i]) * ( fragmentPosition.y - rayLightPos[i].y)  <= cos(rayRotation[i]) * (fragmentPosition.x - rayLightPos[i].x) + radius)
     		  	  // 650 is the value offset of Y
     					{
						float lapp = length(aux * 2.5f/ distance(fragmentPosition,rayLightPos[i]) * 400.0f);

		     			 float attenuation= 4.5 / (rayLightAtten[i].x + rayLightAtten[i].y * lapp  + rayLightAtten[i].z * lapp * (1.0f/lapp) ) ;	
		     			finalColor+= vec4(attenuation,attenuation,attenuation,1.0)*vec4(rayLightColor[i]);	
		     			finalColor.a = fragmentColor.a;
		     			}
	     			}
	     			else
	     			{
	     				vec2 aux =  (rayLightPos[i] - fragmentPosition);

	     				float lapp = length(aux * 2.5f/ distance(fragmentPosition,rayLightPos[i]) * 400.0f);

		     			 float attenuation= 4.5 / (rayLightAtten[i].x + rayLightAtten[i].y * lapp  + rayLightAtten[i].z * lapp *0.1f * (1.0f/lapp) ) ;	
	     				finalColor+= vec4(attenuation,attenuation,attenuation,1.0)*vec4(rayLightColor[i]);	
		     			finalColor.a = fragmentColor.a;

	     			}
     		}	

     	
		for(i = 0 ; i < lightCount ; i++)
		{

		float radius = 400.0f /lightAttenuation[i].z;
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