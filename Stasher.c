#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Скрытие
void hide (const char *filename) { // Получаем имя файла
    char hided_name[256];
    snprintf(hided_name, sizeof(hided_name), "%s.hidden", filename); // Собираем новое имя

    if (rename(filename, hided_name) == -1) { // Переименовываем файл и проверяем
        printf("Не удалось исказить файл");
        exit;
    }
}

// Восстановление
void recovery (const char *filename) { // Получаем имя файла
    const char *suffix = ".hidden";
    size_t filename_len = strlen(filename);
    size_t suffix_len = strlen(suffix);

    if (filename_len > suffix_len && strcmp(filename + filename_len - suffix_len, suffix) == 0) { // Проверяем, если ли у имени файла окончание .hidden
        char recovered_name[256];
        snprintf(recovered_name, sizeof(recovered_name), "%.*s", (int)(filename_len - suffix_len), filename); // Пытаемся переименовать обратно, исходя из того, что у имени файла окончание .hidden

        if (rename(filename, recovered_name) == -1) { // Переименовываем файл и проверяем
            printf("Не удалось восстановить файл");
            exit;
        }
    } else {
        printf("Окончание имени файла не содержит '.hidden' - восстановление невозможно"); // ыводим ошибку, если имя файла не содержит .hidden
        exit;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) { 
        printf("Неверные данные на входе", argv[0]); // Проверяем данные на входе (ожидаем режим и имя файла)
        exit;
    }

    if (strcmp(argv[1], "hide") == 0) { // Проверяем режим, вызываем нужную функцию
        hide(argv[2]);
    } else if (strcmp(argv[1], "recover") == 0) {
        recovery(argv[2]);
    } else {
        printf("Неизвестнй режим"); // Для некорректных входных данных
        exit;
    }

    return 0;
}
