#version 410
// Fragment shader

in vec4 line_color;
out vec4 fColor;
//out vec4(0.8, 0.8, 0.8, 1.0) fColor;
//layout (location = 0) in vec3 pos_in;


void main() {
  fColor = line_color;
  //gl_Position = vec4(pos_in, 1.0);

}
