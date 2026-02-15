#include "engine/platform/shader.h"
#include "engine/range.h"
#include "glad/glad.h"
#include <alloca.h>
#include <engine/platform/graphics.h>
#include <game/input_functions.h>
#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <engine/platform/input.h>
#include <assert.h>
#include <game/game_loop.h>
#include <engine/platform/game_loop.h>

#include <stdbool.h>
#include <string.h>
#include <external/stb_image_write.h>

#include <engine/platform/file_io.h>
#include <engine/font.h>
#include <stdio.h>

extern PointerTable *GameMemory;

void GameLoop() {
    const PointerTable *table = GameMemory;
    assert(table);

    // ShaderProgramID shader = CreateShaderProgram("../../engine/src/shaders/triangle.vert", "../../engine/src/shaders/triangle.frag");

    // f32 vertices[] = {
    // 	-0.5f, -0.5f, 0.0f,
    // 	0.5f, -0.5f, 0.0f,
    // 	0.0f,  0.5f, 0.0f
    // };

    // u32 VBO;
    // glGenBuffers(1, &VBO);
    // u32 VAO;
    // glGenVertexArrays(1, &VAO);

    // glBindVertexArray(VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(f32), (void*)0);
    // glEnableVertexAttribArray(0);

    // UseShaderProgram(shader);
    // glBindVertexArray(VAO);

    FileData file;
    readEntireTextFile("../../assets/fonts/bdf/cherry-11-r.bdf", &file);
    Font f = InitializeFont(file);
    printf("space needed for cherry-11-r.bdf = %llu\n", (llu) GetSizeForEntireFont(&f));
    Font *font = alloca(GetSizeForEntireFont(&f));
    *font = f;
    InitializeCharacterDataOntoFont(font, file);
    freeEntireTextFile(file);
    stbi_write_png("./cherryfont.png", (i32) bitmapW(font), (i32) bitmapH(font), 1, font->characterBitmap,
                   (i32) bitmapW(font));

    ShaderProgramID FontShader = CreateShaderProgram("../../engine/src/shaders/font.vert",
                                                     "../../engine/src/shaders/font.frag");

    u32 textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, (i32) bitmapW(font), (i32) bitmapH(font), 0, GL_RED, GL_UNSIGNED_BYTE,
                 font->characterBitmap);

    glGenerateMipmap(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    f32 buf[] = {
        0.0f, 0.0f, GetTextureCoordinateBottomLeft('&', font).x, GetTextureCoordinateBottomLeft('&', font).y,
        0.06f, 0.0f, GetTextureCoordinateBottomRight('&', font).x, GetTextureCoordinateBottomRight('&', font).y,
        0.06f, 0.11f, GetTextureCoordinateTopRight('&', font).x, GetTextureCoordinateTopRight('&', font).y,
        0.0f, 0.11f, GetTextureCoordinateTopLeft('&', font).x, GetTextureCoordinateTopLeft('&', font).y,
        0.06f + 0.0f, 0.0f, GetTextureCoordinateBottomLeft('s', font).x, GetTextureCoordinateBottomLeft('s', font).y,
        0.06f + 0.06f, 0.0f, GetTextureCoordinateBottomRight('s', font).x, GetTextureCoordinateBottomRight('s', font).y,
        0.06f + 0.06f, 0.11f, GetTextureCoordinateTopRight('s', font).x, GetTextureCoordinateTopRight('s', font).y,
        0.06f + 0.0f, 0.11f, GetTextureCoordinateTopLeft('s', font).x, GetTextureCoordinateTopLeft('s', font).y,
        2.0f * 0.06f + 0.0f, 0.0f, GetTextureCoordinateBottomLeft('Y', font).x, GetTextureCoordinateBottomLeft('&', font).y,
        2.0f * 0.06f + 0.06f, 0.0f, GetTextureCoordinateBottomRight('Y', font).x, GetTextureCoordinateBottomRight('&', font).y,
        2.0f * 0.06f + 0.06f, 0.11f, GetTextureCoordinateTopRight('Y', font).x, GetTextureCoordinateTopRight('&', font).y,
        2.0f * 0.06f + 0.0f, 0.11f, GetTextureCoordinateTopLeft('Y', font).x, GetTextureCoordinateTopLeft('&', font).y,
    };

    u32 ebobuf[] = {
        0, 1, 3,
        1, 2, 3,

        4, 5, 7,
        5, 6, 7,

        8, 9, 11,
        9, 10, 11
    };

    u32 VAO;
    u32 VBO;
    u32 EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ebobuf), ebobuf, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void *) (2 * sizeof(f32)));


    UseShaderProgram(FontShader);

    glBindTexture(GL_TEXTURE_2D, textureID);
    GLint loc = glGetUniformLocation(FontShader, "FontTexture");
    glUniform1i(loc, 0);
    loc = glGetUniformLocation(FontShader, "fontColor");
    f32 color[3] = {0.0f, 1.0f, 1.0f};
    glUniform3fv(loc, 1, color);
    glBindVertexArray(VAO);


    while (!((WindowData *) getRegion(WINDOW_DATA))->windowShouldClose) {
        clearScreen();

        handleInput();
        // handleEditor();
        // handleGameEvents(table);
        // renderScene(table);

        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, (void *) 0);


        updateBuffer();
        handleEngineEvents();
    }
    CloseWindow();
}
