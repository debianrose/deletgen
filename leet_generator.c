#include "leet_generator.h"

static LeetErrorCode g_last_error      = LEET_OK;
static char          g_error_msg[256]  = {0};

static void set_error(LeetErrorCode code, const char* msg) {
    g_last_error = code;
    if (msg) {
        strncpy(g_error_msg, msg, sizeof(g_error_msg) - 1);
        g_error_msg[sizeof(g_error_msg) - 1] = '\0';
    } else {
        g_error_msg[0] = '\0';
    }
}

LEET_API LeetErrorCode leet_get_last_error(void) {
    return g_last_error;
}

LEET_API const char* leet_get_last_error_msg(void) {
    return g_error_msg;
}

LEET_API void leet_clear_error(void) {
    g_last_error  = LEET_OK;
    g_error_msg[0] = '\0';
}

static void* safe_malloc(size_t size) {
    if (size == 0) return NULL;
    void* ptr = malloc(size);
    if (!ptr) {
        set_error(LEET_ERR_MEMORY, "malloc failed");
    }
    return ptr;
}

static void* safe_calloc(size_t count, size_t size) {
    if (count == 0 || size == 0) return NULL;
    void* ptr = calloc(count, size);
    if (!ptr) {
        set_error(LEET_ERR_MEMORY, "calloc failed");
    }
    return ptr;
}

static wchar_t* safe_wcsdup(const wchar_t* s) {
    if (!s) return NULL;
    size_t len = wcslen(s) + 1;
    wchar_t* p = (wchar_t*)safe_malloc(len * sizeof(wchar_t));
    if (p) wcscpy(p, s);
    return p;
}

static char* safe_strdup(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char* p = (char*)safe_malloc(len);
    if (p) memcpy(p, s, len);
    return p;
}

static unsigned int xorshift32(unsigned int* state) {
    unsigned int x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}

static void leet_init_rng(LeetGenerator* gen) {
    if (gen->useSeed && gen->seed != 0) {
        gen->rng_state = gen->seed;
    } else {
        unsigned int t = (unsigned int)time(NULL);
        unsigned int p = (unsigned int)((uintptr_t)gen & 0xFFFFFFFF);
        gen->rng_state = t ^ (p * 2654435761u);
        if (gen->rng_state == 0) gen->rng_state = 0xDEADBEEF;
    }
    for (int i = 0; i < 16; i++) xorshift32(&gen->rng_state);
}

static int leet_rand_percent(LeetGenerator* gen) {
    return (int)(xorshift32(&gen->rng_state) % 100);
}

static int leet_rand_n(LeetGenerator* gen, int n) {
    if (n <= 1) return 0;
    return (int)(xorshift32(&gen->rng_state) % (unsigned int)n);
}

static unsigned int hash_pattern(const wchar_t* pattern, int length) {
    unsigned int hash = 5381;
    for (int i = 0; i < length; i++) {
        hash = ((hash << 5) + hash) + (unsigned int)pattern[i];
    }
    return hash % 1024;
}

static LeetRule* create_extended_rules(int* count) {
    *count = 26;
    LeetRule* rules = (LeetRule*)safe_calloc(*count, sizeof(LeetRule));
    if (!rules) return NULL;

#define ADD_RULE(idx, orig, cap, ...) \
    do { \
        const char* _repls[] = { __VA_ARGS__ }; \
        int _n = (int)(sizeof(_repls)/sizeof(_repls[0])); \
        rules[idx].original = (orig); \
        rules[idx].replacements = (char**)safe_malloc(_n * sizeof(char*)); \
        if (!rules[idx].replacements) return NULL; \
        rules[idx].count = _n; \
        int _maxlen = 0; \
        for (int _i = 0; _i < _n; _i++) { \
            rules[idx].replacements[_i] = safe_strdup(_repls[_i]); \
            if (!rules[idx].replacements[_i]) return NULL; \
            int _l = (int)strlen(_repls[_i]); \
            if (_l > _maxlen) _maxlen = _l; \
        } \
        rules[idx].maxReplacementLength = _maxlen; \
    } while(0)

    ADD_RULE( 0, 'a', 12, "@","4","/\\","/-\\","Д","α","λ","а","∀","Δ","ª","Ä");
    ADD_RULE( 1, 'b', 10, "8","|3","ß","13","|o","!3","(3","฿","в","β");
    ADD_RULE( 2, 'c',  9, "(","<","{","©","¢","с","ς","☾","🌑");
    ADD_RULE( 3, 'd',  8, "|)","đ","ď","cl","Ð","∂","♫","╫");
    ADD_RULE( 4, 'e', 12, "3","€","&","£","ë","е","Ē","Ɛ","∈","€","ⴹ","⋲");
    ADD_RULE( 5, 'f',  7, "|=","ƒ","ph","(=)","₣","♭","⨍");
    ADD_RULE( 6, 'g',  7, "9","6","&","g","ğ","ɢ","❡");
    ADD_RULE( 7, 'h',  8, "#","|-|","]-[","}-{","н","ħ","ℍ","♄");
    ADD_RULE( 8, 'i', 10, "1","!","|","][","ï","і","ɪ","‼","⁑","⚡");
    ADD_RULE( 9, 'j',  6, "_|","]","ј","ʝ","⌡","ʲ");
    ADD_RULE(10, 'k',  7, "|<","|(","ķ","κ","ќ","ƙ","𝕜");
    ADD_RULE(11, 'l',  9, "1","|","£","|_","ł","ļ","ℓ","└","Ⳑ");
    ADD_RULE(12, 'm',  9, "|V|","IVI","|\\/|","м","Ⓜ","♏","ɱ","ᵯ","𐌑");
    ADD_RULE(13, 'n',  8, "|\\|","/\\/","п","ñ","ń","η","ℕ","∩");
    ADD_RULE(14, 'o', 12, "0","()","[]","<>","Ø","ⵁ","⊕","◯","ⴱ","ø","ö","œ");
    ADD_RULE(15, 'p',  8, "|*","|o","|>","|7","р","þ","¶","♇");
    ADD_RULE(16, 'q',  6, "(,)","0,","9","ҩ","ʠ","ⵕ");
    ADD_RULE(17, 'r',  9, "|2","|?","|^","®","ř","я","ʁ","ᴚ","ℝ");
    ADD_RULE(18, 's', 11, "$","5","z","§","ş","ś","ѕ","ʂ","⚡","𐑈","🌠");
    ADD_RULE(19, 't', 10, "7","+","†","¥","т","ŧ","⊥","┳","╦","⫟");
    ADD_RULE(20, 'u',  8, "|_|","µ","ü","υ","ц","∩","∪","⋃");
    ADD_RULE(21, 'v',  7, "\\/","|/","√","ν","ѵ","▼","♢");
    ADD_RULE(22, 'w',  9, "\\/\\/","VV","ω","ш","ฬ","ʍ","ẁ","⚡","𐐎");
    ADD_RULE(23, 'x',  7, "><","×","Ж","χ","✕","✖","☓");
    ADD_RULE(24, 'y',  7, "¥","ÿ","γ","у","ɏ","ψ","♇");
    ADD_RULE(25, 'z',  7, "2","~/_","ζ","з","ź","ℤ","⚡");

#undef ADD_RULE

    return rules;
}

static void build_reverse_map(LeetGenerator* gen) {
    if (!gen || !gen->rules) return;

    gen->reverseMap = (LeetReverseMap**)safe_calloc(1024, sizeof(LeetReverseMap*));
    if (!gen->reverseMap) return;

    for (int i = 0; i < gen->ruleCount; i++) {
        LeetRule* rule = &gen->rules[i];

        for (int j = 0; j < rule->count; j++) {
            size_t len = strlen(rule->replacements[j]);
            wchar_t* pattern = (wchar_t*)safe_malloc((len + 1) * sizeof(wchar_t));
            if (!pattern) continue;

            size_t converted = mbstowcs(pattern, rule->replacements[j], len + 1);
            if (converted == (size_t)-1) {
                free(pattern);
                continue;
            }

            unsigned int hash = hash_pattern(pattern, (int)converted);

            LeetReverseMap* entry = (LeetReverseMap*)safe_malloc(sizeof(LeetReverseMap));
            if (!entry) { free(pattern); continue; }
            entry->pattern       = pattern;
            entry->original      = rule->original;
            entry->patternLength = (int)converted;
            entry->next          = gen->reverseMap[hash];
            gen->reverseMap[hash] = entry;

            wchar_t* upper = (wchar_t*)safe_malloc((converted + 1) * sizeof(wchar_t));
            if (upper) {
                for (size_t k = 0; k < converted; k++)
                    upper[k] = towupper(pattern[k]);
                upper[converted] = L'\0';

                unsigned int uhash = hash_pattern(upper, (int)converted);
                LeetReverseMap* ue = (LeetReverseMap*)safe_malloc(sizeof(LeetReverseMap));
                if (ue) {
                    ue->pattern       = upper;
                    ue->original      = toupper((unsigned char)rule->original);
                    ue->patternLength = (int)converted;
                    ue->next          = gen->reverseMap[uhash];
                    gen->reverseMap[uhash] = ue;
                } else {
                    free(upper);
                }
            }
        }
    }
}

LEET_API LeetGenerator* leet_create_generator(void) {
    leet_clear_error();

    LeetGenerator* gen = (LeetGenerator*)safe_calloc(1, sizeof(LeetGenerator));
    if (!gen) return NULL;

    gen->rules = create_extended_rules(&gen->ruleCount);
    if (!gen->rules) {
        free(gen);
        set_error(LEET_ERR_MEMORY, "failed to create rules");
        return NULL;
    }

    gen->useMultiChar    = 1;
    gen->preserveCase    = 0;
    gen->cacheSize       = 512;
    gen->replacementChance = 50;
    gen->caseChangeChance  = 30;
    gen->useSeed         = 0;
    gen->seed            = 0;

    leet_init_rng(gen);
    build_reverse_map(gen);

    if (!gen->reverseMap) {
        leet_destroy_generator(gen);
        set_error(LEET_ERR_MEMORY, "failed to build reverse map");
        return NULL;
    }

    return gen;
}

LEET_API void leet_destroy_generator(LeetGenerator* generator) {
    if (!generator) return;

    if (generator->rules) {
        for (int i = 0; i < generator->ruleCount; i++) {
            if (generator->rules[i].replacements) {
                for (int j = 0; j < generator->rules[i].count; j++)
                    free(generator->rules[i].replacements[j]);
                free(generator->rules[i].replacements);
            }
        }
        free(generator->rules);
    }

    if (generator->reverseMap) {
        for (int i = 0; i < 1024; i++) {
            LeetReverseMap* entry = generator->reverseMap[i];
            while (entry) {
                LeetReverseMap* next = entry->next;
                free(entry->pattern);
                free(entry);
                entry = next;
            }
        }
        free(generator->reverseMap);
    }

    if (generator->wordCache) {
        for (int i = 0; i < generator->cacheCount; i++)
            free(generator->wordCache[i]);
        free(generator->wordCache);
        free(generator->cacheLengths);
    }

    free(generator);
}

LEET_API void leet_set_replacement_chance(LeetGenerator* generator, int chance) {
    if (!generator) return;
    if (chance < 0)   chance = 0;
    if (chance > 100) chance = 100;
    generator->replacementChance = chance;
}

LEET_API void leet_set_case_chance(LeetGenerator* generator, int chance) {
    if (!generator) return;
    if (chance < 0)   chance = 0;
    if (chance > 100) chance = 100;
    generator->caseChangeChance = chance;
}

LEET_API void leet_set_seed(LeetGenerator* generator, unsigned int seed) {
    if (!generator) return;
    generator->seed    = seed;
    generator->useSeed = 1;
    leet_init_rng(generator);
}

LEET_API void leet_randomize_seed(LeetGenerator* generator) {
    if (!generator) return;
    generator->useSeed = 0;
    leet_init_rng(generator);
}

LEET_API void leet_set_use_multichar(LeetGenerator* generator, int use) {
    if (generator) generator->useMultiChar = use;
}

LEET_API void leet_set_preserve_case(LeetGenerator* generator, int preserve) {
    if (generator) generator->preserveCase = preserve;
}

LEET_API void leet_set_cache_size(LeetGenerator* generator, int maxKB) {
    if (!generator) return;
    generator->cacheSize = maxKB;
    if (generator->wordCache) leet_clear_cache(generator);
}

static LeetRule* find_rule(LeetGenerator* generator, char c) {
    if (!generator || !generator->rules) return NULL;
    c = (char)tolower((unsigned char)c);
    for (int i = 0; i < generator->ruleCount; i++) {
        if (generator->rules[i].original == c)
            return &generator->rules[i];
    }
    return NULL;
}

LEET_API wchar_t* leet_encrypt_word(LeetGenerator* generator, const char* word) {
    if (!generator || !word) {
        set_error(LEET_ERR_NULL_PTR, "null argument to leet_encrypt_word");
        return NULL;
    }
    leet_clear_error();

    int len        = (int)strlen(word);
    int bufferSize = len * 4 + 1;

    wchar_t* result = (wchar_t*)safe_malloc(bufferSize * sizeof(wchar_t));
    if (!result) return NULL;

    int resultIndex = 0;

    for (int i = 0; i < len; i++) {
        char currentChar = word[i];
        LeetRule* rule   = find_rule(generator, currentChar);

        if (rule && leet_rand_percent(generator) < generator->replacementChance) {
            int repIndex     = leet_rand_n(generator, rule->count);
            char* replacement = rule->replacements[repIndex];

            wchar_t wc[16];
            size_t wlen = mbstowcs(wc, replacement, sizeof(wc)/sizeof(wc[0]) - 1);
            if (wlen != (size_t)-1) {
                if (resultIndex + (int)wlen >= bufferSize) {
                    bufferSize += 64;
                    wchar_t* tmp = (wchar_t*)realloc(result, bufferSize * sizeof(wchar_t));
                    if (!tmp) {
                        free(result);
                        set_error(LEET_ERR_MEMORY, "realloc failed in encrypt_word");
                        return NULL;
                    }
                    result = tmp;
                }
                for (size_t j = 0; j < wlen; j++)
                    result[resultIndex++] = wc[j];
            } else {
                result[resultIndex++] = (wchar_t)currentChar;
            }
        } else {
            if (!generator->preserveCase &&
                leet_rand_percent(generator) < generator->caseChangeChance) {
                result[resultIndex++] = (wchar_t)toupper((unsigned char)currentChar);
            } else {
                result[resultIndex++] = (wchar_t)currentChar;
            }
        }
    }

    result[resultIndex] = L'\0';
    return result;
}

LEET_API LeetEncryptedMessage* leet_encrypt_message(LeetGenerator* generator,
                                                    const char* message) {
    if (!generator || !message) {
        set_error(LEET_ERR_NULL_PTR, "null argument to leet_encrypt_message");
        return NULL;
    }
    leet_clear_error();

    LeetEncryptedMessage* msg =
        (LeetEncryptedMessage*)safe_malloc(sizeof(LeetEncryptedMessage));
    if (!msg) return NULL;

    msg->originalLength = (int)strlen(message);
    msg->metadata       = NULL;

    char* msg_copy = safe_strdup(message);
    if (!msg_copy) { free(msg); return NULL; }

    int wordCount = 0;
    char* p = msg_copy;
    while (*p) {
        while (*p == ' ') p++;
        if (*p) { wordCount++; while (*p && *p != ' ') p++; }
    }

    if (wordCount == 0) {
        free(msg_copy);
        msg->words     = NULL;
        msg->wordCount = 0;
        return msg;
    }

    wchar_t** words = (wchar_t**)safe_calloc(wordCount, sizeof(wchar_t*));
    if (!words) { free(msg_copy); free(msg); return NULL; }

    int idx = 0;
    char* saveptr = NULL;
    char* token   = strtok_r(msg_copy, " ", &saveptr);
    while (token && idx < wordCount) {
        words[idx] = leet_encrypt_word(generator, token);
        if (!words[idx]) {
            for (int k = 0; k < idx; k++) free(words[k]);
            free(words);
            free(msg_copy);
            free(msg);
            return NULL;
        }
        idx++;
        token = strtok_r(NULL, " ", &saveptr);
    }

    free(msg_copy);
    msg->words     = words;
    msg->wordCount = idx;
    return msg;
}

LEET_API char* leet_decrypt_word(LeetGenerator* generator, const wchar_t* leetWord) {
    if (!generator || !generator->reverseMap || !leetWord) {
        set_error(LEET_ERR_NULL_PTR, "null argument to leet_decrypt_word");
        return NULL;
    }
    leet_clear_error();

    int len     = (int)wcslen(leetWord);
    char* result = (char*)safe_malloc(len * 4 + 1);
    if (!result) return NULL;

    int resultIndex = 0;
    int pos         = 0;
    int unknown     = 0;

    while (pos < len) {
        int matched = 0;

        for (int l = 4; l >= 1; l--) {
            if (pos + l > len) continue;

            unsigned int hash = hash_pattern(&leetWord[pos], l);
            LeetReverseMap* entry = generator->reverseMap[hash % 1024];

            while (entry) {
                if (entry->patternLength == l) {
                    int match = 1;
                    for (int i = 0; i < l; i++) {
                        if (entry->pattern[i] != leetWord[pos + i]) {
                            match = 0;
                            break;
                        }
                    }
                    if (match) {
                        result[resultIndex++] = entry->original;
                        pos     += l;
                        matched  = 1;
                        break;
                    }
                }
                entry = entry->next;
            }
            if (matched) break;
        }

        if (!matched) {
            if (leetWord[pos] < 128) {
                result[resultIndex++] = (char)leetWord[pos];
            } else {
                wchar_t single[2] = {leetWord[pos], L'\0'};
                unsigned int hash = hash_pattern(single, 1);
                LeetReverseMap* entry = generator->reverseMap[hash % 1024];
                int found = 0;

                while (entry) {
                    if (entry->patternLength == 1 &&
                        entry->pattern[0] == leetWord[pos]) {
                        result[resultIndex++] = entry->original;
                        found = 1;
                        break;
                    }
                    entry = entry->next;
                }

                if (!found) {
                    result[resultIndex++] = '?';
                    unknown++;
                }
            }
            pos++;
        }
    }

    result[resultIndex] = '\0';

    if (resultIndex > 0) {
        result[0] = (char)toupper((unsigned char)result[0]);
        for (int i = 1; i < resultIndex; i++)
            result[i] = (char)tolower((unsigned char)result[i]);
    }

    (void)unknown;
    return result;
}

LEET_API LeetDecryptResult* leet_decrypt_message(LeetGenerator* generator,
                                                 LeetEncryptedMessage* msg) {
    if (!generator || !msg) {
        set_error(LEET_ERR_NULL_PTR, "null argument to leet_decrypt_message");
        return NULL;
    }
    leet_clear_error();

    clock_t start = clock();

    LeetDecryptResult* result =
        (LeetDecryptResult*)safe_malloc(sizeof(LeetDecryptResult));
    if (!result) return NULL;

    if (msg->wordCount == 0) {
        result->text         = safe_strdup("");
        result->confidence   = 100;
        result->timeMs       = 0;
        result->unknownWords = 0;
        return result;
    }

    char** decryptedWords = (char**)safe_calloc(msg->wordCount, sizeof(char*));
    if (!decryptedWords) { free(result); return NULL; }

    int totalLength  = 0;
    int totalUnknown = 0;

    for (int i = 0; i < msg->wordCount; i++) {
        decryptedWords[i] = leet_decrypt_word(generator, msg->words[i]);
        if (decryptedWords[i]) {
            totalLength += (int)strlen(decryptedWords[i]) + 1;
            for (int j = 0; decryptedWords[i][j]; j++)
                if (decryptedWords[i][j] == '?') totalUnknown++;
        }
    }

    char* fullText = (char*)safe_malloc(totalLength + 1);
    if (!fullText) {
        for (int i = 0; i < msg->wordCount; i++) free(decryptedWords[i]);
        free(decryptedWords);
        free(result);
        return NULL;
    }
    fullText[0] = '\0';

    for (int i = 0; i < msg->wordCount; i++) {
        if (decryptedWords[i]) {
            strcat(fullText, decryptedWords[i]);
            if (i < msg->wordCount - 1) strcat(fullText, " ");
            free(decryptedWords[i]);
        }
    }
    free(decryptedWords);

    result->text         = fullText;
    result->unknownWords = totalUnknown;

    int totalChars = (int)strlen(fullText);
    result->confidence = (totalChars > 0)
        ? 100 - (totalUnknown * 100 / totalChars)
        : 0;

    result->timeMs = (int)((clock() - start) * 1000 / CLOCKS_PER_SEC);
    return result;
}

LEET_API LeetDecryptResult* leet_decrypt_words(LeetGenerator* generator,
                                               wchar_t** words, int wordCount) {
    if (!generator || !words || wordCount <= 0) {
        set_error(LEET_ERR_NULL_PTR, "null/empty argument to leet_decrypt_words");
        return NULL;
    }
    LeetEncryptedMessage msg;
    msg.words          = words;
    msg.wordCount      = wordCount;
    msg.originalLength = 0;
    msg.metadata       = NULL;
    return leet_decrypt_message(generator, &msg);
}

LEET_API void leet_free_decrypt_result(LeetDecryptResult* result) {
    if (result) {
        free(result->text);
        free(result);
    }
}

LEET_API void leet_free_encrypted_message(LeetEncryptedMessage* msg) {
    if (!msg) return;
    for (int i = 0; i < msg->wordCount; i++)
        free(msg->words[i]);
    free(msg->words);
    free(msg->metadata);
    free(msg);
}

LEET_API char* leet_unicode_to_utf8(const wchar_t* unicode) {
    if (!unicode) {
        set_error(LEET_ERR_NULL_PTR, "null unicode string");
        return NULL;
    }
    leet_clear_error();

    size_t len  = wcslen(unicode);
    size_t bufSize = len * 4 + 1;
    char*  utf8 = (char*)safe_malloc(bufSize);
    if (!utf8) return NULL;

    size_t converted = wcstombs(utf8, unicode, bufSize - 1);
    if (converted == (size_t)-1) {
        free(utf8);
        set_error(LEET_ERR_ENCODING, "wcstombs conversion failed");
        return NULL;
    }
    utf8[converted] = '\0';
    return utf8;
}

LEET_API void leet_cache_word(LeetGenerator* generator,
                              const char* word, const wchar_t* encrypted) {
    if (!generator || !word || !encrypted) return;

    if (!generator->wordCache) {
        generator->wordCache  = (char**)safe_calloc(1000, sizeof(char*));
        generator->cacheLengths = (int*)safe_calloc(1000, sizeof(int));
        generator->cacheCount = 0;
        if (!generator->wordCache || !generator->cacheLengths) return;
    }

    if (generator->cacheCount < 1000) {
        char* dup = safe_strdup(word);
        if (!dup) return;
        generator->wordCache[generator->cacheCount]   = dup;
        generator->cacheLengths[generator->cacheCount] = (int)wcslen(encrypted);
        generator->cacheCount++;
    }
}

LEET_API const char* leet_lookup_cache(LeetGenerator* generator, const char* word) {
    if (!generator || !generator->wordCache || !word) return NULL;
    for (int i = 0; i < generator->cacheCount; i++) {
        if (generator->wordCache[i] &&
            strcmp(generator->wordCache[i], word) == 0)
            return generator->wordCache[i];
    }
    return NULL;
}

LEET_API void leet_clear_cache(LeetGenerator* generator) {
    if (!generator || !generator->wordCache) return;
    for (int i = 0; i < generator->cacheCount; i++)
        free(generator->wordCache[i]);
    free(generator->wordCache);
    free(generator->cacheLengths);
    generator->wordCache    = NULL;
    generator->cacheLengths = NULL;
    generator->cacheCount   = 0;
}

LEET_API void leet_print_hex(const char* data, int length) {
    for (int i = 0; i < length; i++)
        printf("%02x", (unsigned char)data[i]);
    printf("\n");
}

LEET_API void leet_print_stats(LeetGenerator* generator) {
    if (!generator) return;
    printf("Leet Generator Statistics:\n");
    printf("  Rules:              %d\n",  generator->ruleCount);
    printf("  Replacement chance: %d%%\n", generator->replacementChance);
    printf("  Case change chance: %d%%\n", generator->caseChangeChance);
    printf("  Use seed:           %s\n",  generator->useSeed ? "yes" : "no");
    if (generator->useSeed)
        printf("  Seed:               %u\n", generator->seed);
    printf("  Cache size:         %d KB\n", generator->cacheSize);
    printf("  Cached words:       %d\n",  generator->cacheCount);
    printf("  Last error:         [%d] %s\n",
           g_last_error,
           g_error_msg[0] ? g_error_msg : "none");
}

LEET_API void leet_print_reverse_map(LeetGenerator* generator) {
    if (!generator || !generator->reverseMap) return;
    printf("Reverse Map:\n");
    for (int i = 0; i < 1024; i++) {
        LeetReverseMap* entry = generator->reverseMap[i];
        while (entry) {
            printf("  %ls -> %c (len=%d)\n",
                   entry->pattern, entry->original, entry->patternLength);
            entry = entry->next;
        }
    }
}
