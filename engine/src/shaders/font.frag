#version 330 core

in vec2 TexturePosition;

uniform sampler2D FontTexture;
uniform vec3 fontColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(fontColor.x, fontColor.y, fontColor.z, 1.0) * texture(FontTexture, TexturePosition).r;
}
