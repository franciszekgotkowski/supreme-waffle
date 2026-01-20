#include <alloca.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <engine/platform/file_io.h>
#include <engine/string_utils.h>
#include <engine/font.h>
#include <engine/typedefs.h>
#include <engine/range.h>

static inline u64 CalculateSpaceForFont(Font font) {
	u64 size =
		sizeof(Font) // Font struct
		+ font.highestCharCode*sizeof(u32) // offsetTable
		+ (font.boundingBoxH + 2*font.spacing) * (font.spacing + font.amountOfCharacters*(font.boundingBoxW + font.spacing));

	return size;
}

static i32 recogniseFontParameter(str s) {
    assert(s);
    const u32 amountOfParameters = 6;
	str parameters[] = {
		"FONTBOUNDINGBOX",
		"SPACING",
		"FONT_ASCENT",
		"FONT_DESCENT",
		"ENDPROPERTIES",
		"CHARS",
	};

    for range(i, amountOfParameters) {
        if (wordsMatch(parameters[i], s)) {
            return i;
        }
    }

    return -1;
}

static inline void handle_fontboundingbox(mstr ms, Font* font) {
    assert(font);
    assert(ms);


    ms = nextWord(ms);
    u64 wordLen = wordLength(ms);
    mstr currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    font->boundingBoxW = atoi(currentstr);

    ms = nextWord(ms);
    wordLen = wordLength(ms);
    currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    font->boundingBoxH = atoi(currentstr);

    ms = nextWord(ms);
    wordLen = wordLength(ms);
    currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    font->offsetX = atoi(currentstr);

    ms = nextWord(ms);
    wordLen = wordLength(ms);
    currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    font->offsetY = atoi(currentstr);

    return;
}

static inline void handle_spacing(mstr ms, Font* font){
    assert(font);
    assert(ms);

    ms = nextWord(ms);
    switch (ms[1]) {
        case 'C':
            font->fontSpacing = CELL;
            break;
        case 'M':
            font->fontSpacing = MONOSPACED;
            break;
        case 'P':
            font->fontSpacing = PROPORTIONAL;
            break;
    }
}

static inline void handle_font_ascent(mstr ms, Font* font){
    assert(ms);
    assert(font);

    ms = nextWord(ms);
    u64 wordLen = wordLength(ms);
    mstr currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    font->fontAscent = atoi(currentstr);
}

static inline void handle_font_descent(mstr ms, Font* font){
    assert(ms);
    assert(font);

    ms = nextWord(ms);
    u64 wordLen = wordLength(ms);
    mstr currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    font->fontDescent = atoi(currentstr);
}

static inline void handle_endproperties(mstr ms, Font* font){
    // nothing has to happen
}

static inline void handle_chars(mstr ms, Font* font){
    assert(ms);
    assert(font);

    ms = nextWord(ms);
    u64 wordLen = wordLength(ms);
    mstr currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    font->amountOfCharacters = atoi(currentstr);
}

Font InitializeFont(FileData file) {
	assert(file.ptr);

	Font font;

    bool parametersRead[] = {
        false,
        false,
        false,
        false,
        false,
        false,
    };

    mstr ms = file.ptr;
    i32 paramNum = -1;
    do {
        paramNum = recogniseFontParameter((str)ms);
        if (paramNum != -1) {
            assert(parametersRead[paramNum] == false);
            parametersRead[paramNum] = true;
        }
        switch (paramNum) {
            case 0:
                handle_fontboundingbox(ms, &font);
                break;
            case 1:
                handle_spacing(ms, &font);
                break;
            case 2:
                handle_font_ascent(ms, &font);
                break;
            case 3:
                handle_font_descent(ms, &font);
                break;
            case 4:
                handle_endproperties(ms, &font);
                break;
            case 5:
                handle_chars(ms, &font);
                break;
            default:
                break;
        }

        ms = newLine(ms);
    } while (paramNum != 5);

    for range(i, 6) {
        assert(parametersRead[i]);
    }

    // font.spacing =

	return font;
}

static u32 checkForHighestCharCode(FileData file) {

	assert(file.ptr);

	mstr ms = file.ptr;

	i32 max = -1;

	do {
		if (wordsMatch("ENCODING", ms)) {

			ms = nextWord(ms);
			u64 wordLen = wordLength(ms);
			mstr currentstr = alloca(wordLen+1);
			strncpy(currentstr, ms, wordLen);
			currentstr[wordLen] = '\0';
			i32 t = atoi(currentstr);
			if (t > max) {
				max = t;
			}

		}

		ms = newLine(ms);
	} while (!wordsMatch("ENDFONT", ms));

	assert(max != -1);
	return max;
}


u64 SpaceNeededForFont(FileData file) {
	assert(file.ptr);

    Font font = InitializeFont(file);
    font.highestCharCode = checkForHighestCharCode(file);
    font.spacing = 1;

	return CalculateSpaceForFont(font);
}

static i32 recogniseCharacterParameter(str s) {
    assert(s);
    const u32 amountOfParameters = 7;
	str parameters[] = {
		"STARTCHAR",
		"ENCODING",
		"DWIDTH",
		"BBX",
		"BITMAP",
		"ENDCHAR",
	};

	for range(i, amountOfParameters) {
		if (wordsMatch(parameters[i], s)) {
			return i;
		}
	}
	return -1;
}

static inline void handle_startchar(mstr ms, Character* character){
	assert(ms);
	assert(character);

	// nothing to do really
}

static inline void handle_encoding(mstr ms, Character* character){
	assert(ms);
    assert(character);

    ms = nextWord(ms);
    u64 wordLen = wordLength(ms);
    mstr currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    character->charCode = atoi(currentstr);
}

static inline void handle_dwidth(mstr ms, Character* character){
	assert(ms);
    assert(character);

    ms = nextWord(ms);
    u64 wordLen = wordLength(ms);
    mstr currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    character->dWidthX = atoi(currentstr);

    ms = nextWord(ms);
    wordLen = wordLength(ms);
    currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    character->dWidthY = atoi(currentstr);
}

static inline void handle_bbx(mstr ms, Character* character){
	assert(ms);
    assert(character);

    ms = nextWord(ms);
    u64 wordLen = wordLength(ms);
    mstr currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    character->boundingBoxW = atoi(currentstr);

    ms = nextWord(ms);
    wordLen = wordLength(ms);
    currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    character->boundingBoxH = atoi(currentstr);

    ms = nextWord(ms);
    wordLen = wordLength(ms);
    currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    character->offsetX = atoi(currentstr);

    ms = nextWord(ms);
    wordLen = wordLength(ms);
    currentstr = alloca(wordLen+1);
    strncpy(currentstr, ms, wordLen);
    currentstr[wordLen] = '\0';
    character->offsetY = atoi(currentstr);
}
//
u32 positionInBitmap(Font* font, u32 charIdx, u32 x, u32 y) {
    assert(font);

    assert(x < font->boundingBoxW);
    assert(y < font->boundingBoxH);
    assert(charIdx < font->amountOfCharacters);

    u32 yOffset = (font->amountOfCharacters*(font->spacing+font->boundingBoxW)+font->spacing)*(y+font->spacing);
    u32 xOffset = font->spacing + charIdx*(font->spacing + font->boundingBoxW) + x;

    return yOffset + xOffset;
}

static inline void handle_bitmap(mstr ms, Character* character, Font* font, u32 charIdx){
	assert(ms);
	assert(character);

	ms = nextWord(ms);
	u32 y = 0;
	while (!wordsMatch("ENDCHAR", ms)) {
		u32 wordLen = wordLength(ms);
		u8* word = alloca(wordLen);
		memcpy(word, ms, wordLen);

		for range(x, character->boundingBoxW) {
			u8 byte = word[x/8];
			u8 shift = x % 8;

			u8 value = (byte << shift) & 0x80;

			u32 offset = positionInBitmap(font, charIdx, x, y);
			font->characterBitmap[offset] = value == 0x80 ? 255 : 0;
		}

		y++;
	}
}

static inline void handle_endchar(mstr ms, Character* character){
	assert(ms);
	assert(character);

	// nothing more to do here
}


static Character ReadCharacterData(mstr ms, Font* font, u32 charIdx) {
	assert(ms);

	Character character;

	bool parametersRead[] = {
		false,
		false,
		false,
		false,
		false,
		false,
	};

    i32 paramNum = -1;
    do {
        paramNum = recogniseCharacterParameter((str)ms);
        if (paramNum != -1) {
            assert(parametersRead[paramNum] == false);
            parametersRead[paramNum] = true;
        }
        switch (paramNum) {
            case 0:
           		handle_startchar(ms, &character);
                break;
            case 1:
          		handle_encoding(ms, &character);
                break;
            case 2:
          		handle_dwidth(ms, &character);
                break;
            case 3:
          		handle_bbx(ms, &character);
                break;
            case 4:
          		handle_bitmap(ms, &character, font, charIdx);
                break;
            case 5:
          		handle_endchar(ms, &character);
                break;
            default:
                break;
        }

        ms = newLine(ms);
    } while (paramNum != 5);

    for range(i, 6) {
        assert(parametersRead[i]);
    }

    return character;
}
// TODO: 	Still have to write this function.
// 			It will iterate not over lines but STARTCHAR lines
Error FillCharacaterData(Font* font, FileData file) {
	assert(font);
	assert(file.ptr);

	font->highestCharCode = checkForHighestCharCode(file);

	font->offsetTable = (u32*)(font+1);
	font->charactersData = (Character*)(font->offsetTable+font->highestCharCode);
	font->characterBitmap = (u8*)(font->charactersData+font->amountOfCharacters);
	u32 bitmapSpace = (font->boundingBoxH+2*font->spacing)*(font->spacing+font->amountOfCharacters*(font->spacing+font->boundingBoxW));
	u64 top = (llu)font->characterBitmap + bitmapSpace;
	// printf("clearing bitmap on address: 0x%llx up to 0x%llx", (llu)font->characterBitmap, ((llu)font->characterBitmap + bitmapSpace));
	printf("%llu\n", (llu)top);

	memset(font->characterBitmap, 0, bitmapSpace);

	mstr ms = file.ptr;

	for range(i, font->amountOfCharacters) {

		do {
			ms = newLine(ms);
		} while (!wordsMatch("STARTCHAR", ms));

		Character c = ReadCharacterData(ms, font, i);
		font->charactersData[i] = c;
		font->offsetTable[c.charCode] = i;
	}

	return OK;
}
