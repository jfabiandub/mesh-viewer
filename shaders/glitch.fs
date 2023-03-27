#version 400

   in vec3 FrontColor;
   in vec3 BackColor;

   in vec2 TextCoord;

   layout( location = 0 ) out vec4 FragColor;

   uniform float time;


float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}
   
void main() {

    const float scale = 30.0;

    bvec2 toDiscard = greaterThan( fract(TextCoord * scale),
                                   vec2(0.2,0.2) );
    if( all(toDiscard) )
        discard;
    float randVal = random(TextCoord + time);
    if (randVal > 0.9) {
        discard;
    }
    if (gl_FrontFacing) {
        FragColor = vec4(FrontColor, 1.0);
    } else {
        FragColor = vec4(BackColor, 1.0);
    }
}
