#extension GL_OES_standard_derivatives : enable

precision highp float;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	float angle =  time * 0.5;
	float range = 0.004;
	float radius = 100.0 / resolution.x; 
	float t_length = 0.4;
	
	vec2 endPoint = vec2(mouse.x + t_length * cos(angle), mouse.y + t_length * sin(angle));
	
	vec2 position = (gl_FragCoord.xy / resolution); // 1920x1080 gl_FragCoor.xy = 0,0 
	
	
	vec3 color = vec3(0,0,0);//0.0;
	
		//vec3 color = vec3(1,1,1);//0.0;
	color = vec3(0.0,0.0,0.0);
	 	
			
	float f_length = sqrt( pow(position.x - mouse.x,2.0) + pow(position.y - mouse.y,2.0) );
	
	if(f_length < t_length)
	{
	
	
		float a = (position.x - mouse.x);
		float b = (position.y - mouse.y);
		float c = (endPoint.x - mouse.x);
		float d = (endPoint.y - mouse.y);
		if( (a * c  + b * d) <=  (sqrt( a * a  + b * b ) * sqrt( c * c + d * d ) ) +  range  
		  &&  (a * c  + b * d) >=  (sqrt( a * a  + b * b ) * sqrt( c * c + d * d ) ) - range  )
		{
			
						
			color = vec3(1,1,0);
		}
	}
		
	
	gl_FragColor = vec4( color, 1.0 );

}