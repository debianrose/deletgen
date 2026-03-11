#include "leet_generator.h"

static void leet_init_rng(void) {
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
}

static char* leet_strdup(const char* s) {
    size_t len = strlen(s) + 1;
    char* new_str = (char*)malloc(len);
    if (new_str) memcpy(new_str, s, len);
    return new_str;
}

static LeetRule* create_extended_rules(int* count) {
    leet_init_rng();
    
    *count = 26; // A-Z
    LeetRule* rules = (LeetRule*)calloc(*count, sizeof(LeetRule));
    
    // A/a
    rules[0].original = 'a';
    rules[0].replacements = (char**)malloc(12 * sizeof(char*));
    rules[0].replacements[0] = leet_strdup("@");
    rules[0].replacements[1] = leet_strdup("4");
    rules[0].replacements[2] = leet_strdup("/\\");
    rules[0].replacements[3] = leet_strdup("/-\\");
    rules[0].replacements[4] = leet_strdup("Д");
    rules[0].replacements[5] = leet_strdup("α");
    rules[0].replacements[6] = leet_strdup("λ");
    rules[0].replacements[7] = leet_strdup("а");
    rules[0].replacements[8] = leet_strdup("∀");
    rules[0].replacements[9] = leet_strdup("Δ");
    rules[0].replacements[10] = leet_strdup("ª");
    rules[0].replacements[11] = leet_strdup("Ä");
    rules[0].count = 12;
    rules[0].maxReplacementLength = 3;
    
    // B/b
    rules[1].original = 'b';
    rules[1].replacements = (char**)malloc(10 * sizeof(char*));
    rules[1].replacements[0] = leet_strdup("8");
    rules[1].replacements[1] = leet_strdup("|3");
    rules[1].replacements[2] = leet_strdup("ß");
    rules[1].replacements[3] = leet_strdup("13");
    rules[1].replacements[4] = leet_strdup("|o");
    rules[1].replacements[5] = leet_strdup("!3");
    rules[1].replacements[6] = leet_strdup("(3");
    rules[1].replacements[7] = leet_strdup("฿");
    rules[1].replacements[8] = leet_strdup("в");
    rules[1].replacements[9] = leet_strdup("β");
    rules[1].count = 10;
    rules[1].maxReplacementLength = 2;
    
    // C/c
    rules[2].original = 'c';
    rules[2].replacements = (char**)malloc(9 * sizeof(char*));
    rules[2].replacements[0] = leet_strdup("(");
    rules[2].replacements[1] = leet_strdup("<");
    rules[2].replacements[2] = leet_strdup("{");
    rules[2].replacements[3] = leet_strdup("©");
    rules[2].replacements[4] = leet_strdup("¢");
    rules[2].replacements[5] = leet_strdup("с");
    rules[2].replacements[6] = leet_strdup("ς");
    rules[2].replacements[7] = leet_strdup("☾");
    rules[2].replacements[8] = leet_strdup("🌑");
    rules[2].count = 9;
    rules[2].maxReplacementLength = 2;
    
    // D/d
    rules[3].original = 'd';
    rules[3].replacements = (char**)malloc(8 * sizeof(char*));
    rules[3].replacements[0] = leet_strdup("|)");
    rules[3].replacements[1] = leet_strdup("đ");
    rules[3].replacements[2] = leet_strdup("ď");
    rules[3].replacements[3] = leet_strdup("cl");
    rules[3].replacements[4] = leet_strdup("Ð");
    rules[3].replacements[5] = leet_strdup("∂");
    rules[3].replacements[6] = leet_strdup("♫");
    rules[3].replacements[7] = leet_strdup("╫");
    rules[3].count = 8;
    rules[3].maxReplacementLength = 2;
    
    // E/e
    rules[4].original = 'e';
    rules[4].replacements = (char**)malloc(12 * sizeof(char*));
    rules[4].replacements[0] = leet_strdup("3");
    rules[4].replacements[1] = leet_strdup("€");
    rules[4].replacements[2] = leet_strdup("&");
    rules[4].replacements[3] = leet_strdup("£");
    rules[4].replacements[4] = leet_strdup("ë");
    rules[4].replacements[5] = leet_strdup("е");
    rules[4].replacements[6] = leet_strdup("Ē");
    rules[4].replacements[7] = leet_strdup("Ɛ");
    rules[4].replacements[8] = leet_strdup("∈");
    rules[4].replacements[9] = leet_strdup("€");
    rules[4].replacements[10] = leet_strdup("ⴹ");
    rules[4].replacements[11] = leet_strdup("⋲");
    rules[4].count = 12;
    rules[4].maxReplacementLength = 2;
    
    // F/f
    rules[5].original = 'f';
    rules[5].replacements = (char**)malloc(7 * sizeof(char*));
    rules[5].replacements[0] = leet_strdup("|=");
    rules[5].replacements[1] = leet_strdup("ƒ");
    rules[5].replacements[2] = leet_strdup("ph");
    rules[5].replacements[3] = leet_strdup("(=)》");
    rules[5].replacements[4] = leet_strdup("₣");
    rules[5].replacements[5] = leet_strdup("♭");
    rules[5].replacements[6] = leet_strdup("⨍");
    rules[5].count = 7;
    rules[5].maxReplacementLength = 3;
    
    // G/g
    rules[6].original = 'g';
    rules[6].replacements = (char**)malloc(7 * sizeof(char*));
    rules[6].replacements[0] = leet_strdup("9");
    rules[6].replacements[1] = leet_strdup("6");
    rules[6].replacements[2] = leet_strdup("&");
    rules[6].replacements[3] = leet_strdup("g");
    rules[6].replacements[4] = leet_strdup("ğ");
    rules[6].replacements[5] = leet_strdup("ɢ");
    rules[6].replacements[6] = leet_strdup("❡");
    rules[6].count = 7;
    rules[6].maxReplacementLength = 1;
    
    // H/h
    rules[7].original = 'h';
    rules[7].replacements = (char**)malloc(8 * sizeof(char*));
    rules[7].replacements[0] = leet_strdup("#");
    rules[7].replacements[1] = leet_strdup("|-|");
    rules[7].replacements[2] = leet_strdup("]-[");
    rules[7].replacements[3] = leet_strdup("}-{");
    rules[7].replacements[4] = leet_strdup("н");
    rules[7].replacements[5] = leet_strdup("ħ");
    rules[7].replacements[6] = leet_strdup("ℍ");
    rules[7].replacements[7] = leet_strdup("♄");
    rules[7].count = 8;
    rules[7].maxReplacementLength = 3;
    
    // I/i
    rules[8].original = 'i';
    rules[8].replacements = (char**)malloc(10 * sizeof(char*));
    rules[8].replacements[0] = leet_strdup("1");
    rules[8].replacements[1] = leet_strdup("!");
    rules[8].replacements[2] = leet_strdup("|");
    rules[8].replacements[3] = leet_strdup("][");
    rules[8].replacements[4] = leet_strdup("ï");
    rules[8].replacements[5] = leet_strdup("і");
    rules[8].replacements[6] = leet_strdup("ɪ");
    rules[8].replacements[7] = leet_strdup("‼");
    rules[8].replacements[8] = leet_strdup("⁑");
    rules[8].replacements[9] = leet_strdup("⚡");
    rules[8].count = 10;
    rules[8].maxReplacementLength = 2;
    
    // J/j
    rules[9].original = 'j';
    rules[9].replacements = (char**)malloc(6 * sizeof(char*));
    rules[9].replacements[0] = leet_strdup("_|");
    rules[9].replacements[1] = leet_strdup("]");
    rules[9].replacements[2] = leet_strdup("ј");
    rules[9].replacements[3] = leet_strdup("ʝ");
    rules[9].replacements[4] = leet_strdup("⌡");
    rules[9].replacements[5] = leet_strdup("ʲ");
    rules[9].count = 6;
    rules[9].maxReplacementLength = 2;
    
    // K/k
    rules[10].original = 'k';
    rules[10].replacements = (char**)malloc(7 * sizeof(char*));
    rules[10].replacements[0] = leet_strdup("|<");
    rules[10].replacements[1] = leet_strdup("|(");
    rules[10].replacements[2] = leet_strdup("ķ");
    rules[10].replacements[3] = leet_strdup("κ");
    rules[10].replacements[4] = leet_strdup("ќ");
    rules[10].replacements[5] = leet_strdup("ƙ");
    rules[10].replacements[6] = leet_strdup("𝕜");
    rules[10].count = 7;
    rules[10].maxReplacementLength = 2;
    
    // L/l
    rules[11].original = 'l';
    rules[11].replacements = (char**)malloc(9 * sizeof(char*));
    rules[11].replacements[0] = leet_strdup("1");
    rules[11].replacements[1] = leet_strdup("|");
    rules[11].replacements[2] = leet_strdup("£");
    rules[11].replacements[3] = leet_strdup("|_");
    rules[11].replacements[4] = leet_strdup("ł");
    rules[11].replacements[5] = leet_strdup("ļ");
    rules[11].replacements[6] = leet_strdup("ℓ");
    rules[11].replacements[7] = leet_strdup("└");
    rules[11].replacements[8] = leet_strdup("Ⳑ");
    rules[11].count = 9;
    rules[11].maxReplacementLength = 2;
    
    // M/m
    rules[12].original = 'm';
    rules[12].replacements = (char**)malloc(9 * sizeof(char*));
    rules[12].replacements[0] = leet_strdup("|V|");
    rules[12].replacements[1] = leet_strdup("IVI");
    rules[12].replacements[2] = leet_strdup("|\\/|");
    rules[12].replacements[3] = leet_strdup("м");
    rules[12].replacements[4] = leet_strdup("Ⓜ");
    rules[12].replacements[5] = leet_strdup("♏");
    rules[12].replacements[6] = leet_strdup("ɱ");
    rules[12].replacements[7] = leet_strdup("ᵯ");
    rules[12].replacements[8] = leet_strdup("𐌑");
    rules[12].count = 9;
    rules[12].maxReplacementLength = 4;
    
    // N/n
    rules[13].original = 'n';
    rules[13].replacements = (char**)malloc(8 * sizeof(char*));
    rules[13].replacements[0] = leet_strdup("|\\|");
    rules[13].replacements[1] = leet_strdup("/\\/");
    rules[13].replacements[2] = leet_strdup("п");
    rules[13].replacements[3] = leet_strdup("ñ");
    rules[13].replacements[4] = leet_strdup("ń");
    rules[13].replacements[5] = leet_strdup("η");
    rules[13].replacements[6] = leet_strdup("ℕ");
    rules[13].replacements[7] = leet_strdup("∩");
    rules[13].count = 8;
    rules[13].maxReplacementLength = 3;
    
    // O/o
    rules[14].original = 'o';
    rules[14].replacements = (char**)malloc(12 * sizeof(char*));
    rules[14].replacements[0] = leet_strdup("0");
    rules[14].replacements[1] = leet_strdup("()");
    rules[14].replacements[2] = leet_strdup("[]");
    rules[14].replacements[3] = leet_strdup("<>");
    rules[14].replacements[4] = leet_strdup("Ø");
    rules[14].replacements[5] = leet_strdup("ⵁ");
    rules[14].replacements[6] = leet_strdup("⊕");
    rules[14].replacements[7] = leet_strdup("◯");
    rules[14].replacements[8] = leet_strdup("ⴱ");
    rules[14].replacements[9] = leet_strdup("ø");
    rules[14].replacements[10] = leet_strdup("ö");
    rules[14].replacements[11] = leet_strdup("œ");
    rules[14].count = 12;
    rules[14].maxReplacementLength = 2;
    
    // P/p
    rules[15].original = 'p';
    rules[15].replacements = (char**)malloc(8 * sizeof(char*));
    rules[15].replacements[0] = leet_strdup("|*");
    rules[15].replacements[1] = leet_strdup("|o");
    rules[15].replacements[2] = leet_strdup("|>");
    rules[15].replacements[3] = leet_strdup("|7");
    rules[15].replacements[4] = leet_strdup("р");
    rules[15].replacements[5] = leet_strdup("þ");
    rules[15].replacements[6] = leet_strdup("¶");
    rules[15].replacements[7] = leet_strdup("♇");
    rules[15].count = 8;
    rules[15].maxReplacementLength = 2;
    
    // Q/q
    rules[16].original = 'q';
    rules[16].replacements = (char**)malloc(6 * sizeof(char*));
    rules[16].replacements[0] = leet_strdup("(,)");
    rules[16].replacements[1] = leet_strdup("0,");
    rules[16].replacements[2] = leet_strdup("9");
    rules[16].replacements[3] = leet_strdup("ҩ");
    rules[16].replacements[4] = leet_strdup("ʠ");
    rules[16].replacements[5] = leet_strdup("ⵕ");
    rules[16].count = 6;
    rules[16].maxReplacementLength = 3;
    
    // R/r
    rules[17].original = 'r';
    rules[17].replacements = (char**)malloc(9 * sizeof(char*));
    rules[17].replacements[0] = leet_strdup("|2");
    rules[17].replacements[1] = leet_strdup("|?");
    rules[17].replacements[2] = leet_strdup("|^");
    rules[17].replacements[3] = leet_strdup("®");
    rules[17].replacements[4] = leet_strdup("ř");
    rules[17].replacements[5] = leet_strdup("я");
    rules[17].replacements[6] = leet_strdup("ʁ");
    rules[17].replacements[7] = leet_strdup("ᴚ");
    rules[17].replacements[8] = leet_strdup("ℝ");
    rules[17].count = 9;
    rules[17].maxReplacementLength = 2;
    
    // S/s
    rules[18].original = 's';
    rules[18].replacements = (char**)malloc(11 * sizeof(char*));
    rules[18].replacements[0] = leet_strdup("$");
    rules[18].replacements[1] = leet_strdup("5");
    rules[18].replacements[2] = leet_strdup("z");
    rules[18].replacements[3] = leet_strdup("§");
    rules[18].replacements[4] = leet_strdup("ş");
    rules[18].replacements[5] = leet_strdup("ś");
    rules[18].replacements[6] = leet_strdup("ѕ");
    rules[18].replacements[7] = leet_strdup("ʂ");
    rules[18].replacements[8] = leet_strdup("⚡");
    rules[18].replacements[9] = leet_strdup("𐑈");
    rules[18].replacements[10] = leet_strdup("🌠");
    rules[18].count = 11;
    rules[18].maxReplacementLength = 2;
    
    // T/t
    rules[19].original = 't';
    rules[19].replacements = (char**)malloc(10 * sizeof(char*));
    rules[19].replacements[0] = leet_strdup("7");
    rules[19].replacements[1] = leet_strdup("+");
    rules[19].replacements[2] = leet_strdup("†");
    rules[19].replacements[3] = leet_strdup("¥");
    rules[19].replacements[4] = leet_strdup("т");
    rules[19].replacements[5] = leet_strdup("ŧ");
    rules[19].replacements[6] = leet_strdup("⊥");
    rules[19].replacements[7] = leet_strdup("┳");
    rules[19].replacements[8] = leet_strdup("╦");
    rules[19].replacements[9] = leet_strdup("⫟");
    rules[19].count = 10;
    rules[19].maxReplacementLength = 2;
    
    // U/u
    rules[20].original = 'u';
    rules[20].replacements = (char**)malloc(8 * sizeof(char*));
    rules[20].replacements[0] = leet_strdup("|_|");
    rules[20].replacements[1] = leet_strdup("µ");
    rules[20].replacements[2] = leet_strdup("ü");
    rules[20].replacements[3] = leet_strdup("υ");
    rules[20].replacements[4] = leet_strdup("ц");
    rules[20].replacements[5] = leet_strdup("∩");
    rules[20].replacements[6] = leet_strdup("∪");
    rules[20].replacements[7] = leet_strdup("⋃");
    rules[20].count = 8;
    rules[20].maxReplacementLength = 3;
    
    // V/v
    rules[21].original = 'v';
    rules[21].replacements = (char**)malloc(7 * sizeof(char*));
    rules[21].replacements[0] = leet_strdup("\\/");
    rules[21].replacements[1] = leet_strdup("|/");
    rules[21].replacements[2] = leet_strdup("√");
    rules[21].replacements[3] = leet_strdup("ν");
    rules[21].replacements[4] = leet_strdup("ѵ");
    rules[21].replacements[5] = leet_strdup("▼");
    rules[21].replacements[6] = leet_strdup("♢");
    rules[21].count = 7;
    rules[21].maxReplacementLength = 2;
    
    // W/w
    rules[22].original = 'w';
    rules[22].replacements = (char**)malloc(9 * sizeof(char*));
    rules[22].replacements[0] = leet_strdup("\\/\\/");
    rules[22].replacements[1] = leet_strdup("VV");
    rules[22].replacements[2] = leet_strdup("ω");
    rules[22].replacements[3] = leet_strdup("ш");
    rules[22].replacements[4] = leet_strdup("ฬ");
    rules[22].replacements[5] = leet_strdup("ʍ");
    rules[22].replacements[6] = leet_strdup("ẁ");
    rules[22].replacements[7] = leet_strdup("⚡");
    rules[22].replacements[8] = leet_strdup("𐐎");
    rules[22].count = 9;
    rules[22].maxReplacementLength = 4;
    
    // X/x
    rules[23].original = 'x';
    rules[23].replacements = (char**)malloc(7 * sizeof(char*));
    rules[23].replacements[0] = leet_strdup("><");
    rules[23].replacements[1] = leet_strdup("×");
    rules[23].replacements[2] = leet_strdup("Ж");
    rules[23].replacements[3] = leet_strdup("χ");
    rules[23].replacements[4] = leet_strdup("✕");
    rules[23].replacements[5] = leet_strdup("✖");
    rules[23].replacements[6] = leet_strdup("☓");
    rules[23].count = 7;
    rules[23].maxReplacementLength = 2;
    
    // Y/y
    rules[24].original = 'y';
    rules[24].replacements = (char**)malloc(7 * sizeof(char*));
    rules[24].replacements[0] = leet_strdup("¥");
    rules[24].replacements[1] = leet_strdup("ÿ");
    rules[24].replacements[2] = leet_strdup("γ");
    rules[24].replacements[3] = leet_strdup("у");
    rules[24].replacements[4] = leet_strdup("ɏ");
    rules[24].replacements[5] = leet_strdup("ψ");
    rules[24].replacements[6] = leet_strdup("♇");
    rules[24].count = 7;
    rules[24].maxReplacementLength = 2;
    
    // Z/z
    rules[25].original = 'z';
    rules[25].replacements = (char**)malloc(7 * sizeof(char*));
    rules[25].replacements[0] = leet_strdup("2");
    rules[25].replacements[1] = leet_strdup("~/_");
    rules[25].replacements[2] = leet_strdup("ζ");
    rules[25].replacements[3] = leet_strdup("з");
    rules[25].replacements[4] = leet_strdup("ź");
    rules[25].replacements[5] = leet_strdup("ℤ");
    rules[25].replacements[6] = leet_strdup("⚡");
    rules[25].count = 7;
    rules[25].maxReplacementLength = 3;
    
    return rules;
}

LEET_API LeetGenerator* leet_create_generator(void) {
    LeetGenerator* gen = (LeetGenerator*)calloc(1, sizeof(LeetGenerator));
    if (!gen) return NULL;
    
    gen->rules = create_extended_rules(&gen->ruleCount);
    gen->useMultiChar = 1;      // по умолчанию используем многобуквенные замены
    gen->preserveCase = 0;      // по умолчанию не сохраняем регистр
    
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
    free(generator);
}

LEET_API void leet_set_use_multichar(LeetGenerator* generator, int use) {
    if (generator) generator->useMultiChar = use;
}

LEET_API void leet_set_preserve_case(LeetGenerator* generator, int preserve) {
    if (generator) generator->preserveCase = preserve;
}

static LeetRule* find_rule(LeetGenerator* generator, char c) {
    if (!generator || !generator->rules) return NULL;
    
    c = tolower(c);
    for (int i = 0; i < generator->ruleCount; i++) {
        if (generator->rules[i].original == c) {
            return &generator->rules[i];
        }
    }
    return NULL;
}

LEET_API char* leet_generate(LeetGenerator* generator, const char* word) {
    if (!generator || !word) return NULL;
    
    int len = strlen(word);
    
    int bufferSize = len + 1;
    for (int i = 0; i < len; i++) {
        LeetRule* rule = find_rule(generator, word[i]);
        if (rule && generator->useMultiChar) {
            bufferSize += rule->maxReplacementLength - 1;
        }
    }
    
    char* result = (char*)malloc(bufferSize);
    if (!result) return NULL;
    
    int resultIndex = 0;
    
    for (int i = 0; i < len; i++) {
        char currentChar = word[i];
        LeetRule* rule = find_rule(generator, currentChar);
        
        if (rule && (rand() % 2)) { // 50% шанс замены
            int repIndex = rand() % rule->count;
            char* replacement = rule->replacements[repIndex];
            int repLen = strlen(replacement);
            
            for (int j = 0; j < repLen; j++) {
                result[resultIndex++] = replacement[j];
            }
        } else {
            if (generator->preserveCase) {
                result[resultIndex++] = currentChar;
            } else {
                result[resultIndex++] = (rand() % 2) ? toupper(currentChar) : tolower(currentChar);
            }
        }
    }
    
    result[resultIndex] = '\0';
    return result;
}

LEET_API char** leet_generate_multiple(LeetGenerator* generator, const char* word, int count) {
    if (!generator || !word || count <= 0) return NULL;
    
    char** results = (char**)malloc(sizeof(char*) * count);
    if (!results) return NULL;
    
    for (int i = 0; i < count; i++) {
        results[i] = leet_generate(generator, word);
    }
    
    return results;
}

LEET_API void leet_free_result(char* result) {
    free(result);
}

LEET_API void leet_free_multiple_results(char** results, int count) {
    if (!results) return;
    for (int i = 0; i < count; i++) {
        free(results[i]);
    }
    free(results);
}
