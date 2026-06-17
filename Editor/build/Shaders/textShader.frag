#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{
    vec2 tex     = texture(text, TexCoords).rg;
    float fill    = tex.r;   // R channel = glyph fill
    float outline = tex.g;   // G channel = outline border

    // Outline color: black, or swap for any color you like
    vec3 outline_col = vec3(0.0, 0.0, 0.0);
    vec3 fill_col    = textColor.rgb;

    // Where both overlap, fill wins; where only outline exists, outline shows
    vec3  final_color = mix(outline_col, fill_col, fill);
    float final_alpha = max(fill, outline) * textColor.a;

    color = vec4(final_color, final_alpha);
}
