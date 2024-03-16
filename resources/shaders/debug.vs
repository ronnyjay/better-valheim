#version 430 core

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec3 color;

uniform mat4 MVP;

out vec3 vertex_color;

void main(){
  gl_Position = MVP * vec4(vertices, 1);
  vertex_color = color;
}