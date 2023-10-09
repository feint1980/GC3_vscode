#version 330
uniform sampler2D tex;
//uniform float time;
//uniform vec2 posEffect;
//uniform float intensityEffect;
//uniform float speed;
in vec2 uv;


#define MAX_RIPPLE_COUNT 30

uniform vec2 ripplePos[MAX_RIPPLE_COUNT];
uniform float rippleSize[MAX_RIPPLE_COUNT];
uniform float rippleFreq[MAX_RIPPLE_COUNT];
uniform float rippleLifeTime[MAX_RIPPLE_COUNT];
uniform int rippleCount;
uniform float rippleScale;

out vec4 color;

//uniform vec3 daylight;


float Circle(vec2 uv, vec2 pos, float r , float blur)
{
	float d = length(uv -  pos);
	float c = smoothstep(r, r-blur, d);
	return c * rippleScale ;
}

void main() 
{

	
	vec4 color_out = vec4(1.0, 1.0, 1.0,1.0);

	//vec2 tex_uv = (2.0 * uv - 1.0f) + ripplePos; //uv; 


	vec2 tex_uv = uv;

	//if(time < 18.5f)
	//{
	vec2 tValue ;
	int i ;
	for( i = 0; i < rippleCount; i++)
	{
		tex_uv =   ((1.0*uv - 1.0)  * rippleScale) + ripplePos[i];
		//vec2 cPos =  1.0*uv - 1.0 + ripplePos;
	  //  float cLength = length(cPos);
		float c = Circle(tex_uv, vec2(0.0,0.0), rippleSize[i],rippleFreq[i]);
		float d = length(tex_uv) * rippleScale ;
		tValue +=  ((d) * cos(d * (18.5 - rippleLifeTime[i]) -  rippleLifeTime[i] * 1.0) * 1.0 * c) *rippleScale;
		
	}
	//tex_uv = Circle(uv,cPos,10,10);// uv + (cPos/cLength)*cos(cLength* (18.5f - time ) *speed)*intensityEffect;
	tex_uv = uv + tValue;
	//}
	
	color_out = vec4(texture(tex, tex_uv).rgb,1.0);//* vec4(daylight,1.0) ;
	// if(fragmentPos.x < 0.0f)
	// {
	// 	color_out = vec4(1,0,0,1);
	// }


	color = color_out;


 //    vec4 color_out = vec4(1.0, 1.0, 1.0,1.0);
	// vec2 cPos = 1.0*uv - 1.0;
 //    float cLength = length(cPos);
	// vec2 tex_uv = uv + (cPos/cLength)*cos(cLength*12.0- time *speed)*intensityEffect;
	
	// color_out = vec4(texture(tex, uv).rgb,1.0) ;//;
	// color = color_out;
}

