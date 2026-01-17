#include <engine/font.h>
#include <engine/typedefs.h>

u64 FontSizeInBytes(Font *font) {
	u64 size = sizeof(Font) + (font->boundingBoxW*font->boundingBoxH + sizeof(Character))*font->amountOfCharacters;
	return size;
}