#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define NUM_RUNS 100  // Количество запусков

int main() {
    setlocale(LC_ALL, "Russian");

    // Ввод количества элементов с клавиатуры
    size_t SIZE;
    printf("Введите количество элементов массива: ");
    scanf("%zu", &SIZE);

    // Проверка на корректность ввода
    if (SIZE <= 0) {
        printf("Ошибка: количество элементов должно быть положительным!\n");
        return 1;
    }

    // Переменные для накопления суммарного времени
    double total_fill_time = 0.0;
    double total_calc_time = 0.0;
    double total_total_time = 0.0;

    for (int run = 0; run < NUM_RUNS; run++) {
        clock_t total_start = clock();

        clock_t fill_start = clock();
        int* array = (int*)malloc(SIZE * sizeof(int));
        if (array == NULL) {
            printf("Ошибка выделения памяти!\n");
            return 1;
        }

        // Инициализация генератора случайных чисел
        srand(time(NULL) + run);  // +run для разного seed в каждом запуске
        for (size_t i = 0; i < SIZE; i++) {
            array[i] = rand() % 100;
        }
        clock_t fill_end = clock();

        clock_t calc_start = clock();
        long long sum = 0;
        for (size_t i = 0; i < SIZE; i++) {
            sum += array[i];
        }
        clock_t calc_end = clock();

        clock_t total_end = clock();

        double fill_time = (double)(fill_end - fill_start) / CLOCKS_PER_SEC;
        double calc_time = (double)(calc_end - calc_start) / CLOCKS_PER_SEC;
        double total_time = (double)(total_end - total_start) / CLOCKS_PER_SEC;

        total_fill_time += fill_time;
        total_calc_time += calc_time;
        total_total_time += total_time;

        free(array);

        // Вывод данных для каждого запуска 
        printf("\033[1mЗапуск %d\033[0m\n", run + 1);
        printf("Сумма элементов: %lld\n", sum);
        printf("Заполнение: %.6f сек\n", fill_time);
        printf("Вычисления: %.6f сек\n", calc_time);
        printf("Общее время: %.6f сек\n\n", total_time);
    }

    // Вывод средних значений
    printf("\033[1m=== ИТОГОВЫЕ СРЕДНИЕ ЗНАЧЕНИЯ (из %d запусков) ===\033[0m\n", NUM_RUNS);
    printf("Среднее время заполнения: %.6f сек\n", total_fill_time / NUM_RUNS);
    printf("Среднее время вычислений: %.6f сек\n", total_calc_time / NUM_RUNS);
    printf("Среднее общее время: %.6f сек\n", total_total_time / NUM_RUNS);

    return 0;
}