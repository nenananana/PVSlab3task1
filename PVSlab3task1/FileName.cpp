#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define NUM_RUNS 100  // ���������� ��������

int main() {
    setlocale(LC_ALL, "Russian");

    // ���� ���������� ��������� � ����������
    size_t SIZE;
    printf("������� ���������� ��������� �������: ");
    scanf("%zu", &SIZE);

    // �������� �� ������������ �����
    if (SIZE <= 0) {
        printf("������: ���������� ��������� ������ ���� �������������!\n");
        return 1;
    }

    // ���������� ��� ���������� ���������� �������
    double total_fill_time = 0.0;
    double total_calc_time = 0.0;
    double total_total_time = 0.0;

    for (int run = 0; run < NUM_RUNS; run++) {
        clock_t total_start = clock();

        clock_t fill_start = clock();
        int* array = (int*)malloc(SIZE * sizeof(int));
        if (array == NULL) {
            printf("������ ��������� ������!\n");
            return 1;
        }

        // ������������� ���������� ��������� �����
        srand(time(NULL) + run);  // +run ��� ������� seed � ������ �������
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

        // ����� ������ ��� ������� ������� 
        printf("\033[1m������ %d\033[0m\n", run + 1);
        printf("����� ���������: %lld\n", sum);
        printf("����������: %.6f ���\n", fill_time);
        printf("����������: %.6f ���\n", calc_time);
        printf("����� �����: %.6f ���\n\n", total_time);
    }

    // ����� ������� ��������
    printf("\033[1m=== �������� ������� �������� (�� %d ��������) ===\033[0m\n", NUM_RUNS);
    printf("������� ����� ����������: %.6f ���\n", total_fill_time / NUM_RUNS);
    printf("������� ����� ����������: %.6f ���\n", total_calc_time / NUM_RUNS);
    printf("������� ����� �����: %.6f ���\n", total_total_time / NUM_RUNS);

    return 0;
}