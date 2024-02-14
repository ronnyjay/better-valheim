#version 430 core

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec2 vertexUV;

uniform mat4 MVP;

out vec2 UV;
  
void main(){
  gl_Position =  MVP * vec4(vertices,1);

  UV = vertexUV;
}