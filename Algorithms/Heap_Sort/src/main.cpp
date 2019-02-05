#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.
void heapify(int *heap, int heap_size, int i)
{
    int l = 2*i+1;
    int r = 2*i+2;
    // наибольший элемент в корне
    int largest = i;
    // стоит ли наибольший слева
    if (l < heap_size && heap[l] > heap[largest])
        largest = l;
    // или справа
    if (r < heap_size && heap[r] > heap[largest])
        largest = r;
    // если вершина поменялась, то меняем элементы местами и рекурсивно перевызываем
    if (largest != i)
    {
        swap(heap[i], heap[largest]);
        heapify(heap, heap_size, largest);
    }
}
//Функция сортировки на куче
//Необходимо реализовать данную функцию.
//Результат должен быть в массиве numbers.
void heapSort(int *numbers, int array_size)
{
    // строим кучу
    for(int i=array_size/2; i>=0; --i)
    {
        heapify(numbers, array_size, i);
    }
    // извлекаем элементы поочереди
    for (int i=array_size-1; i>=0; --i)
    {
        // ставим корень на место листа
        swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
    }
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
    heapSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}