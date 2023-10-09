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


float getTrianglePerimeter(float a, float b, float c)
{
	
	return (a + b + c ) / 2.0f;	
}

float getTriangleSize(float a, float b, float c)
{	
	float p = getTrianglePerimeter(a,b,c);
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

float getCalculateLine(vec2 point1, vec2 point2)
{
	return sqrt( pow(point1.x - point2.x,2.0f) + pow(point1.y - point2.y,2.0f));
}

void main() {

		vec4 textureColor = texture(mySampler, fragmentUV);
		vec4 finalColor = vec4(fragmentColor.r + dayLight.x -1.0f , fragmentColor.g + dayLight.y - 1.0f ,
		fragmentColor.b + dayLight.z -1.0f ,fragmentColor.a);
		int i;

		float t_radius = 2000.1f;
		float t_length = 7000.4f;


		float addedRot2 = 1.57079632679f * 1.0f;
		float addedRot = 1.57079632679f * 2.0f;

		for(i = 0 ; i < rayCount ; i++)
     	{

	
     		vec2 sidePointA = vec2(rayLightPos[i].x + t_radius * cos(rayRotation[i] + addedRot2), rayLightPos[i].y + t_radius * sin(rayRotation[i] + addedRot2));
			vec2 sidePointB = vec2(rayLightPos[i].x - t_radius * cos(rayRotation[i] + addedRot2), rayLightPos[i].y - t_radius * sin(rayRotation[i] + addedRot2));

			//vec2 endPoint = vec2(rayLightPos[i].x + t_length * cos(rayRotation[i] + addedRot), rayLightPos[i].y + t_length * sin(rayRotation[i] + addedRot));
			//vec2 sidePointC = vec2(endPoint.x + t_radius * cos(rayRotation[i] + addedRot2), endPoint.y + t_radius * sin(rayRotation[i] + addedRot2));
			//vec2 sidePointD = vec2(endPoint.x - t_radius * cos(rayRotation[i] + addedRot2), endPoint.y - t_radius * sin(rayRotation[i] + addedRot2));
			vec2 sidePointC = vec2(sidePointB.x + t_length * cos(rayRotation[i] + addedRot), sidePointB.y + t_length * sin(rayRotation[i] + addedRot));
			vec2 sidePointD = vec2(sidePointA.x + t_length * cos(rayRotation[i] + addedRot), sidePointA.y + t_length * sin(rayRotation[i] + addedRot));
		
			float AD = t_length;
			float BC = t_length;
			float AB = 2.0f * t_radius;
			float CD = 2.0f * t_radius; 
		
			float OA = getCalculateLine(fragmentPosition,sidePointA );
			float OB = getCalculateLine(fragmentPosition,sidePointB );
			float OC = getCalculateLine(fragmentPosition,sidePointC );
			float OD = getCalculateLine(fragmentPosition,sidePointD );

			float rectangleSize = t_length * ( 2.0f * t_radius );

			if((distance(fragmentPosition,rayLightPos[i]) < 1000.0f) )
	     	{

	     		vec2 aux= rayLightPos[i] - fragmentPosition;
	     		float lapp = length(aux) * 0.25f;
	     		float attenuation= 1/ (rayLightAtten[i].x + rayLightAtten[i].y * lapp  + rayLightAtten[i].z * lapp * (1.0f/lapp));	
	     		finalColor+= vec4(attenuation,attenuation,attenuation,1.0)*vec4(rayLightColor[i]);	
	     		finalColor.a = fragmentColor.a;
	     	}
			if(rectangleSize + 1400.1f >= (getTriangleSize(AB,OA,OB ) + getTriangleSize(AD,OA,OD) +  getTriangleSize(CD,OC,OD) + getTriangleSize(BC,OC,OB) ) )
			{		
				float radius = 200.0f / rayLightAtten[i].z;
     			float aux =  (rayLightPos[i].x - fragmentPosition.x) * cos(rayRotation[i] + 1.57079632679) + (rayLightPos[i].y - fragmentPosition.y) * sin(rayRotation[i] + 1.57079632679); 	
     			//vec2 aux= (rayLightPos[i] - fragmentPosition) * 0.05f;
     			float lapp = length(aux) * 200/ distance(fragmentPosition.y,rayLightPos[i].y);

	     		float attenuation= 1 / (rayLightAtten[i].x + rayLightAtten[i].y * lapp  + rayLightAtten[i].z * lapp * (1.0f/lapp) ) ;	
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