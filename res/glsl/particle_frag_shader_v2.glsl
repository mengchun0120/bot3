#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D pointTexture;
uniform vec4 color;

in float alpha;
out vec4 fragColor;

void main()
{
    if (alpha <= 0.0)
    {
        discard;
    }
    else
    {
        vec4 tmpColor = vec4(color.rgb, alpha);
        fragColor = texture(pointTexture, gl_PointCoord) * tmpColor;
    }
}
