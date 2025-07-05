#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTex;

void main() {
    float x = texture(uTex , TexCoord).r; // Assumes normalized [0,1]

    if (abs(x -  (1.0/255.0)) < 0.003) {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); // red if x == 1
        return;
    }

    float r = 9.0 * (1.0 - x) * pow(x, 3.0);
    float g = 15.0 * pow(1.0 - x, 2.0) * pow(x, 2.0);
    float b = 8.5 * pow(1.0 - x, 3.0) * x;

    FragColor = vec4(r, g, b, 1.0);
}

