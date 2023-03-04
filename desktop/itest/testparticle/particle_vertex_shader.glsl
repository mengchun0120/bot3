#version 330

uniform vec2 viewportOrigin;
uniform vec2 viewportSize;
uniform float curTime;
uniform float pointSize;
uniform float duration;
uniform float acceleration;

in vec2 startPos;
in vec2 direction;
in float initSpeed;
out float alpha;

void main()
{
    vec2 pos;
    float dist = curTime * initSpeed - acceleration * curTime * curTime / 2.0;
    pos[0] = startPos[0] + direction[0] * dist;
    pos[1] = startPos[1] + direction[1] * dist;
    pos -= viewportOrigin;

    gl_Position = vec4(pos * 2.0 / viewportSize, 0.0, 1.0);
    gl_PointSize = pointSize;

    alpha = 1 - curTime / duration;
    if (alpha < 0.0)
    {
        alpha = 0.0;
    }
}
