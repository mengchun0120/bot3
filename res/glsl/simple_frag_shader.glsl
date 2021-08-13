uniform bool useColor;
uniform bool useTexColor;
uniform vec4 color;
uniform vec4 texColor;
uniform sampler2D texture;

in vec2 texCoord;

void main() {
    if(useColor)
    {
        gl_FragColor = color;
    }
    else
    {
        if(useTexColor)
        {
            gl_FragColor = texture2D(texture, texCoord) * texColor;
        }
        else
        {
            gl_FragColor = texture2D(texture, texCoord);
        }
    }
}
