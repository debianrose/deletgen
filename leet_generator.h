#ifndef LEET_GENERATOR_H
#define LEET_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
    #ifdef LEET_EXPORTS
        #define LEET_API __declspec(dllexport)
    #else
        #define LEET_API __declspec(dllimport)
    #endif
#else
    #define LEET_API
#endif

typedef struct LeetRule {
    char original;
    char** replacements;
    int count;
    int maxReplacementLength;
} LeetRule;

typedef struct LeetGenerator {
    LeetRule* rules;
    int ruleCount;
    int useMultiChar;  // флаг для использования многобуквенных замен
    int preserveCase;  // сохранять ли оригинальный регистр
} LeetGenerator;

LEET_API LeetGenerator* leet_create_generator(void);
LEET_API void leet_destroy_generator(LeetGenerator* generator);
LEET_API void leet_set_use_multichar(LeetGenerator* generator, int use);
LEET_API void leet_set_preserve_case(LeetGenerator* generator, int preserve);
LEET_API char* leet_generate(LeetGenerator* generator, const char* word);
LEET_API char** leet_generate_multiple(LeetGenerator* generator, const char* word, int count);
LEET_API void leet_free_result(char* result);
LEET_API void leet_free_multiple_results(char** results, int count);
LEET_API int leet_load_rules(LeetGenerator* generator, const char* filename);

#endif // LEET_GENERATOR_H
