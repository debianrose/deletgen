#include "leet_generator.h"

static unsigned int hash_pattern(const wchar_t* pattern, int length) {
    unsigned int hash = 5381;
    for (int i = 0; i < length; i++) {
        hash = ((hash << 5) + hash) + pattern[i];
    }
    return hash % 1024;
}

static void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr && size > 0) {
        fprintf(stderr, "Ошибка: не удалось выделить %zu байт памяти\n", size);
        exit(1);
    }
    return ptr;
}

static void* safe_calloc(size_t count, size_t size) {
    void* ptr = calloc(count, size);
    if (!ptr && count > 0 && size > 0) {
        fprintf(stderr, "Ошибка: не удалось выделить память\n");
        exit(1);
    }
    return ptr;
}

static wchar_t* safe_wcsdup(const wchar_t* s) {
    if (!s) return NULL;
    size_t len = wcslen(s) + 1;
    wchar_t* new_str = (wchar_t*)safe_malloc(len * sizeof(wchar_t));
    wcscpy(new_str, s);
    return new_str;
}

static char* safe_strdup(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char* new_str = (char*)safe_malloc(len);
    memcpy(new_str, s, len);
    return new_str;
}

static void leet_init_rng(LeetGenerator* gen) {
    if (gen->useSeed) {
        srand(gen->seed);
    } else {
        srand(time(NULL));
    }
}

static LeetRule* create_extended_rules(int* count) {
    *count = 26;
    LeetRule* rules = (LeetRule*)safe_calloc(*count, sizeof(LeetRule));
    
    // A/a
    rules[0].original = 'a';
    rules[0].replacements = (char**)safe_malloc(12 * sizeof(char*));
    rules[0].replacements[0] = safe_strdup("@");
    rules[0].replacements[1] = safe_strdup("4");
    rules[0].replacements[2] = safe_strdup("/\\");
    rules[0].replacements[3] = safe_strdup("/-\\");
    rules[0].replacements[4] = safe_strdup("Д");
    rules[0].replacements[5] = safe_strdup("α");
    rules[0].replacements[6] = safe_strdup("λ");
    rules[0].replacements[7] = safe_strdup("а");
    rules[0].replacements[8] = safe_strdup("∀");
    rules[0].replacements[9] = safe_strdup("Δ");
    rules[0].replacements[10] = safe_strdup("ª");
    rules[0].replacements[11] = safe_strdup("Ä");
    rules[0].count = 12;
    rules[0].maxReplacementLength = 3;
    
    // B/b
    rules[1].original = 'b';
    rules[1].replacements = (char**)safe_malloc(10 * sizeof(char*));
    rules[1].replacements[0] = safe_strdup("8");
    rules[1].replacements[1] = safe_strdup("|3");
    rules[1].replacements[2] = safe_strdup("ß");
    rules[1].replacements[3] = safe_strdup("13");
    rules[1].replacements[4] = safe_strdup("|o");
    rules[1].replacements[5] = safe_strdup("!3");
    rules[1].replacements[6] = safe_strdup("(3");
    rules[1].replacements[7] = safe_strdup("฿");
    rules[1].replacements[8] = safe_strdup("в");
    rules[1].replacements[9] = safe_strdup("β");
    rules[1].count = 10;
    rules[1].maxReplacementLength = 2;
    
    // C/c
    rules[2].original = 'c';
    rules[2].replacements = (char**)safe_malloc(9 * sizeof(char*));
    rules[2].replacements[0] = safe_strdup("(");
    rules[2].replacements[1] = safe_strdup("<");
    rules[2].replacements[2] = safe_strdup("{");
    rules[2].replacements[3] = safe_strdup("©");
    rules[2].replacements[4] = safe_strdup("¢");
    rules[2].replacements[5] = safe_strdup("с");
    rules[2].replacements[6] = safe_strdup("ς");
    rules[2].replacements[7] = safe_strdup("☾");
    rules[2].replacements[8] = safe_strdup("🌑");
    rules[2].count = 9;
    rules[2].maxReplacementLength = 2;
    
    rules[3].original = 'd';
    rules[3].replacements = (char**)safe_malloc(8 * sizeof(char*));
    rules[3].replacements[0] = safe_strdup("|)");
    rules[3].replacements[1] = safe_strdup("đ");
    rules[3].replacements[2] = safe_strdup("ď");
    rules[3].replacements[3] = safe_strdup("cl");
    rules[3].replacements[4] = safe_strdup("Ð");
    rules[3].replacements[5] = safe_strdup("∂");
    rules[3].replacements[6] = safe_strdup("♫");
    rules[3].replacements[7] = safe_strdup("╫");
    rules[3].count = 8;
    rules[3].maxReplacementLength = 2;
    
    // E/e
    rules[4].original = 'e';
    rules[4].replacements = (char**)safe_malloc(12 * sizeof(char*));
    rules[4].replacements[0] = safe_strdup("3");
    rules[4].replacements[1] = safe_strdup("€");
    rules[4].replacements[2] = safe_strdup("&");
    rules[4].replacements[3] = safe_strdup("£");
    rules[4].replacements[4] = safe_strdup("ë");
    rules[4].replacements[5] = safe_strdup("е");
    rules[4].replacements[6] = safe_strdup("Ē");
    rules[4].replacements[7] = safe_strdup("Ɛ");
    rules[4].replacements[8] = safe_strdup("∈");
    rules[4].replacements[9] = safe_strdup("€");
    rules[4].replacements[10] = safe_strdup("ⴹ");
    rules[4].replacements[11] = safe_strdup("⋲");
    rules[4].count = 12;
    rules[4].maxReplacementLength = 2;
    
    // F/f
    rules[5].original = 'f';
    rules[5].replacements = (char**)safe_malloc(7 * sizeof(char*));
    rules[5].replacements[0] = safe_strdup("|=");
    rules[5].replacements[1] = safe_strdup("ƒ");
    rules[5].replacements[2] = safe_strdup("ph");
    rules[5].replacements[3] = safe_strdup("(=)");
    rules[5].replacements[4] = safe_strdup("₣");
    rules[5].replacements[5] = safe_strdup("♭");
    rules[5].replacements[6] = safe_strdup("⨍");
    rules[5].count = 7;
    rules[5].maxReplacementLength = 3;
    
    // G/g
    rules[6].original = 'g';
    rules[6].replacements = (char**)safe_malloc(7 * sizeof(char*));
    rules[6].replacements[0] = safe_strdup("9");
    rules[6].replacements[1] = safe_strdup("6");
    rules[6].replacements[2] = safe_strdup("&");
    rules[6].replacements[3] = safe_strdup("g");
    rules[6].replacements[4] = safe_strdup("ğ");
    rules[6].replacements[5] = safe_strdup("ɢ");
    rules[6].replacements[6] = safe_strdup("❡");
    rules[6].count = 7;
    rules[6].maxReplacementLength = 1;
    
    // H/h
    rules[7].original = 'h';
    rules[7].replacements = (char**)safe_malloc(8 * sizeof(char*));
    rules[7].replacements[0] = safe_strdup("#");
    rules[7].replacements[1] = safe_strdup("|-|");
    rules[7].replacements[2] = safe_strdup("]-[");
    rules[7].replacements[3] = safe_strdup("}-{");
    rules[7].replacements[4] = safe_strdup("н");
    rules[7].replacements[5] = safe_strdup("ħ");
    rules[7].replacements[6] = safe_strdup("ℍ");
    rules[7].replacements[7] = safe_strdup("♄");
    rules[7].count = 8;
    rules[7].maxReplacementLength = 3;
    
    // I/i
    rules[8].original = 'i';
    rules[8].replacements = (char**)safe_malloc(10 * sizeof(char*));
    rules[8].replacements[0] = safe_strdup("1");
    rules[8].replacements[1] = safe_strdup("!");
    rules[8].replacements[2] = safe_strdup("|");
    rules[8].replacements[3] = safe_strdup("][");
    rules[8].replacements[4] = safe_strdup("ï");
    rules[8].replacements[5] = safe_strdup("і");
    rules[8].replacements[6] = safe_strdup("ɪ");
    rules[8].replacements[7] = safe_strdup("‼");
    rules[8].replacements[8] = safe_strdup("⁑");
    rules[8].replacements[9] = safe_strdup("⚡");
    rules[8].count = 10;
    rules[8].maxReplacementLength = 2;
    
    // J/j
    rules[9].original = 'j';
    rules[9].replacements = (char**)safe_malloc(6 * sizeof(char*));
    rules[9].replacements[0] = safe_strdup("_|");
    rules[9].replacements[1] = safe_strdup("]");
    rules[9].replacements[2] = safe_strdup("ј");
    rules[9].replacements[3] = safe_strdup("ʝ");
    rules[9].replacements[4] = safe_strdup("⌡");
    rules[9].replacements[5] = safe_strdup("ʲ");
    rules[9].count = 6;
    rules[9].maxReplacementLength = 2;
    
    // K/k
    rules[10].original = 'k';
    rules[10].replacements = (char**)safe_malloc(7 * sizeof(char*));
    rules[10].replacements[0] = safe_strdup("|<");
    rules[10].replacements[1] = safe_strdup("|(");
    rules[10].replacements[2] = safe_strdup("ķ");
    rules[10].replacements[3] = safe_strdup("κ");
    rules[10].replacements[4] = safe_strdup("ќ");
    rules[10].replacements[5] = safe_strdup("ƙ");
    rules[10].replacements[6] = safe_strdup("𝕜");
    rules[10].count = 7;
    rules[10].maxReplacementLength = 2;
    
    // L/l
    rules[11].original = 'l';
    rules[11].replacements = (char**)safe_malloc(9 * sizeof(char*));
    rules[11].replacements[0] = safe_strdup("1");
    rules[11].replacements[1] = safe_strdup("|");
    rules[11].replacements[2] = safe_strdup("£");
    rules[11].replacements[3] = safe_strdup("|_");
    rules[11].replacements[4] = safe_strdup("ł");
    rules[11].replacements[5] = safe_strdup("ļ");
    rules[11].replacements[6] = safe_strdup("ℓ");
    rules[11].replacements[7] = safe_strdup("└");
    rules[11].replacements[8] = safe_strdup("Ⳑ");
    rules[11].count = 9;
    rules[11].maxReplacementLength = 2;
    
    // M/m
    rules[12].original = 'm';
    rules[12].replacements = (char**)safe_malloc(9 * sizeof(char*));
    rules[12].replacements[0] = safe_strdup("|V|");
    rules[12].replacements[1] = safe_strdup("IVI");
    rules[12].replacements[2] = safe_strdup("|\\/|");
    rules[12].replacements[3] = safe_strdup("м");
    rules[12].replacements[4] = safe_strdup("Ⓜ");
    rules[12].replacements[5] = safe_strdup("♏");
    rules[12].replacements[6] = safe_strdup("ɱ");
    rules[12].replacements[7] = safe_strdup("ᵯ");
    rules[12].replacements[8] = safe_strdup("𐌑");
    rules[12].count = 9;
    rules[12].maxReplacementLength = 4;
    
    // N/n
    rules[13].original = 'n';
    rules[13].replacements = (char**)safe_malloc(8 * sizeof(char*));
    rules[13].replacements[0] = safe_strdup("|\\|");
    rules[13].replacements[1] = safe_strdup("/\\/");
    rules[13].replacements[2] = safe_strdup("п");
    rules[13].replacements[3] = safe_strdup("ñ");
    rules[13].replacements[4] = safe_strdup("ń");
    rules[13].replacements[5] = safe_strdup("η");
    rules[13].replacements[6] = safe_strdup("ℕ");
    rules[13].replacements[7] = safe_strdup("∩");
    rules[13].count = 8;
    rules[13].maxReplacementLength = 3;
    
    // O/o
    rules[14].original = 'o';
    rules[14].replacements = (char**)safe_malloc(12 * sizeof(char*));
    rules[14].replacements[0] = safe_strdup("0");
    rules[14].replacements[1] = safe_strdup("()");
    rules[14].replacements[2] = safe_strdup("[]");
    rules[14].replacements[3] = safe_strdup("<>");
    rules[14].replacements[4] = safe_strdup("Ø");
    rules[14].replacements[5] = safe_strdup("ⵁ");
    rules[14].replacements[6] = safe_strdup("⊕");
    rules[14].replacements[7] = safe_strdup("◯");
    rules[14].replacements[8] = safe_strdup("ⴱ");
    rules[14].replacements[9] = safe_strdup("ø");
    rules[14].replacements[10] = safe_strdup("ö");
    rules[14].replacements[11] = safe_strdup("œ");
    rules[14].count = 12;
    rules[14].maxReplacementLength = 2;
    
    // P/p
    rules[15].original = 'p';
    rules[15].replacements = (char**)safe_malloc(8 * sizeof(char*));
    rules[15].replacements[0] = safe_strdup("|*");
    rules[15].replacements[1] = safe_strdup("|o");
    rules[15].replacements[2] = safe_strdup("|>");
    rules[15].replacements[3] = safe_strdup("|7");
    rules[15].replacements[4] = safe_strdup("р");
    rules[15].replacements[5] = safe_strdup("þ");
    rules[15].replacements[6] = safe_strdup("¶");
    rules[15].replacements[7] = safe_strdup("♇");
    rules[15].count = 8;
    rules[15].maxReplacementLength = 2;
    
    // Q/q
    rules[16].original = 'q';
    rules[16].replacements = (char**)safe_malloc(6 * sizeof(char*));
    rules[16].replacements[0] = safe_strdup("(,)");
    rules[16].replacements[1] = safe_strdup("0,");
    rules[16].replacements[2] = safe_strdup("9");
    rules[16].replacements[3] = safe_strdup("ҩ");
    rules[16].replacements[4] = safe_strdup("ʠ");
    rules[16].replacements[5] = safe_strdup("ⵕ");
    rules[16].count = 6;
    rules[16].maxReplacementLength = 3;
    
    // R/r
    rules[17].original = 'r';
    rules[17].replacements = (char**)safe_malloc(9 * sizeof(char*));
    rules[17].replacements[0] = safe_strdup("|2");
    rules[17].replacements[1] = safe_strdup("|?");
    rules[17].replacements[2] = safe_strdup("|^");
    rules[17].replacements[3] = safe_strdup("®");
    rules[17].replacements[4] = safe_strdup("ř");
    rules[17].replacements[5] = safe_strdup("я");
    rules[17].replacements[6] = safe_strdup("ʁ");
    rules[17].replacements[7] = safe_strdup("ᴚ");
    rules[17].replacements[8] = safe_strdup("ℝ");
    rules[17].count = 9;
    rules[17].maxReplacementLength = 2;
    
    // S/s
    rules[18].original = 's';
    rules[18].replacements = (char**)safe_malloc(11 * sizeof(char*));
    rules[18].replacements[0] = safe_strdup("$");
    rules[18].replacements[1] = safe_strdup("5");
    rules[18].replacements[2] = safe_strdup("z");
    rules[18].replacements[3] = safe_strdup("§");
    rules[18].replacements[4] = safe_strdup("ş");
    rules[18].replacements[5] = safe_strdup("ś");
    rules[18].replacements[6] = safe_strdup("ѕ");
    rules[18].replacements[7] = safe_strdup("ʂ");
    rules[18].replacements[8] = safe_strdup("⚡");
    rules[18].replacements[9] = safe_strdup("𐑈");
    rules[18].replacements[10] = safe_strdup("🌠");
    rules[18].count = 11;
    rules[18].maxReplacementLength = 2;
    
    // T/t
    rules[19].original = 't';
    rules[19].replacements = (char**)safe_malloc(10 * sizeof(char*));
    rules[19].replacements[0] = safe_strdup("7");
    rules[19].replacements[1] = safe_strdup("+");
    rules[19].replacements[2] = safe_strdup("†");
    rules[19].replacements[3] = safe_strdup("¥");
    rules[19].replacements[4] = safe_strdup("т");
    rules[19].replacements[5] = safe_strdup("ŧ");
    rules[19].replacements[6] = safe_strdup("⊥");
    rules[19].replacements[7] = safe_strdup("┳");
    rules[19].replacements[8] = safe_strdup("╦");
    rules[19].replacements[9] = safe_strdup("⫟");
    rules[19].count = 10;
    rules[19].maxReplacementLength = 2;
    
    // U/u
    rules[20].original = 'u';
    rules[20].replacements = (char**)safe_malloc(8 * sizeof(char*));
    rules[20].replacements[0] = safe_strdup("|_|");
    rules[20].replacements[1] = safe_strdup("µ");
    rules[20].replacements[2] = safe_strdup("ü");
    rules[20].replacements[3] = safe_strdup("υ");
    rules[20].replacements[4] = safe_strdup("ц");
    rules[20].replacements[5] = safe_strdup("∩");
    rules[20].replacements[6] = safe_strdup("∪");
    rules[20].replacements[7] = safe_strdup("⋃");
    rules[20].count = 8;
    rules[20].maxReplacementLength = 3;
    
    // V/v
    rules[21].original = 'v';
    rules[21].replacements = (char**)safe_malloc(7 * sizeof(char*));
    rules[21].replacements[0] = safe_strdup("\\/");
    rules[21].replacements[1] = safe_strdup("|/");
    rules[21].replacements[2] = safe_strdup("√");
    rules[21].replacements[3] = safe_strdup("ν");
    rules[21].replacements[4] = safe_strdup("ѵ");
    rules[21].replacements[5] = safe_strdup("▼");
    rules[21].replacements[6] = safe_strdup("♢");
    rules[21].count = 7;
    rules[21].maxReplacementLength = 2;
    
    // W/w
    rules[22].original = 'w';
    rules[22].replacements = (char**)safe_malloc(9 * sizeof(char*));
    rules[22].replacements[0] = safe_strdup("\\/\\/");
    rules[22].replacements[1] = safe_strdup("VV");
    rules[22].replacements[2] = safe_strdup("ω");
    rules[22].replacements[3] = safe_strdup("ш");
    rules[22].replacements[4] = safe_strdup("ฬ");
    rules[22].replacements[5] = safe_strdup("ʍ");
    rules[22].replacements[6] = safe_strdup("ẁ");
    rules[22].replacements[7] = safe_strdup("⚡");
    rules[22].replacements[8] = safe_strdup("𐐎");
    rules[22].count = 9;
    rules[22].maxReplacementLength = 4;
    
    // X/x
    rules[23].original = 'x';
    rules[23].replacements = (char**)safe_malloc(7 * sizeof(char*));
    rules[23].replacements[0] = safe_strdup("><");
    rules[23].replacements[1] = safe_strdup("×");
    rules[23].replacements[2] = safe_strdup("Ж");
    rules[23].replacements[3] = safe_strdup("χ");
    rules[23].replacements[4] = safe_strdup("✕");
    rules[23].replacements[5] = safe_strdup("✖");
    rules[23].replacements[6] = safe_strdup("☓");
    rules[23].count = 7;
    rules[23].maxReplacementLength = 2;
    
    // Y/y
    rules[24].original = 'y';
    rules[24].replacements = (char**)safe_malloc(7 * sizeof(char*));
    rules[24].replacements[0] = safe_strdup("¥");
    rules[24].replacements[1] = safe_strdup("ÿ");
    rules[24].replacements[2] = safe_strdup("γ");
    rules[24].replacements[3] = safe_strdup("у");
    rules[24].replacements[4] = safe_strdup("ɏ");
    rules[24].replacements[5] = safe_strdup("ψ");
    rules[24].replacements[6] = safe_strdup("♇");
    rules[24].count = 7;
    rules[24].maxReplacementLength = 2;
    
    // Z/z
    rules[25].original = 'z';
    rules[25].replacements = (char**)safe_malloc(7 * sizeof(char*));
    rules[25].replacements[0] = safe_strdup("2");
    rules[25].replacements[1] = safe_strdup("~/_");
    rules[25].replacements[2] = safe_strdup("ζ");
    rules[25].replacements[3] = safe_strdup("з");
    rules[25].replacements[4] = safe_strdup("ź");
    rules[25].replacements[5] = safe_strdup("ℤ");
    rules[25].replacements[6] = safe_strdup("⚡");
    rules[25].count = 7;
    rules[25].maxReplacementLength = 3;
    
    return rules;
}

static void build_reverse_map(LeetGenerator* gen) {
    if (!gen || !gen->rules) return;
    
    gen->reverseMap = (LeetReverseMap**)safe_calloc(1024, sizeof(LeetReverseMap*));
    
    for (int i = 0; i < gen->ruleCount; i++) {
        LeetRule* rule = &gen->rules[i];
        
        for (int j = 0; j < rule->count; j++) {
            size_t len = strlen(rule->replacements[j]);
            wchar_t* pattern = (wchar_t*)safe_malloc((len + 1) * sizeof(wchar_t));
            
            size_t converted = mbstowcs(pattern, rule->replacements[j], len + 1);
            if (converted == (size_t)-1) {
                free(pattern);
                continue;
            }
            
            unsigned int hash = hash_pattern(pattern, converted);
            
            LeetReverseMap* entry = (LeetReverseMap*)safe_malloc(sizeof(LeetReverseMap));
            entry->pattern = pattern;
            entry->original = rule->original;
            entry->patternLength = converted;
            entry->next = gen->reverseMap[hash];
            gen->reverseMap[hash] = entry;
            
            wchar_t* upper_pattern = (wchar_t*)safe_malloc((converted + 1) * sizeof(wchar_t));
            if (upper_pattern) {
                for (int k = 0; k < converted; k++) {
                    upper_pattern[k] = towupper(pattern[k]);
                }
                upper_pattern[converted] = L'\0';
                
                hash = hash_pattern(upper_pattern, converted);
                LeetReverseMap* upper_entry = (LeetReverseMap*)safe_malloc(sizeof(LeetReverseMap));
                upper_entry->pattern = upper_pattern;
                upper_entry->original = toupper(rule->original);
                upper_entry->patternLength = converted;
                upper_entry->next = gen->reverseMap[hash];
                gen->reverseMap[hash] = upper_entry;
            }
        }
    }
}

LEET_API LeetGenerator* leet_create_generator(void) {
    LeetGenerator* gen = (LeetGenerator*)safe_calloc(1, sizeof(LeetGenerator));
    
    gen->rules = create_extended_rules(&gen->ruleCount);
    gen->useMultiChar = 1;
    gen->preserveCase = 0;
    gen->cacheSize = 512;
    
    // Настройки рандомайзера по умолчанию
    gen->replacementChance = 50;  // 50% шанс замены
    gen->caseChangeChance = 30;   // 30% шанс смены регистра
    gen->useSeed = 0;
    gen->seed = 0;
    
    leet_init_rng(gen);
    build_reverse_map(gen);
    
    return gen;
}

LEET_API void leet_destroy_generator(LeetGenerator* generator) {
    if (!generator) return;
    
    if (generator->rules) {
        for (int i = 0; i < generator->ruleCount; i++) {
            if (generator->rules[i].replacements) {
                for (int j = 0; j < generator->rules[i].count; j++) {
                    free(generator->rules[i].replacements[j]);
                }
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
        for (int i = 0; i < generator->cacheCount; i++) {
            free(generator->wordCache[i]);
        }
        free(generator->wordCache);
        free(generator->cacheLengths);
    }
    
    free(generator);
}

LEET_API void leet_set_replacement_chance(LeetGenerator* generator, int chance) {
    if (generator) {
        if (chance < 0) chance = 0;
        if (chance > 100) chance = 100;
        generator->replacementChance = chance;
    }
}

LEET_API void leet_set_case_chance(LeetGenerator* generator, int chance) {
    if (generator) {
        if (chance < 0) chance = 0;
        if (chance > 100) chance = 100;
        generator->caseChangeChance = chance;
    }
}

LEET_API void leet_set_seed(LeetGenerator* generator, unsigned int seed) {
    if (generator) {
        generator->seed = seed;
        generator->useSeed = 1;
        leet_init_rng(generator);
    }
}

LEET_API void leet_randomize_seed(LeetGenerator* generator) {
    if (generator) {
        generator->useSeed = 0;
        leet_init_rng(generator);
    }
}

LEET_API void leet_set_use_multichar(LeetGenerator* generator, int use) {
    if (generator) generator->useMultiChar = use;
}

LEET_API void leet_set_preserve_case(LeetGenerator* generator, int preserve) {
    if (generator) generator->preserveCase = preserve;
}

LEET_API void leet_set_cache_size(LeetGenerator* generator, int maxKB) {
    if (generator) {
        generator->cacheSize = maxKB;
        if (generator->wordCache) {
            leet_clear_cache(generator);
        }
    }
}

static LeetRule* find_rule(LeetGenerator* generator, char c) {
    if (!generator || !generator->rules) return NULL;
    
    c = tolower((unsigned char)c);
    for (int i = 0; i < generator->ruleCount; i++) {
        if (generator->rules[i].original == c) {
            return &generator->rules[i];
        }
    }
    return NULL;
}

LEET_API wchar_t* leet_encrypt_word(LeetGenerator* generator, const char* word) {
    if (!generator || !word) return NULL;
    
    int len = strlen(word);
    int bufferSize = len * 4 + 1;
    
    wchar_t* result = (wchar_t*)safe_malloc(bufferSize * sizeof(wchar_t));
    int resultIndex = 0;
    
    for (int i = 0; i < len; i++) {
        char currentChar = word[i];
        LeetRule* rule = find_rule(generator, currentChar);
        
        if (rule && (rand() % 100) < generator->replacementChance) {
            int repIndex = rand() % rule->count;
            char* replacement = rule->replacements[repIndex];
            
            wchar_t wc[10];
            size_t wlen = mbstowcs(wc, replacement, 10);
            if (wlen != (size_t)-1) {
                for (size_t j = 0; j < wlen; j++) {
                    result[resultIndex++] = wc[j];
                }
            } else {
                result[resultIndex++] = currentChar;
            }
        } else {
            if (!generator->preserveCase && (rand() % 100) < generator->caseChangeChance) {
                result[resultIndex++] = toupper((unsigned char)currentChar);
            } else {
                result[resultIndex++] = currentChar;
            }
        }
    }
    
    result[resultIndex] = L'\0';
    return result;
}

LEET_API LeetEncryptedMessage* leet_encrypt_message(LeetGenerator* generator, const char* message) {
    if (!generator || !message) return NULL;
    
    LeetEncryptedMessage* msg = (LeetEncryptedMessage*)safe_malloc(sizeof(LeetEncryptedMessage));
    msg->originalLength = strlen(message);
    msg->metadata = NULL;
    
    char* msg_copy = safe_strdup(message);
    char* token = strtok(msg_copy, " ");
    int wordCount = 0;
    wchar_t** words = NULL;
    
    while (token) {
        wordCount++;
        words = (wchar_t**)realloc(words, wordCount * sizeof(wchar_t*));
        if (!words) {
            free(msg_copy);
            free(msg);
            return NULL;
        }
        words[wordCount-1] = leet_encrypt_word(generator, token);
        token = strtok(NULL, " ");
    }
    
    free(msg_copy);
    msg->words = words;
    msg->wordCount = wordCount;
    
    return msg;
}

LEET_API char* leet_decrypt_word(LeetGenerator* generator, const wchar_t* leetWord) {
    if (!generator || !generator->reverseMap || !leetWord) return NULL;
    
    int len = wcslen(leetWord);
    char* result = (char*)safe_malloc(len * 4 + 1);
    int resultIndex = 0;
    int pos = 0;
    int unknown = 0;
    
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
                        pos += l;
                        matched = 1;
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
                    if (entry->patternLength == 1 && entry->pattern[0] == leetWord[pos]) {
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
        result[0] = toupper((unsigned char)result[0]);
        for (int i = 1; i < resultIndex; i++) {
            result[i] = tolower((unsigned char)result[i]);
        }
    }
    
    return result;
}

LEET_API LeetDecryptResult* leet_decrypt_message(LeetGenerator* generator, LeetEncryptedMessage* msg) {
    if (!generator || !msg) return NULL;
    
    clock_t start = clock();
    
    LeetDecryptResult* result = (LeetDecryptResult*)safe_malloc(sizeof(LeetDecryptResult));
    
    char** decryptedWords = (char**)safe_malloc(msg->wordCount * sizeof(char*));
    int totalLength = 0;
    int totalUnknown = 0;
    
    for (int i = 0; i < msg->wordCount; i++) {
        decryptedWords[i] = leet_decrypt_word(generator, msg->words[i]);
        if (decryptedWords[i]) {
            totalLength += strlen(decryptedWords[i]) + 1;
            for (int j = 0; decryptedWords[i][j]; j++) {
                if (decryptedWords[i][j] == '?') totalUnknown++;
            }
        }
    }
    
    char* fullText = (char*)safe_malloc(totalLength + 1);
    fullText[0] = '\0';
    
    for (int i = 0; i < msg->wordCount; i++) {
        if (decryptedWords[i]) {
            strcat(fullText, decryptedWords[i]);
            if (i < msg->wordCount - 1) strcat(fullText, " ");
            free(decryptedWords[i]);
        }
    }
    
    free(decryptedWords);
    
    result->text = fullText;
    result->unknownWords = totalUnknown;
    
    int totalChars = strlen(fullText);
    if (totalChars > 0) {
        result->confidence = 100 - (totalUnknown * 100 / totalChars);
    } else {
        result->confidence = 0;
    }
    
    result->timeMs = (clock() - start) * 1000 / CLOCKS_PER_SEC;
    
    return result;
}

LEET_API LeetDecryptResult* leet_decrypt_words(LeetGenerator* generator, wchar_t** words, int wordCount) {
    if (!generator || !words || wordCount <= 0) return NULL;
    
    LeetEncryptedMessage msg;
    msg.words = words;
    msg.wordCount = wordCount;
    msg.originalLength = 0;
    msg.metadata = NULL;
    
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
    
    for (int i = 0; i < msg->wordCount; i++) {
        free(msg->words[i]);
    }
    free(msg->words);
    free(msg->metadata);
    free(msg);
}

LEET_API void leet_cache_word(LeetGenerator* generator, const char* word, const wchar_t* encrypted) {
    if (!generator || !word || !encrypted) return;
    
    if (!generator->wordCache) {
        generator->wordCache = (char**)safe_calloc(1000, sizeof(char*));
        generator->cacheLengths = (int*)safe_calloc(1000, sizeof(int));
        generator->cacheCount = 0;
    }
    
    if (generator->cacheCount < 1000) {
        generator->wordCache[generator->cacheCount] = safe_strdup(word);
        generator->cacheLengths[generator->cacheCount] = wcslen(encrypted);
        generator->cacheCount++;
    }
}

LEET_API wchar_t* leet_lookup_cache(LeetGenerator* generator, const char* word) {
    if (!generator || !generator->wordCache || !word) return NULL;
    
    for (int i = 0; i < generator->cacheCount; i++) {
        if (generator->wordCache[i] && strcmp(generator->wordCache[i], word) == 0) {
            return (wchar_t*)generator->wordCache[i];
        }
    }
    return NULL;
}

LEET_API void leet_clear_cache(LeetGenerator* generator) {
    if (!generator || !generator->wordCache) return;
    
    for (int i = 0; i < generator->cacheCount; i++) {
        free(generator->wordCache[i]);
    }
    free(generator->wordCache);
    free(generator->cacheLengths);
    generator->wordCache = NULL;
    generator->cacheLengths = NULL;
    generator->cacheCount = 0;
}

LEET_API void leet_print_hex(const char* data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02x", (unsigned char)data[i]);
    }
    printf("\n");
}

LEET_API char* leet_unicode_to_utf8(const wchar_t* unicode) {
    if (!unicode) return NULL;
    
    size_t len = wcslen(unicode);
    char* utf8 = (char*)safe_malloc(len * 4 + 1);
    wcstombs(utf8, unicode, len * 4);
    return utf8;
}

LEET_API void leet_print_stats(LeetGenerator* generator) {
    if (!generator) return;
    
    printf("Leet Generator Statistics:\n");
    printf("  Rules: %d\n", generator->ruleCount);
    printf("  Replacement chance: %d%%\n", generator->replacementChance);
    printf("  Case change chance: %d%%\n", generator->caseChangeChance);
    printf("  Use seed: %s\n", generator->useSeed ? "yes" : "no");
    if (generator->useSeed) {
        printf("  Seed: %u\n", generator->seed);
    }
    printf("  Cache size: %d KB\n", generator->cacheSize);
    printf("  Cached words: %d\n", generator->cacheCount);
}

LEET_API void leet_print_reverse_map(LeetGenerator* generator) {
    if (!generator || !generator->reverseMap) return;
    
    printf("Reverse Map содержимое:\n");
    for (int i = 0; i < 1024; i++) {
        LeetReverseMap* entry = generator->reverseMap[i];
        while (entry) {
            printf("  %ls -> %c (len=%d)\n", entry->pattern, entry->original, entry->patternLength);
            entry = entry->next;
        }
    }
}
