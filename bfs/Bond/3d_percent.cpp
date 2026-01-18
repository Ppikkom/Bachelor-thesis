#include "3d_percent.h"

void Bond3D_Percent::Init() {
    srand((unsigned int)time(NULL));
    Size = 16; // L = Size - 1
    //per = 50;
    Total = 1000;

}

void Bond3D_Percent::Set() {
    isPercolate = false;
    fill(&check[0][0][0], &check[Size][Size][Size], false);
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            for (int k = 0; k < Size; k++)
                li[i][j][k].clear();

    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            for (int k = 0; k < Size; k++) {
                for (int l = 0; l < 6; l++) {
                    int dx = i + x[l];
                    int dy = j + y[l];
                    int dz = k + z[i];
                    if ((dx >= 0 && dx < Size) && (dy >= 0 && dy < Size) && (dz >= 0 && dz < Size))
                        li[i][j][k].push_back(make_tuple(dx, dy, dz));
                }
            }

        }
    }

    //
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            for (int k = 0; k < Size; k++) {

                check[i][j][k] = true;

                for (auto& pair : li[i][j][k]) {
                    rnum = dist_d(eng);

                    int a = get<0>(pair);
                    int b = get<1>(pair);
                    int c = get<2>(pair);
                    if (check[a][b][c]) continue;

                    if (rnum <= per) {

                    }
                    else {

                        li[a][b][c].erase(remove(li[a][b][c].begin(), li[a][b][c].end(), make_tuple(i, j, k)), li[a][b][c].end());
                        li[i][j][k].erase(remove(li[i][j][k].begin(), li[i][j][k].end(), make_tuple(a, b, c)), li[i][j][k].end());

                    }
                }
            }

        }

    }
}

void Bond3D_Percent::bfs(int a, int b, int c) {
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(a, b, c));

    int Fst = a;
    int Snd = b;
    int Thr = c;

    while (!q.empty()) {
        Fst = get<0>(q.front());
        Snd = get<1>(q.front());
        Thr = get<2>(q.front());

        if (Fst == Size - 1) {
            isPercolate = true;
            return;
        }

        q.pop();
        check[Fst][Snd][Thr] = true;
        for (auto& pair : li[Fst][Snd][Thr]) {
            if (check[get<0>(pair)][get<1>(pair)][get<2>(pair)]) continue;
            q.push(make_tuple(get<0>(pair), get<1>(pair), get<2>(pair)));
            check[get<0>(pair)][get<1>(pair)][get<2>(pair)] = true;
        }

    }
}

void Bond3D_Percent::Main() {
    Init();
    //Print();

    string s;
    s = format("data{0}_{0}_{0}.txt", Size - 1);
    fout.open(s);
    for (per = 1; per <= 100; per++) {
        success_n = 0;
        for (int b = 0; b < Total; b++) {

            Set();

            fill(&check[0][0][0], &check[Size][Size][Size], false);
            for (int i = 0; i < Size * Size; i++) {

                if (!li[0][i / Size][i % Size].empty() && !check[0][i / Size][i % Size])
                    bfs(0, i / Size, i % Size);
                if (isPercolate) {
                    success_n++;
                    break;
                }

            }

        }
        cout << "#" << per << " Completed" << " Open Tile : " << success_n << "\n";

        fout << success_n << "\n";
    }

    fout.close();
}