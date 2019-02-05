#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

void qSort(int *numbers, int left, int right)
{
    // наш разделитель
    // в данном случае случайный опорный элемент
    int pivot = numbers[rand() % (right - left + 1) + left];
    int i = left, j = right;

    while (i <= j)
    {
        // идем слева направо
        while (numbers[i] < pivot)
            i++;
        // идем справа налево
        while (numbers[j] > pivot)
            j--;
        // меняем местами
        // при этом  должны увеличить индексы
        if (i <= j)
        {
            swap(numbers[i++], numbers[j--]);
        }
    }
    //запускаем рекурсию
    //для участка левее пивота
    //далее для участка правее пивота
    //и так далее
    if (left < j)
        qSort(numbers, left, j);
    if (i < right)
        qSort(numbers, i, right);
}


//Необходимо реализовать алгоритм быстрой сортировки.
//В качестве опорного элемента выбирать случайный
void quickSort(int *numbers, int array_size)
{
    qSort(numbers, 0, array_size - 1);
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
    quickSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}