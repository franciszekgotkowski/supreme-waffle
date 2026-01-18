#pragma once

#define FONT_FILES_LOCATION "../../assets/fonts/bdf/"

#include <engine/typedefs.h>
#include <engine/errors.h>
#include <engine/platform/file_io.h>

typedef enum {
	CELL, 			// every character has the same width
	MONOSPACED,  	// every character has the same width but characters are treated like elements of a grid
	PROPORTIONAL	// every character has different size
} FontSpacing ;

typedef struct {
	// ascii code
	// from ENCODING
	u32 charCode;

	// how much cursor should move after drawing this character
	// from DWIDTH
	u32 dWidthX;
	u32 dWidthY;

	// bounding box size
	// from BBX
	u32 boundingBoxW;
	u32 boundingBoxH;

	// offsets from baseline
	// from BBX
	i32 offsetX;
	i32 offsetY;
} Character ;

typedef struct {
	// maximum bounding box size
	// from FONTBOUNDINGBOX
	u32 boundingBoxW;
	u32 boundingBoxH;

	// maximum offsets from baseline
	// from FONTBOUNDINGBOX
	i32 offsetX;
	i32 offsetY;

	// type of font spacing
	// from SPACING
	FontSpacing fontSpacing;

	// font ascent - how many pixels are below and above baseline
	// from FONT_ASCENT
	u32 fontAscent;
	// from FONT_DESCENT
	u32 fontDescent;

	// amount of characters
	// from CHARS
	u32 amountOfCharacters;

	Character* charactersData;
	u8* characterBitmap;
} Font;

Font ReadJustFontData(FileData file);

// Function returns amount of bytes needed to accomodate a font.
// It counts size of font struct, amount of characters * (character struct size + (1 byte per pixel * BoundingBoxW * BoundingBoxH) )
u64 SpaceNeededForFont(FileData file);

// Function gives font struct pointers to where character structs are and where a bitmap is.
// Inteded location of those is next to the Font struct like here:
// 		Font struct
// 		Character struct[]
// 		Character bitmaps[]
Error FillCharacaterData(Font* font, FileData file);