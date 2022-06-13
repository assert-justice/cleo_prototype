attribute vec3 aPos;
attribute vec2 aCoord;
varying vec2 TexCoord;
uniform mat4 mat;

void main()
{
    gl_Position = mat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = aCoord;
    // TexCoord = aPos.xy + vec2(0.5, 0.5);
}