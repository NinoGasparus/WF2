#include <SDL2/SDL_video.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <sys/types.h>





//convert 8bit ints to chars for viewing
void preRender(uint8_t* data, int len){
  char range[] = {',', ':', 'o', 'O', '@', '#'};

  for(int i =0; i < len; i++){
    if(data[i] == 0){
      data[i] = '.';
    }else{
      //map value to somethign between 0 and 5 
      data[i] = range[(int)data[i]/43];
    }
  }

}


uint8_t getMAX(int x, int y, int blockX, int blockY, int bsx, int bsy, uint8_t * data){
  int max = 0;  
/* 

  for(int i = 0; i < bsy; i ++){
    for(int j = 0; j < bsx; j++){
      int val = data[(blockY + i) * x+ (blockX+ j)];
      if(val > max)
        max = val;
    }
  }

*/
  for(int i = blockY; i < blockY + bsy; i++){
    for(int j = blockX; j < blockX + bsx; j++){
      if(data[i * x + j] > max){
        max = data[i*x+j];
      }
    }
  }
  return max;
}



uint8_t* downscale(uint8_t* data, int x, int y, int scale){
  int newX = (int) x / scale;
  int newY = (int) y / scale;
  int bsx = x / newX;
  int bsy = y / newY;

  int newSize = newX * newY;

  uint8_t* newData = new uint8_t[newSize];

  for(int i  = 0; i < newY ; i+= 1 ){
    for(int j = 0; j < newX; j+=1){
      newData[i * newX + j] = getMAX(x, y ,j*bsx, i * bsy, bsx, bsy, data); 
    }
  }
  return newData;
}

void render(int x, int y, uint8_t* data){
  int df = 32;
  int newlen =  (int)(x/df) * (int)(y/df);
  uint8_t* newData = downscale(data, x , y, df);

  preRender(newData, newlen);

  char* buff = new char[x/df +1];
  buff [x/df] = '\0';
  for(int i = 0; i < y/df; i++){
    memcpy(buff,newData+i*(x/df), x/df);
    std::cout << buff <<  std::endl;
  }

  delete[] newData;
  delete[] buff;

}






extern int mit; 
void colorPixles(uint8_t* data, int dataLen, uint32_t* out){
  for(int i =0; i < dataLen; i++){
    float  x = data[i]/(mit * 1.0);

    uint8_t r = (uint8_t)(9 * (1-x) * x* x* x * 255);
    uint8_t g = (uint8_t)(15 * (1-x) * (1-x) * x * x * 255);
    uint8_t b = (uint8_t)(8.5 * (1-x) * (1-x) * (1-x) * x * 255);
    if(data[i] == 0){
      r = 0;
      g = 0;
      b = 0;
    }
    uint32_t v = 0x00000000;
    v |= 0xFF;
    v <<= 8;
    v |= b;
    v <<= 8;
    v |= g;
    v <<= 8;
    v |= r;
    out[i] = v;
  }
}















GLuint loadShader(GLenum type, const char* path) {
    FILE* f = fopen(path, "rb");
    if(!f){
    std::cerr << "shader file missing" << std::endl;
    return 0;
    }
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    rewind(f);
    char* src = (char*)malloc(len + 1);
    fread(src, 1, len, f);
    src[len] = '\0';
    fclose(f);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    free(src);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, NULL, log);
        fprintf(stderr, "Shader compile error: %s\n", log);
    }

    return shader;
}

GLuint createShaderProgram() {
    GLuint vert = loadShader(GL_VERTEX_SHADER, "shader.vert");
    GLuint frag = loadShader(GL_FRAGMENT_SHADER, "shader.frag");

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    GLint success;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(prog, 512, NULL, log);
        fprintf(stderr, "Shader link error: %s\n", log);
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    return prog;
}


GLuint create_texture(int WIDTH, int HEIGHT) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, WIDTH, HEIGHT, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return tex;
}



GLuint quadVAO = 0, quadVBO;
void setupFullscreenQuad() {
    float quadVertices[] = {
        // positions   // texCoords
        -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f,   0.0f, 1.0f,
    };
    unsigned int indices[] = { 0, 1, 2, 0, 2, 3 };

    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);

    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}



void draw_fullscreen_quad() {
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}



void render2(int WIDTH, int HEIGHT, uint8_t* data ) {
    uint32_t* pixels = new uint32_t[WIDTH* HEIGHT];
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    uint8_t v = data[i]; // 0-255 grayscale
    pixels[i] = (255u << 24)      // A = 255 (opaque)
              | (v << 16)        // R
              | (v << 8)         // G
              | (v);             // B
}
//    colorPixles(data,WIDTH*HEIGHT , pixels);
SDL_Init(SDL_INIT_VIDEO);
SDL_Window* window = SDL_CreateWindow("window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL); 
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GLContext context = SDL_GL_CreateContext(window);

glewExperimental = GL_TRUE;
if (glewInit() != GLEW_OK) {
    std::cerr << "GLEW init failed\n";
    exit(1);
}

GLuint shaderProgram = createShaderProgram(); 

setupFullscreenQuad();

GLuint texture = create_texture(WIDTH, HEIGHT);

int uniformLocation = glGetUniformLocation(shaderProgram, "uTex");

bool running = true;
SDL_Event event;
while (running) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = false;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(uniformLocation, 0);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    draw_fullscreen_quad();

    SDL_GL_SwapWindow(window);
}

glDeleteTextures(1, &texture);
SDL_GL_DeleteContext(context);
SDL_DestroyWindow(window);
SDL_Quit();
}

