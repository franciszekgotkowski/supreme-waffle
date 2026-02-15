#version 330 core

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 inTexturePosition;

out vec2 TexturePosition;

void main() {
    gl_Position = vec4(Position.x, Position.y, 0.0, 1.0);
    TexturePosition = inTexturePosition;
}
