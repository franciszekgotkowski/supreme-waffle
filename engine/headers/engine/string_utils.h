#pragma once

#include <stdbool.h>
#include <engine/typedefs.h>

mstr stickToWord(mstr s);

mstr nextWord(mstr s);

mstr newLine(mstr s);

mstr searchFor(mstr s, char c);

u32 wordLength(mstr s);

bool wordsMatch(str a, str b);
