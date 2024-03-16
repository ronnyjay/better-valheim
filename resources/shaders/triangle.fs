#version 430 core

uniform sampler2D tex;

in vec2 UV;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(tex, UV);
    if(texColor.a < 0.2)
        discard;
    
    FragColor = vec4(texColor.rgb, 1);
}
