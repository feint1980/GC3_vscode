#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;


uniform float time;

void main()
{    

    vec3 fill_col    = vec3(textColor.r, textColor.g, textColor.b); 
    vec3 outline_col = vec3(0.0, 0.0, 0.0); 

    vec2 tex = texture2D(text, TexCoords).rg;
    float fill    = tex.r;
    float outline = tex.g ;

    float alpha    = max( fill, outline  );
    vec3 mix_color = mix( mix(vec3(0.2), fill_col, fill), outline_col,  outline );

    color = vec4(mix_color, alpha * textColor.a);
   
  

} 