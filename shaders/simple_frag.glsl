varying vec2 TexCoord;
uniform sampler2D ourTexture;

void main()
{
    // gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    gl_FragColor = texture(ourTexture, TexCoord);
    // if(gl_FragColor.a < 1.0){
    if(gl_FragColor.r < 0.1 && gl_FragColor.g < 0.1 && gl_FragColor.b < 0.1){
        discard;
    }
} 