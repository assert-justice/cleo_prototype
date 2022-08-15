#version 130
attribute vec3 aPos;
attribute vec2 aCoord;
varying vec2 TexCoord;
uniform mat4 proj;
uniform mat4 matrix;
uniform vec4 dimensions;

void main()
{
    // gl_Position = proj * matrix * vec4(aPos.x * dimensions.z * 1024, aPos.y, aPos.z, 1.0);
    // 1024 is the atlas width. There is probably a smart way of synching these up
    gl_Position = proj * matrix * vec4(aPos.x * dimensions.z * 1024, aPos.y * dimensions.w * 1024, aPos.z, 1.0);
    TexCoord = aCoord * dimensions.zw + dimensions.xy;
    // TexCoord = aPos.xy + vec2(0.5, 0.5);
}