attribute vec3 aPos;
attribute vec2 aCoord;
varying vec2 TexCoord;
uniform mat4 proj;
uniform mat4 matrix;
uniform vec4 dimensions;

void main()
{
    gl_Position = proj * matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = aCoord * dimensions.zw + dimensions.xy;
    // TexCoord = aPos.xy + vec2(0.5, 0.5);
}