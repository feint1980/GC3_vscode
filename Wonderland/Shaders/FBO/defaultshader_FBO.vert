#version 330
in vec3 vpoint;
in vec2 vtexcoord;
out vec2 uv;

//out vec2 ripplePos;

uniform mat4 P;

out vec2 fragmentPos;

void main() {
   gl_Position = vec4(vpoint, 1.0);
   fragmentPos = vec4(vpoint, 1.0).xy;
   //ripplePos =  (P * vec4(tPos, 0.0, 1.0)).xy;
   uv = vtexcoord;
}
