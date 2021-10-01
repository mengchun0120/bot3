#version 110 core

uniform bool useColor;
uniform bool useTexColor;
uniform vec4 color;
uniform vec4 texColor;
uniform sampler2D texture;

in vec2 texCoord;
out vec4 fragColor;

void main()
{
    if(useColor)
    {
        fragColor = color;
    }
    else
    {
        if(useTexColor)
        {
            fragColor = texture2D(texture, texCoord) * texColor;
        }
        else
        {
            fragColor = texture2D(texture, texCoord);
        }
    }
}
