#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ребер, каждое ребро представлено 3-мя числами (А,В,W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра,
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора ребер, передается по ссылке (&), чтобы не копировать его.

static int comp(Edge& left, Edge& right)
{
    return left.W < right.W;
}


class Components
{
public:
    int* parent; // parent of component
    int* comp; // comp number

    Components(int n)
    {
        parent = new int[n];
        comp = new int[n];

        // initialize components with itself.
        for (int i = 0; i < n; i++)
        {
            comp[i] = 0;
            parent[i] = i;
        }
    }

    // finding parent of the component
    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // merge two components
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        if (comp[x] > comp[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (comp[x] == comp[y])
            comp[y]++;
    }
};

void solve(int N, int M, vector<Edge>& edges, vector<Edge>& result)
{
    //Советую разделить решение на логические блоки
    //Можно использовать любые другие структуры, но затем скопировать ответ в структуру Edge для записи результата в файл.
    //Также можно добавить любые необходимые компараторы для предложенного класса Edge, так как все методы и поля публичные.
    sort(edges.begin(), edges.end(), comp);
    Components components(N);
    for (int i = 0; i < edges.size(); ++i)
    {
        int u = edges[i].A;
        int v = edges[i].B;

        int comp_u = components.find(u); // finding parent of vertex u
        int comp_v = components.find(v); // finding parent of vertex v

        // if they are not same pushing them to result
        // then merge two components
        if(comp_u != comp_v)
        {
            result.push_back(edges[i]);
            components.merge(comp_u, comp_v);
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