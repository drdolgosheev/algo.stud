#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h
#include <algorithm>
#include <climits>

using namespace std;
	    // write all values
    void ReadWriter::writeValues(std::vector<std::vector<int>>& result)
    {
        if (!fout.is_open())
            throw std::ios_base::failure("file not open");

        for (int i = 0; i < result.size(); ++i)
        {
            for (int j = 0; j < result[i].size(); ++j)
            {
                (result[i][j] == 130001) ? result[i][j] = -1 : result[i][j];
                if(i != j)
                    fout << i << " " << j << " " << result[i][j] << '\n';
            }
        }
    }

    vector<vector<int>> extend_shortest_path(vector<vector<int>>& L, vector<vector<int>>& W, int size)
    {
        vector<vector<int>> new_L(size);
        for (int i = 0; i < size; ++i)
        {
            new_L[i] = vector<int>(size);
            for (int j = 0; j < size; ++j)
            {
                new_L[i][j] = 130001;
                for (int k = 0; k < size; ++k)
                {
                    new_L[i][j] = min(new_L[i][j], min(L[i][j], L[i][k] + W[k][j]));
                }
            }
        }
        return new_L;
    }


void solve(int N, int M, vector<Edge>& edges, vector<vector<int>>& result)
{
    vector<vector<int>> W(N);
    for (int i = 0; i < N; ++i)
    {
        W[i] = vector<int>(N);
        for (int j = 0; j < N; ++j)
        {
            W[i][j] = 130001;
        }
    }
    for (int i = 0; i < edges.size(); ++i)
    {
        W[edges[i].A][edges[i].B] = edges[i].W;
    }
    vector<vector<int>> L(N);
    L = W;
    int m = 1;
    while(m < N - 1)
    {
        L = extend_shortest_path(L, L, N);
        m = m * 2;
    }
    result = L;
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

    vector<vector<int>> result(N);

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    rw.writeValues(result);

    return 0;
}