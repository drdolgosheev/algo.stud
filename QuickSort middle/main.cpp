#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

//Необходимо реализовать алгоритм быстрой сортировки.
//В качестве опорного элемента выбирать случайный
int partition(int* numbers, int p, int r)
{
    int x = numbers[p];
    int i = p-1;
    int j = r+1;
    while(true)
    {
        do
            i++;
        while(numbers[i] < x);
        do
            j--;
        while(numbers[j] > x);
        if(i >= j)
            return j;
        swap(numbers[i], numbers[j]);
    }
}

void rand_quicksort(int* numbers, int p, int r)
{
    if(p < r)
    {
        int q = partition(numbers, p, r);
        rand_quicksort(numbers, p , q);
        rand_quicksort(numbers, q+1 , r);
    }
}

void quickSort(int *numbers, int array_size)
{
    rand_quicksort(numbers, 0 ,array_size - 1);
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