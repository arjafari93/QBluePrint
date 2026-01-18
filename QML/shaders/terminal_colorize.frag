#version 440

layout(location = 0) in vec2 qt_TexCoord0;
layout(location = 0) out vec4 fragColor;

// Qt 6 ShaderEffect expects a uniform buffer that begins with qt_Matrix + qt_Opacity
layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    vec4 customColor;
};

layout(binding = 1) uniform sampler2D source;

void main()
{
    vec4 color = texture(source, qt_TexCoord0);

    if (color.r + color.g + color.b < 0.2)
        fragColor = color * qt_Opacity;
    else
        fragColor = customColor * qt_Opacity;
}
