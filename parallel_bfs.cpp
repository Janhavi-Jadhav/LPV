#include <iostream>
#include <vector>
#include <omp.h>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

void parallel_bfs(int start, int* arr, int n, int visit[])
{
    queue<int> q;
    q.push(start);
    visit[start] = 1;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        cout << current << " ";

        #pragma omp parallel for
        for (int i = 0; i < n; i++)
        {
            if (*(arr + (n * current) + i) == 1 && visit[i] == 0)
            {
                #pragma omp critical
                {
                    q.push(i);
                    visit[i] = 1;
                }
            }
        }
    }
}

void bfs(int start, int* arr, int n, int visit[])
{
    queue<int> q;
    q.push(start);
    visit[start] = 1;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        cout << current << " ";

        for (int i = 0; i < n; i++)
        {
            if (*(arr + (n * current) + i) == 1 && visit[i] == 0)
            {
                q.push(i);
                visit[i] = 1;
            }
        }
    }
}

int main()
{
    cout << "Enter the number of vertices: ";
    int n;
    cin >> n;

    int arr[n][n] = {0};

    cout << "Enter the number of edges: ";
    int edges;
    cin >> edges;

    for (int j = 0; j < edges; j++)
    {
        int a, b;
        cout << "Enter the two edges:" << endl;
        cin >> a >> b;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }

    int visited[n] = {0};

    cout << "Enter the start vertex: ";
    int start;
    cin >> start;
    double strt = omp_get_wtime();
    parallel_bfs(start, (int*)arr, n, visited);
    double stop = omp_get_wtime();

    int v[n] = {0};
    v[start] = 1;
    cout << "\n";
    double st = omp_get_wtime();
    bfs(start, (int*)arr, n, v);
    double sp = omp_get_wtime();

    cout << "\nTime required Parallel Execution: " << (double)(stop - strt) << " ms" << endl;
    cout << "Time required Serial Execution: " << (double)(sp - st) << " ms" << endl;

    return 0;
}

/*

"Parallel Execution"
PS D:\C++> g++ -fopenmp parallel_bfs.cpp
PS D:\C++> ./a out
Enter the number of vertices: 7
Enter the number of edges: 6
Enter the two edges:
0 1
Enter the two edges:
0 2
Enter the two edges:
1 3
Enter the two edges:
1 4
Enter the two edges:
2 5
Enter the two edges:
2 6
Enter the start vertex: 0
0 1 2 3 4 5 6
Time required : 3 ms

"Serial Execution"
PS D:\C++> g++ parallel_bfs.cpp
PS D:\C++> ./a out
Enter the number of vertices: 7
Enter the number of edges: 6
Enter the two edges:
0 1
Enter the two edges:
0 2
Enter the two edges:
1 3
Enter the two edges:
1 4
Enter the two edges:
2 5
Enter the two edges:
2 6
Enter the start vertex: 0
0 1 2 3 4 5 6
Time required : 11 ms


*/