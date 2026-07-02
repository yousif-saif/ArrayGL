#version 460 core

out vec4 PixelColor;
uniform vec3 color;

void main() {
   PixelColor = vec4(color, 1.0);

}


