#pragma once

#include <engine/typedefs.h>
#include <engine/errors.h>

typedef struct {
	u64 fileSize; // comes with additional \0 at the end
	void* ptr;
} FileData ;

Error readEntireFile(str path, FileData* fileData);
Error freeEntireFile(FileData fileData);