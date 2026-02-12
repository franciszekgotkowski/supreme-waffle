#pragma once

#define FONT_FILES_LOCATION "../../assets/fonts/bdf/"
#define CHARACTER_SPACING 1

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

// Contains all relevant info about a font
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

	// Highest char code. Needed for me to create a table of offsets
	u32 highestCharCode;

    // How many pixels will be between character bitmaps
    // All characters are in 1 array hegth array (there are no columns of characters. It has amountOfCharacters x 1 proportions)
    u32 spacing;

    // index [i] is offset in to array which has offset into charactersData which has relevant information about the character
    i32* offsetTable;

    // array with relevant information about character
    Character* charactersData;

    // bitmap of the font
	u8* characterBitmap;
} Font;

// size in bytes needed to accomodate offsetTable, charactersData and characterBitmap
u64 GetSizeForCharacterData(Font* font);

// size in bytes for GetSizeForCharacterData and Font struct
u64 GetSizeForEntireFont(Font* font);

// Creates Font struct with info about a font without filling in offsetTable, charactersData and characterBitmap
// This will happen later in InitializeCharacterDataOntoFont or InitializeCharacterDataOnAddress
Font InitializeFont(
	FileData file
);

// Function gives font struct pointers to where character structs are and where a bitmap is.
// Inteded location of those is next to the Font struct like here:
// 		[low address]
// 		Font struct
// 		Offset table where indexes of the table are charCodes
// 		Character struct[]
// 		Character bitmaps[]
// 		[hight address]
// NOTE: if character does not exist there is -1 in its offset table value
Error InitializeCharacterDataOnAddress(
	Font* font,
	void* dest,
	FileData file
);

// the same as InitializeCharacterDataOntoFont but it allocates character data not on some address but on addres adter font
Error InitializeCharacterDataOntoFont(
	Font* font,
	FileData file
);

// how wide is bitmap in pixels accounting for padding
u64 bitmapW(
	Font* font
);

// how high is bitmap in pixels accounting for padding
u64 bitmapH(
	Font* font
);

// gets bottom left u8acter position in texture
v2 GetTextureCoordinateBottomLeft(
	u8 character,
	Font* font
);

// gets bottom right u8acter position in texture
v2 GetTextureCoordinateBottomRight(
	u8 character,
	Font* font
);

// gets top left u8acter position in texture
v2 GetTextureCoordinateTopLeft(
	u8 character,
	Font* font
);

// gets top left u8acter position in texture
v2 GetTextureCoordinateTopRight(
	u8 character,
	Font* font
);

void InitializeTextureCoordinatesBuffer(
	Font* font, // font to look up to
	str* textLine, // ascii line to generate
	u32 offset, // offset from buffer to start filling in texture coordinates
	u32 stride, // stride between characters texture coordinates
	void* out
);