#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть

class Vertex
{
public:
    int bound;
    vector<Edge> edges;
};

int findMin(vector<Vertex>& vertex, vector<bool>& used)
{
    int min = 30001;
    int min_v;
    for (int i = 0; i < vertex.size(); ++i)
    {
        if(!used[i] && vertex[i].bound < min)
        {
            min = vertex[i].bound;
            min_v = i;
        }
    }
    return min_v;
}

void solve(int N, int M, vector<Edge>& edges, vector<int>& result)
{
    //Советую разделить решение на логические блоки
    vector<Vertex> vertex(N);
    vector<bool> used;
    used.assign(N, false);
    int cur = 0;
    int number = 0;
    for (int i = 0; i < N; ++i)
    {
        vertex[i].bound = 30001;
        for (int j = 0; j < edges.size(); ++j)
        {
            if(edges[j].A == i)
                vertex[i].edges.push_back(edges[j]);
        }
    }
    vertex[0].bound = 0;

    while(number < N)
    {
        cur = findMin(vertex, used);
        used[cur] = true;
        for (int i = 0; i < vertex[cur].edges.size(); ++i)
        {
            if(vertex[cur].edges[i].W + vertex[cur].bound < vertex[vertex[cur].edges[i].B].bound && !used[vertex[cur].edges[i].B])
                vertex[vertex[cur].edges[i].B].bound = vertex[cur].edges[i].W + vertex[cur].bound;
        }
        number++;
    }

    for (int i = 1; i < N; ++i)
    {
        result.push_back(vertex[i].bound);
    }
}

int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<int> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeIntValues(result);

    return 0;
}