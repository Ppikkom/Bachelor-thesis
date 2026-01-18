#include "2d_percent.h"

void Bond2D_Percent::Array_Erase(int a, int b, int x, int y) {
    li[a][b].erase(remove(li[a][b].begin(), li[a][b].end(), make_pair(x, y)), li[a][b].end());
}

template <typename T>
void Bond2D_Percent::quick_remove_at(vector<T>& v, typename vector<T>::iterator it)
{
    if (it != end(v)) {
        *it = move(v.back());
        v.pop_back();
    }
}


void Bond2D_Percent::Init() {
    srand((unsigned int)time(NULL));
    Size = 11; // L = Size - 1
    //per = 50;
    Total = 1000;

}

void Bond2D_Percent::Set() {

    // Init
    isPercolate = false;
    fill(&check[0][0], &check[Size][Size], false);
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            li[i][j].clear();

    // Make Graph
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            for (int k = 0; k < 4; k++) {
                int dx = i + x[k];
                int dy = j + y[k];
                if ((dx >= 0 && dx < Size) && (dy >= 0 && dy < Size))
                    li[i][j].push_back(make_pair(dx, dy));
            }
        }
    }

    //
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            check[i][j] = 1;

            for (auto& pair : li[i][j]) {
                rnum = dist_d(eng);

                int a = pair.first;
                int b = pair.second;
                if (check[a][b]) continue;

                if (rnum <= per) {

                }
                else {

                    li[a][b].erase(remove(li[a][b].begin(), li[a][b].end(), make_pair(i, j)), li[a][b].end());
                    li[i][j].erase(remove(li[i][j].begin(), li[i][j].end(), make_pair(a, b)), li[i][j].end());

                    //quick_remove_at(li[a][b], find(begin(li[a][b]), end(li[a][b]), make_pair(i, j)) );
                    //quick_remove_at(li[i][j], find(begin(li[i][j]), end(li[i][j]), make_pair(a, b)));

                    //Array_Erase(a, b, i, j);
                    //Array_Erase(i, j, a, b);
                    //
                    //cout << "Test #3" << "\n";
                }
            }

        }
    }

}

void Bond2D_Percent::Print() {

    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {

            vector<pair<int, int>>::iterator iter;

            cout << "[" << i << ", " << j << "] : ";
            for (auto& pair : li[i][j]) {
                cout << pair.first << " " << pair.second << " ";
            }

            cout << "\n";
        }
    }
}

void Bond2D_Percent::bfs(int a, int b) {
    queue<pair<int, int>> q;
    q.push(make_pair(a, b));

    int Fst = a;
    int Snd = b;

    while (!q.empty()) {
        Fst = q.front().first;
        Snd = q.front().second;

        if (Fst == Size - 1) {
            isPercolate = true;
            return;
        }

        q.pop();
        check[Fst][Snd] = 1;
        for (auto& pair : li[Fst][Snd]) {
            if (check[pair.first][pair.second]) continue;
            q.push(make_pair(pair.first, pair.second));
            check[pair.first][pair.second] = 1;
        }

    }
}

void Bond2D_Percent::Main() {
    Init();
    //Print();

    string s;
    s = format("data{0}_{0}.txt", Size - 1);
    fout.open(s);
    for (per = 1; per <= 100; per++) {
        success_n = 0;
        for (int b = 0; b < Total; b++) {

            Set();

            fill(&check[0][0], &check[Size][Size], false);
            for (int i = 0; i < Size; i++) {
                //cout << li[0][i].empty() << "\n";
                if (!li[0][i].empty() && !check[0][i])
                    bfs(0, i);
                if (isPercolate) {
                    success_n++;
                    break;
                }
            }

        }
        cout << "#" << per << " Completed!" << "\n";
        fout << success_n << "\n";
    }

    fout.close();
}