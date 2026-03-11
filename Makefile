CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC -std=c99
LDFLAGS = -shared
LIB_NAME = libleet
TARGET_LIB = $(LIB_NAME).so
TARGET_STATIC = $(LIB_NAME).a
TARGET_DEMO = leet_demo
SRC_DIR = .
INCLUDE_DIR = .
BUILD_DIR = build
LIB_SRC = leet_generator.c
DEMO_SRC = main.c
HEADER = leet_generator.h
LIB_OBJ = $(BUILD_DIR)/leet_generator.o
DEMO_OBJ = $(BUILD_DIR)/main.o
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m # No Color

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

.PHONY: all
all: $(TARGET_LIB) $(TARGET_STATIC) $(TARGET_DEMO)
	@echo "$(GREEN)Сборка завершена успешно!$(NC)"

$(TARGET_LIB): $(BUILD_DIR) $(LIB_OBJ)
	@echo "$(GREEN)Создание динамической библиотеки...$(NC)"
	$(CC) $(LDFLAGS) -o $@ $(LIB_OBJ)
	@echo "$(GREEN)Динамическая библиотека создана: $@$(NC)"

$(TARGET_STATIC): $(BUILD_DIR) $(LIB_OBJ)
	@echo "$(GREEN)Создание статической библиотеки...$(NC)"
	ar rcs $@ $(LIB_OBJ)
	@echo "$(GREEN)Статическая библиотека создана: $@$(NC)"

$(TARGET_DEMO): $(BUILD_DIR) $(DEMO_OBJ) $(TARGET_LIB)
	@echo "$(GREEN)Компиляция демонстрационной программы...$(NC)"
	$(CC) -o $@ $(DEMO_OBJ) -L. -l:$(TARGET_LIB)
	@echo "$(GREEN)Демо программа создана: $@$(NC)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@echo "$(GREEN)Компиляция $<...$(NC)"
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

static-demo: $(TARGET_STATIC) $(DEMO_OBJ)
	@echo "$(GREEN)Компиляция со статической библиотекой...$(NC)"
	$(CC) -o $(TARGET_DEMO)_static $(DEMO_OBJ) $(TARGET_STATIC)
	@echo "$(GREEN)Статическая демо программа создана: $(TARGET_DEMO)_static$(NC)"

.PHONY: install
install: $(TARGET_LIB) $(HEADER)
	@echo "$(GREEN)Установка библиотеки в систему...$(NC)"
	@sudo cp $(TARGET_LIB) /usr/local/lib/
	@sudo cp $(HEADER) /usr/local/include/
	@sudo ldconfig
	@echo "$(GREEN)Библиотека установлена в /usr/local/lib/ и /usr/local/include/$(NC)"

.PHONY: uninstall
uninstall:
	@echo "$(RED)Удаление библиотеки из системы...$(NC)"
	@sudo rm -f /usr/local/lib/$(TARGET_LIB)
	@sudo rm -f /usr/local/include/$(HEADER)
	@sudo ldconfig
	@echo "$(GREEN)Библиотека удалена$(NC)"

.PHONY: run
run: $(TARGET_DEMO)
	@echo "$(GREEN)Запуск демонстрационной программы...$(NC)"
	@LD_LIBRARY_PATH=. ./$(TARGET_DEMO)

.PHONY: run-static
run-static: static-demo
	@echo "$(GREEN)Запуск статической демо программы...$(NC)"
	@./$(TARGET_DEMO)_static

.PHONY: test
test: $(TARGET_DEMO)
	@echo "$(GREEN)Запуск тестов...$(NC)"
	@echo "test" | LD_LIBRARY_PATH=. ./$(TARGET_DEMO) > /dev/null && \
		echo "$(GREEN)Тест пройден$(NC)" || \
		echo "$(RED)Тест не пройден$(NC)"

.PHONY: clean
clean:
	@echo "$(RED)Очистка...$(NC)"
	@rm -rf $(BUILD_DIR) $(TARGET_LIB) $(TARGET_STATIC) $(TARGET_DEMO) $(TARGET_DEMO)_static *.txt
	@echo "$(GREEN)Очистка завершена$(NC)"

.PHONY: rebuild
rebuild: clean all

.PHONY: info
info:
	@echo "$(GREEN)Информация о проекте:$(NC)"
	@echo "  Компилятор:     $(CC)"
	@echo "  Флаги:          $(CFLAGS)"
	@echo "  Библиотека:     $(TARGET_LIB)"
	@echo "  Статическая:    $(TARGET_STATIC)"
	@echo "  Демо программа: $(TARGET_DEMO)"
	@echo "  Заголовок:      $(HEADER)"
	@echo ""
	@echo "  Доступные цели:"
	@echo "    make all        - полная сборка"
	@echo "    make run        - запуск демо"
	@echo "    make clean      - очистка"
	@echo "    make install    - установка"
	@echo "    make uninstall  - удаление"
	@echo "    make test       - тестирование"
	@echo "    make rebuild    - пересборка"

.PHONY: help
help:
	@echo "$(GREEN)Доступные команды:$(NC)"
	@echo "  make all        - собрать всё (библиотеки + демо)"
	@echo "  make lib        - собрать только библиотеки"
	@echo "  make demo       - собрать только демо программу"
	@echo "  make static     - собрать статическую библиотеку"
	@echo "  make run        - запустить демо (с динамической библиотекой)"
	@echo "  make run-static - запустить демо (со статической библиотекой)"
	@echo "  make clean      - очистить все сгенерированные файлы"
	@echo "  make install    - установить библиотеку в систему"
	@echo "  make uninstall  - удалить библиотеку из системы"
	@echo "  make test       - запустить тесты"
	@echo "  make rebuild    - пересобрать всё с нуля"
	@echo "  make info       - показать информацию о проекте"

.PHONY: lib
lib: $(TARGET_LIB) $(TARGET_STATIC)
	@echo "$(GREEN)Библиотеки созданы$(NC)"

.PHONY: demo
demo: $(TARGET_DEMO)
	@echo "$(GREEN)Демо программа создана$(NC)"

.PHONY: static
static: $(TARGET_STATIC)
	@echo "$(GREEN)Статическая библиотека создана$(NC)"

$(HEADER):
	@echo "$(RED)Ошибка: $(HEADER) не найден!$(NC)"
	@exit 1

$(LIB_SRC):
	@echo "$(RED)Ошибка: $(LIB_SRC) не найден!$(NC)"
	@exit 1

$(DEMO_SRC):
	@echo "$(RED)Ошибка: $(DEMO_SRC) не найден!$(NC)"
	@exit 1

$(LIB_OBJ): $(LIB_SRC) $(HEADER)
$(DEMO_OBJ): $(DEMO_SRC) $(HEADER)
