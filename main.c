#include "leet_generator.h"
#include <locale.h>
#include <time.h>

const char* DICTIONARY[] = {
    "apple", "banana", "cherry", "date", "elderberry",
    "fig", "grape", "honeydew", "kiwi", "lemon",
    "mango", "nectarine", "orange", "papaya", "quince",
    "raspberry", "strawberry", "tangerine", "ugli", "voavanga",
    "watermelon", "xigua", "yuzu", "zucchini"
};

int main(void) {
    setlocale(LC_ALL, "");
    srand(time(NULL));
    
    printf("========================================\n");
    printf("  Leet/L33t генератор\n");
    printf("  Словарь: %d слов\n", sizeof(DICTIONARY)/sizeof(DICTIONARY[0]));
    printf("========================================\n\n");
    
    LeetGenerator* gen = leet_create_generator();
    
    printf("Демонстрация слова \"strawberry\":\n");
    for (int i = 0; i < 5; i++) {
        char* leet = leet_generate(gen, "strawberry");
        printf("  %d. %s\n", i+1, leet);
        leet_free_result(leet);
    }
    printf("\n");
    
    printf("16 случайных слов из словаря:\n");
    for (int i = 0; i < 16; i++) {
        int idx = rand() % (sizeof(DICTIONARY)/sizeof(DICTIONARY[0]));
        char* leet = leet_generate(gen, DICTIONARY[idx]);
        printf("  %2d. %-12s -> %s\n", i+1, DICTIONARY[idx], leet);
        leet_free_result(leet);
    }
    printf("\n");
    
    printf("Генерация 32 слов (первые 10 показаны):\n");
    for (int i = 0; i < 32; i++) {
        int idx = rand() % (sizeof(DICTIONARY)/sizeof(DICTIONARY[0]));
        char* leet = leet_generate(gen, DICTIONARY[idx]);
        if (i < 10) printf("  %2d. %-12s -> %s\n", i+1, DICTIONARY[idx], leet);
        leet_free_result(leet);
    }
    printf("  ... и еще 22 слова сгенерировано\n\n");
    
    printf("Интерактивный режим (exit для выхода):\n");
    char input[256];
    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "exit") == 0) break;
        if (strlen(input) == 0) continue;
        
        char* leet = leet_generate(gen, input);
        printf("  %s\n", leet);
        leet_free_result(leet);
    }
    
    leet_destroy_generator(gen);
    printf("\nДемонстрация завершена.\n");
    return 0;
}
