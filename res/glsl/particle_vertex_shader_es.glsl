#version 300 es

uniform vec2 viewportSize;
uniform vec2 viewportOrigin;
uniform vec2 ref;
uniform float curTime;
uniform float acceleration;
uniform float particleSize;
uniform float duration;

in vec2 startPos;
in vec2 direction;
in float initSpeed;
out float alpha;

void main()
{
    vec2 pos = ref + startPos + direction *
               (initSpeed * curTime - acceleration * curTime * curTime / 2.0);

    pos -= viewportOrigin;

    gl_Position = vec4(pos * 2.0 / viewportSize, 0.0, 1.0);

    alpha = 1.0 - curTime / duration;
    if (alpha < 0.0)
    {
        alpha = 0.0;
    }

    gl_PointSize = particleSize;
}
