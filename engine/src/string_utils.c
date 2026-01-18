#include <engine/string_utils.h>

#include <assert.h>
#include <stddef.h>

mstr stickToWord(mstr s) {
	assert(s);

	mstr t = s;
	while (*t != '\0' && *t != '\n' && *t != ' ' && *t != '\t') {
		t--;
	}

	return ++t;
}

mstr nextWord(mstr s) {
	assert(s);

	mstr t = s;
	while (*t != '\n'  && *t != ' ' && *t != '\t') {
		if (*t == '\0') {
			return NULL;
		}
		t++;
	}

	while (*t == '\n' || *t == ' ' || *t == '\t') {
		if (*t == '\0') {
			return NULL;
		}
		t++;
	}

	return t;
}

mstr newLine(mstr s) {
	assert(s);

	mstr t = s;
	while (*t != '\n') {
		if (*t == '\0') {
			return NULL;
		}
		t++;
	}

	while (*t == '\n') {
		if (*t == '\0') {
			return NULL;
		}
		t++;
	}

	return t;
}

mstr searchFor(mstr s, char c) {
	assert(s);

	mstr t = s+1;
	while (*t != c) {
		if (*t == '\0') {
			return NULL;
		}
		t++;
	}

	return t;
}

u32 wordLength(mstr s) {
	assert(s);

		mstr t = s;
		while (*t != '\0' && *t != '\n'  && *t != ' ' && *t != '\t') {
			t--;
		}
		t++;

		u32 len = 0;
		while (*t != '\0' && *t != '\n' && *t != ' ' && *t != '\t') {
			t++;
			len++;
		}

		return len;
}

bool wordsMatch(str a, str b) {
    assert(a);
    assert(b);

    mstr ma = (mstr)a;
    mstr mb = (mstr)b;

    stickToWord(ma);
    stickToWord(mb);

    while ((*ma!= '\0' && *ma!= '\n' && *ma!= ' ' && *ma!= '\t')  && (*mb != '\0' && *mb != '\n' && *mb != ' ' && *mb != '\t')) {

    	if (*ma != *mb) {
   			return false;
     	}

    	ma++;
        mb++;
    }
    if ((*ma== '\0' || *ma== '\n' || *ma== ' ' || *ma== '\t') && (*mb == '\0' || *mb == '\n' || *mb == ' ' || *mb == '\t')) {
        return true;
    } else {
        return false;
    }
}
