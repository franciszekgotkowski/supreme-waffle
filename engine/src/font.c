#include <engine/platform/file_io.h>
#include <assert.h>
#include <engine/font.h>
#include <engine/typedefs.h>

static inline u64 CalculateSpaceForFont(Font font) {
	u64 size = sizeof(Font) + (font.boundingBoxW*font.boundingBoxH + sizeof(Character))*font.amountOfCharacters;
	return size;
}

static u32 recogniseFontParameter(str s) {
	str parameters[] = {
		"FONTBOUNDINGBOX",
		"SPACING",
		"FONT_ASCENT",
		"FONT_DESCENT",
		"ENDPROPERTIES",
		"CHARS",
	};

	mstr ms = (mstr)s;
}

// TODO
static Font ReadJustFontData(FileData file) {
	assert(file.ptr);

	Font font;

	assert(0);
	return font;
}

u64 SpaceNeededForFont(FileData file) {
	assert(file.ptr);

	return CalculateSpaceForFont( ReadJustFontData(file) );
}