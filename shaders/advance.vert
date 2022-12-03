#version 410
// Vertex shader

layout(location = 0) in vec2 vertcoords_clip_vs;

out vec4 line_color;

void main() {
  gl_Position = vec4(vertcoords_clip_vs, 0.0, 1.0);
  line_color = vec4(0.8, 0.3, 0.7, 1.0);
}

