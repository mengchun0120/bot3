#version 330

uniform vec4 color;

in float alpha;
out vec4 fragColor;
uniform sampler2D pointTexture;

void main()
{
    if (alpha <= 0.0)
    {
        discard;
    }
    else
    {
        fragColor = texture(pointTexture, gl_PointCoord) * vec4(color.rgb, alpha);
    }
}
