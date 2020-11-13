#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.

class Component
{
public:
    int parent;
    int comp;
};

// finding parent of each component
int find(Component components[], int i)
{
    if (components[i].parent != i)
        components[i].parent =
                find(components, components[i].parent);

    return components[i].parent;
}

// merge two components
void merge(Component subsets[], int x, int y)
{
    int xParent = find(subsets, x);
    int yParent = find(subsets, y);

    if (subsets[xParent].comp < subsets[yParent].comp)
        subsets[xParent].parent = yParent;
    else if (subsets[xParent].comp > subsets[yParent].comp)
        subsets[yParent].parent = xParent;
    else
    {
        subsets[yParent].parent = xParent;
        subsets[xParent].comp++;
    }
}

void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    //Советую разделить решение на логические блоки
    //Можно использовать любые другие структуры, но затем скопировать ответ в структуру Edge для записи результата в файл.
    //Также можно добавить любые необходимые компараторы для предложенного класса Edge, так как все методы и поля публичные.
    Component components[N];
    int cheapest[N];

    for (int v = 0; v < N; ++v)
    {
        components[v].parent = v;
        components[v].comp = 0;
        cheapest[v] = -1;
    }

    int numTrees = N;

    while (numTrees > 1)
    {
        for (int v = 0; v < N; ++v)
        {
            cheapest[v] = -1;
        }

        for (int i = 0; i < M; i++)
        {
            // finding parent of each component
            int comp1 = find(components, edges[i].A);
            int comp2 = find(components, edges[i].B);

            // if they are equal, they are in the same component.
            // skip it
            if (comp1 == comp2)
                continue;
            else
            {
                if (cheapest[comp1] == -1 || edges[i].W < edges[cheapest[comp1]].W)
                    cheapest[comp1] = i;

                if (cheapest[comp2] == -1 || edges[i].W < edges[cheapest[comp2]].W)
                    cheapest[comp2] = i;
            }
        }

        for (int i = 0; i < N; i++)
        {
            if (cheapest[i] != -1)
            {
                // finding parents of components
                int comp1 = find(components, edges[cheapest[i]].A);
                int comp2 = find(components, edges[cheapest[i]].B);

                if (comp1 == comp2)
                    continue;

                result.push_back(edges[cheapest[i]]);

                merge(components, comp1, comp2);
                numTrees--;
            }
        }
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
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}