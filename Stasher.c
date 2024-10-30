#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void hide (const char *filename) {
    char hided_name[256];
    snprintf(hided_name, sizeof(hided_name), "%s.hidden", filename);

    // Переименование файла
    if (rename(filename, hided_name) == -1) {
        printf("Не удалось исказить файл");
        exit;
    }
}

void recovery (const char *filename) {
    const char *suffix = ".hidden";
    size_t filename_len = strlen(filename);
    size_t suffix_len = strlen(suffix);

    if (filename_len > suffix_len && strcmp(filename + filename_len - suffix_len, suffix) == 0) {
        char recovered_name[256];
        snprintf(recovered_name, sizeof(recovered_name), "%.*s", (int)(filename_len - suffix_len), filename);

        if (rename(filename, recovered_name) == -1) {
            printf("Не удалось восстановить файл");
            exit;
        }
    } else {
        printf("Окончание имени файла не содержит '.hidden' - восстановление невозможно");
        exit;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Неверные данные на входе", argv[0]);
        exit;
    }

    // Выбор действия на основе первого аргумента
    if (strcmp(argv[1], "hide") == 0) {
        hide(argv[2]);
    } else if (strcmp(argv[1], "recover") == 0) {
        recovery(argv[2]);
    } else {
        printf("Неизвестнй режим");
        exit;
    }

    return 0;
}
