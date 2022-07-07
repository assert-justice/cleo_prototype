varying vec2 TexCoord;
uniform sampler2D ourTexture;
uniform vec3 transparentColor;

void main()
{
    gl_FragColor = texture(ourTexture, TexCoord);
    if(length(gl_FragColor - transparentColor) < 0.1) discard;
    // if(gl_FragColor.r < 0.1 && gl_FragColor.g < 0.1 && gl_FragColor.b < 0.1){
    //     discard;
    // }
} 