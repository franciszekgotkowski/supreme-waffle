#pragma once

#define CANVAS_FILES_LOCATION "../../assets/canvas/"

#include <engine/errors.h>
#include <engine/scene.h>
#include <engine/ui.h>

typedef struct {

	SceneData* sceneData;
	UiData* uiData;
	void* stackTop;

} CanvasMetadata ;

Error InitailizeCanvasData();