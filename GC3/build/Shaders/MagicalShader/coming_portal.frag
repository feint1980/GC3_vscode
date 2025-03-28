#ifdef GL_ES
precision mediump float;
#endif

// glslsandbox uniforms
uniform float time;
uniform vec2 resolution;
//LEAN SWIRL -ඞ sussy guy
// shadertoy emulation
#define iTime time
#define iResolution vec3(resolution,1.)

uniform int reach;
uniform float alphaRate;

void mainImage(out vec4 O, vec2 I)
{
    vec3 p=iResolution,d = -.5*vec3(I+I-p.xy,p)/p.x,c = d-d, i=c;
    for(int x=0;x<reach;++x) {
        if (i.x>=1.) break;
        p = c,
        p.z -= iTime+(i.x+=.01),
        p.xy *= mat2(sin((p.z*=.1)+vec4(0,11,33,0)));
        c += length(sin(p.yx)+cos(p.xz+iTime))*d;
    }
    O = vec4(7
         ,0,8,9)/length(c);
}


void main(void)
{
    mainImage(gl_FragColor, gl_FragCoord.xy);
    gl_FragColor.rgb = gl_FragColor.rgb * 0.55;
    gl_FragColor.a = alphaRate;
}
