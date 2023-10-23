//--- Hexennest
// by Catzpaw 2018
#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

#define OCT 5
#define ITER 80
#define EPS .002
#define NEAR 0.
#define FAR 24.

vec3 rotX(vec3 p,float a){return vec3(p.x,p.y*cos(a)-p.z*sin(a),p.y*sin(a)+p.z*cos(a));}
vec3 rotY(vec3 p,float a){return vec3(p.x*cos(a)-p.z*sin(a),p.y,p.x*sin(a)+p.z*cos(a));}
vec3 rotZ(vec3 p,float a){return vec3(p.x*cos(a)-p.y*sin(a), p.x*sin(a)+p.y*cos(a), p.z);}
vec3 hsv(float h,float s,float v){return ((clamp(abs(fract(h+vec3(0.,.666,.333))*6.-3.)-1.,0.,1.)-1.)*s+1.)*v;}
float hex(vec3 p){vec3 q = abs(p);return max(q.z-.01,max((q.x*.866+q.y*.5),q.y)-.95);}

float map(vec3 p){
    float s=.94,df=1.3;
    p=rotX(p,time*.11);
    p=rotZ(p,time*.27);
    for(int i=0;i<OCT;i++){
        if(p.x>.88){p.x=1.76-p.x;}else if(p.x<-.88){p.x=-1.76-p.x;}
        if(p.y>.88){p.y=1.76-p.y;}else if(p.y<-.88){p.y=-1.76-p.y;}
        if(p.z>.88){p.z=1.76-p.z;}else if(p.z<-.88){p.z=-1.76-p.z;}
        float q=p.x*p.x+p.y*p.y+p.z*p.z;
        if(q<.16){p*=6.25;df*=6.25;}
        else if(q<1.02){p*=1.02/q;df*=1.02/q;}
        p*=s;df*=s;     
    }
    return (hex(p))/df;
}

float trace(vec3 ro,vec3 rd,out float n){float t=NEAR,d;
    for(int i=0;i<ITER;i++){d=map(ro+rd*t);if(abs(d)<EPS||t>FAR)break;t+=step(d,1.)*d*.2+d*.5;n+=1.;}
    return min(t,FAR);}

void main(void){
    vec2 uv=(vec2(gl_FragCoord.x + 250, gl_FragCoord.y)-.5*resolution.xy)/resolution.y;
    float n=0.,v=trace(vec3(0,1,sin(time*.3)*1.5-2.),vec3(uv,.5),n)*.05;n/=float(ITER);
    gl_FragColor=vec4(mix(hsv(1.15-n*.1,.9,v),vec3(1),(v*.2)*(n*5.)),1);
}
