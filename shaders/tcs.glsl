#version 410
 
// Uniform variables that update from
// the draw function of tessellation shader
uniform float noIsolines;
uniform float noSplit;

// vertices = n ; n = # of control points per patch
// For quadratic B-spline Tessellation set this to 4,
// otherwise for cubic set it to 5.
layout (vertices = 4) out;

void main(void) {

    // Define Tessellation level
    if (gl_InvocationID == 0) {
        // Specify the tessellation levels
        gl_TessLevelOuter[0] = noIsolines;    // # of isolines
        gl_TessLevelOuter[1] = noSplit;    // # of splits in each line
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}


