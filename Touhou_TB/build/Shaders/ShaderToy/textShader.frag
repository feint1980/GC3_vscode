#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;


uniform float time;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r * time );

    // Crazy Color 
    color = vec4(textColor.x * (cos(time) +1 * TexCoords.x ) * 0.5 , TexCoords.y * (cos(time + 2) +1) * 0.5 ,textColor.y * (sin(time + 1 ))*0.5,1) * sampled;

  // Original 
   //color = vec4(textColor.x,textColor.y,textColor.z,1) * sampled;
} 