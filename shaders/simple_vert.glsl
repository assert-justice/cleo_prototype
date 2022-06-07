attribute vec3 aPos;
attribute vec2 aCoord;
varying vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = aCoord;
}