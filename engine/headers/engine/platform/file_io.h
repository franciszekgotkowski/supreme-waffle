#pragma once

#include <engine/typedefs.h>
#include <engine/errors.h>

typedef struct {
	u64 fileSize; // comes with additional \0 at the end
	void* ptr;
} FileData ;

// reads entire file into a dynamically alocated memory region (via system calls). Gets rid of \r on endlilne on windows
Error readEntireTextFile(str path, FileData* fileData);
Error freeEntireTextFile(FileData fileData);

// maps file into memory
// TODO
Error mapTextFile(str path, FileData* fileData);
Error unmapTextFile(FileData fileData);