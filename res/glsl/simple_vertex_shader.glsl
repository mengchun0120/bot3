uniform bool useObjRef;
uniform vec2 objRef;
uniform vec2 viewportSize;
uniform vec2 viewportOrigin;
uniform vec2 direction;
uniform bool useDirection;

in vec3 position;
in vec2 texPos;
out vec2 texCoord;

void main()
{
    vec3 pos = position;
    if(useDirection)
    {
        float x = pos.x * direction.x - pos.y * direction.y;
        float y = pos.x * direction.y + pos.y * direction.x;
        pos.x = x;
        pos.y = y;
    }

    if(useObjRef)
    {
        pos.xy += objRef;
    }

    pos.xy -= viewportOrigin;

    gl_Position = vec4(pos.xy * 2.0 / viewportSize, pos.z, 1.0);

    texCoord = texPos;
}
