#include <alloca.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <engine/platform/file_io.h>
#include <engine/string_utils.h>
#include <engine/font.h>
#include <engine/typedefs.h>
#include <engine/range.h>

static inline u64 CalculateSpaceForFont(Font font) {
	u64 size = sizeof(Font) + (font.boundingBoxW*font.boundingBoxH + sizeof(Character))*font.amountOfCharacters;
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

Font ReadJustFontData(FileData file) {
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

	return font;
}

u64 SpaceNeededForFont(FileData file) {
	assert(file.ptr);

    Font font = ReadJustFontData(file);

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

// TODO: I still need to do bitmap reading
static inline void handle_bitmap(mstr ms, Character* character, u8* bitmap){
	assert(ms);
	assert(character);

	assert(0);

	ms = nextWord(ms);
	while (expression) {

	}
}

static inline void handle_endchar(mstr ms, Character* character){
	assert(ms);
	assert(character);

	// nothing more to do here
}


static Character ReadCharacterData(mstr ms, u8* bitmap) {
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
          		handle_bitmap(ms, &character, bitmap);
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
	assert(0);
}