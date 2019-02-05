#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

/*
 * Краснов Василий
 * БПИ173_2
 */

// метод для поиска максимального элемента в массиве
int findMax(int *numbers, int array_size)
{
    int max = numbers[0];
    for (int i = 0; i < array_size; ++i)
        if (numbers[i] > max)
            max = numbers[i];
    return max;
}


// Функция сортировки подсчетом
void countingSort(int *numbers, int array_size, int digit)
{
    if (array_size == 0) return;
    // массив из 256 элементов, рассматриваем байты
    int base=256;
    int *C = new int[base];
    int *B = new int[array_size];
    for (int i = 0; i < base; ++i)
    {
        C[i] = 0;
    }
    // считаем количество чисел
    for (int i = 0; i < array_size; ++i)
    {
        // берем по модулю нашего основания(в данном случае 256)
        C[(numbers[i] / digit) % base]++;
    }
    // частичные суммы
    for (int i = 1; i < base; ++i)
    {
        C[i] = C[i] + C[i - 1];
    }
    // сортированный массив в B
    // смотрим повторения для устойчивости
    for (int i = array_size - 1; i >= 0; --i)
    {
        B[C[(numbers[i] / digit) % base] - 1] = numbers[i];
        C[(numbers[i] / digit) % base]--;
    }
    // кладем все в наш массив
    for (int i = 0; i < array_size; ++i)
    {
        numbers[i] = B[i];
    }
    delete[] B;
    delete[] C;
}
// Функция цифровой сортировки
void radixSort(int *numbers, int array_size)
{
    int digit, k;
    k = findMax(numbers, array_size);

    // digit определяет по какой СС мы отделяем числа
    for (digit = 1; k/digit > 0; digit *= 256)
        countingSort(numbers, array_size, digit);
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    radixSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}