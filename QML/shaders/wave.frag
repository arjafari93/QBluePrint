#version 440

layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 0) out vec4 fragColor;

// Qt 6 ShaderEffect: uniforms come from a std140 buffer at binding 0.
// The first two entries must be qt_Matrix and qt_Opacity.
layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;

    // your custom uniforms (match QML property names)
    float u_time;
    float u_amplitute;
};

layout(binding = 1) uniform sampler2D source;

void main()
{
    float newY = u_amplitute * sin(qt_TexCoord0.y * 25.0 + u_time);

    // keep your opacity curve (your original does nested sqrt three times)
    float newOpacity = 1.0 - 1.015 * sqrt(sqrt(sqrt(qt_TexCoord0.y)));
    newOpacity = max(newOpacity, 0.0);

    vec2 uv = vec2(qt_TexCoord0.x, 1.0 - (qt_TexCoord0.y + newY));
    vec4 color = texture(source, uv);

    fragColor = color * qt_Opacity * newOpacity;
}
