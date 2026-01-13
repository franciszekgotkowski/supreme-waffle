#pragma once

#include <engine/memory_pool.h>
#include <stdbool.h>

bool shouldWindowClose(PointerTable* table);

void clearScreen(PointerTable* table);

void updateBuffer(PointerTable* table);

void handleEngineEvents(PointerTable* table);