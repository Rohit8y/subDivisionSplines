#version 410

layout (isolines) in;

// This type defines if we have quadratic or cubic
// B-splines in the output. Set this to 5 for cubic and
// to 4 for quadratic.
int type = 4;

float[4] getBValuesQuadratic(float t){
    
    float b0 = (1.-t) * (1.-t) * (1.-t);
    float b1 = 3. * t * (1.-t) * (1.-t);
    float b2 = 3. * t * t * (1.-t);
    float b3 = t * t * t;

    float val[4] = float[4](b0,b1,b2,b3);

    return val;
    
}
float[5] getBValuesCubic(float t){
    
    float b0 = (1.-t) * (1.-t) * (1.-t) * (1.-t);
    float b1 = 4. * t * (1.-t) * (1.-t) * (1.-t);
    float b2 = 6. * t * t * (1.-t) * (1.-t);
    float b3 = 4. * t * t * t * (1.-t);
    float b4 = t * t * t * t;

    float val[5] = float[5](b0,b1,b2,b3,b4);

    return val;
    
}

void main() {
    //int type = 2 ;
    vec3 p0 = (gl_in[0].gl_Position).xyz;
    vec3 p1 = (gl_in[1].gl_Position).xyz;
    vec3 p2 = (gl_in[2].gl_Position).xyz;
    vec3 p3 = (gl_in[3].gl_Position).xyz;
    vec3 outputPosition;

    float t = gl_TessCoord.x;   // How far along a line we are (between 0 and 1)
    float v = gl_TessCoord.y;   // Which line we are on
    
    // For Quadratic mask 1 3 3 1
    if (type == 4){
        float[4] basis = getBValuesQuadratic(t);
        
         outputPosition = basis[0]*p0 + basis[1]*p1 + basis[2]*p2 + basis[3]*p3;
    }
    // For cubic mask 1 4 6 4 1
    else if (type == 5){
        vec3 p4 = (gl_in[4].gl_Position).xyz;

        float[5] basis = getBValuesCubic(t);

         outputPosition = basis[0]*p0 + basis[1]*p1 + basis[2]*p2 + basis[3]*p3 + basis[4]*p4;
    }
    gl_Position = vec4(outputPosition.x, outputPosition.y + v*0.2, outputPosition.z, 1.0f);     // Shift different lines vertically
}
