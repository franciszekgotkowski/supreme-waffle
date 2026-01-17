#pragma once

#include <engine/errors.h>
#include <engine/scene.h>
#include <engine/ui.h>

typedef struct {

	SceneMetadata* sceneMetadata;
	UiMetadata* uiMetadata;
	void* stackTop;

} CanvasMetadata ;

Error InitailizeCanvasMetadata();