#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

//Функция для построения кучи
//Ответ должен лежать в массиве ages
void heapify(int* ages, int n, int arrSize)
{
    int leftChild = 2*n + 1;
    int rightChild = 2*n + 2;
    int largest;

    if(leftChild < arrSize && ages[leftChild] > ages[n])
        largest = leftChild;
    else
        largest = n;
    if(rightChild < arrSize && ages[rightChild] > ages[largest])
        largest = rightChild;

    if(largest != n)
    {
        int cur = ages[n];
        ages[n] = ages[largest];
        ages[largest] = cur;
        heapify(ages, largest, arrSize);
    }
}
void heapBuild(int *ages, int n)
{
    for (int i = n/2; i >= 0; --i)
    {
        heapify(ages, i, n);
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

    //Запуск построения кучи, ответ в том же массиве (brr)
    heapBuild(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
