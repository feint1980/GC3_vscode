#version 330
uniform sampler2D tex;
uniform float time;
uniform vec2 posEffect;
uniform float intensityEffect;
uniform float speed;
in vec2 uv;
out vec4 color;

void main() {

    vec4 color_out = vec4(1.0, 1.0, 1.0,1.0);
	vec2 cPos = 1.0*uv - 1.0;
    float cLength = length(cPos);
	vec2 tex_uv = uv + (cPos/cLength)*cos(cLength*12.0- time *speed)*intensityEffect;
	
	color_out = vec4(texture(tex, tex_uv).rgb,1.0);
	color = color_out;
}
