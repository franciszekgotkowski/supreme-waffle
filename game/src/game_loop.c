#include "engine/platform/shader.h"
#include "glad/glad.h"
#include <engine/platform/graphics.h>
#include <game/input_functions.h>
#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <engine/platform/input.h>
#include <assert.h>
#include <game/game_loop.h>
#include <engine/platform/game_loop.h>

#include <stdbool.h>

extern PointerTable* GameMemory;

void GameLoop() {
	const PointerTable* table = GameMemory;
	assert(table);

	ShaderProgramID shader = CreateShaderProgram("../../engine/src/shaders/triangle.vert", "../../engine/src/shaders/triangle.frag");

	f32 vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	u32 VBO;
	glGenBuffers(1, &VBO);
	u32 VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(f32), (void*)0);
	glEnableVertexAttribArray(0);

	UseShaderProgram(shader);
	glBindVertexArray(VAO);

	while (!((WindowData*)getRegion(WINDOW_DATA))->windowShouldClose) {
		clearScreen();

		handleInput();
		// handleEditor();
		// handleGameEvents(table);
		// renderScene(table);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		updateBuffer();
		handleEngineEvents();
	}
	CloseWindow();
}