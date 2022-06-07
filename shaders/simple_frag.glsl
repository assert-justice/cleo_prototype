varying vec2 TexCoord;
uniform sampler2D ourTexture;

void main()
{
    // gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    gl_FragColor = texture(ourTexture, TexCoord);
} 