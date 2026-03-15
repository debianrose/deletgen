#ifndef LEET_GENERATOR_H
#define LEET_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <stdint.h>

#define LEET_API

typedef enum {
    LEET_OK           = 0,
    LEET_ERR_MEMORY   = 1,
    LEET_ERR_NULL_PTR = 2,
    LEET_ERR_ENCODING = 3
} LeetErrorCode;

typedef struct LeetRule {
    char  original;
    char** replacements;
    int   count;
    int   maxReplacementLength;
} LeetRule;

typedef struct LeetReverseMap {
    wchar_t* pattern;
    char     original;
    int      patternLength;
    struct LeetReverseMap* next;
} LeetReverseMap;

typedef struct LeetGenerator {
    LeetRule*      rules;
    int            ruleCount;
    LeetReverseMap** reverseMap;
    int            useMultiChar;
    int            preserveCase;
    int            cacheSize;
    char**         wordCache;
    int*           cacheLengths;
    int            cacheCount;
    int            replacementChance;
    int            caseChangeChance;
    int            useSeed;
    unsigned int   seed;
    unsigned int   rng_state;
} LeetGenerator;

typedef struct LeetDecryptResult {
    char* text;
    int   confidence;
    int   timeMs;
    int   unknownWords;
} LeetDecryptResult;

typedef struct LeetEncryptedMessage {
    wchar_t** words;
    int       wordCount;
    int       originalLength;
    char*     metadata;
} LeetEncryptedMessage;

LEET_API LeetGenerator* leet_create_generator(void);
LEET_API void           leet_destroy_generator(LeetGenerator* generator);
LEET_API void           leet_set_replacement_chance(LeetGenerator* generator, int chance);
LEET_API void           leet_set_case_chance(LeetGenerator* generator, int chance);
LEET_API void           leet_set_seed(LeetGenerator* generator, unsigned int seed);
LEET_API void           leet_randomize_seed(LeetGenerator* generator);
LEET_API void           leet_set_use_multichar(LeetGenerator* generator, int use);
LEET_API void           leet_set_preserve_case(LeetGenerator* generator, int preserve);
LEET_API void           leet_set_cache_size(LeetGenerator* generator, int maxKB);

LEET_API wchar_t*              leet_encrypt_word(LeetGenerator* generator, const char* word);
LEET_API LeetEncryptedMessage* leet_encrypt_message(LeetGenerator* generator, const char* message);
LEET_API void                  leet_free_encrypted_message(LeetEncryptedMessage* msg);

LEET_API char*             leet_decrypt_word(LeetGenerator* generator, const wchar_t* leetWord);
LEET_API LeetDecryptResult* leet_decrypt_message(LeetGenerator* generator, LeetEncryptedMessage* msg);
LEET_API LeetDecryptResult* leet_decrypt_words(LeetGenerator* generator, wchar_t** words, int wordCount);
LEET_API void              leet_free_decrypt_result(LeetDecryptResult* result);

LEET_API void        leet_cache_word(LeetGenerator* generator, const char* word, const wchar_t* encrypted);
LEET_API const char* leet_lookup_cache(LeetGenerator* generator, const char* word);
LEET_API void        leet_clear_cache(LeetGenerator* generator);

LEET_API char* leet_unicode_to_utf8(const wchar_t* unicode);
LEET_API void  leet_print_hex(const char* data, int length);
LEET_API void  leet_print_stats(LeetGenerator* generator);
LEET_API void  leet_print_reverse_map(LeetGenerator* generator);

LEET_API LeetErrorCode leet_get_last_error(void);
LEET_API const char*   leet_get_last_error_msg(void);
LEET_API void          leet_clear_error(void);

#endif
