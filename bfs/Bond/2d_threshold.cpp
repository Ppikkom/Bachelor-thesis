#include "2d_threshold.h"

void Bond2D_Threshold::Array_Erase(int a, int b, int x, int y) {
    li[a][b].erase(remove(li[a][b].begin(), li[a][b].end(), pair<int, int>(x, y)), li[a][b].end());
}

void Bond2D_Threshold::Init() {
    srand((unsigned int)time(NULL));
    Size = 101; // L = Size - 1
    Total = 1000;
    //per = 50;

    dist_i = uniform_int_distribution<int>(0, Size - 1);
}

void Bond2D_Threshold::Set() {

    // Init
    open_n = 0;
    isPercolate = false;
    fill(&check[0][0], &check[Size][Size], false);
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            li[i][j].clear();

}

void Bond2D_Threshold::Print() {

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

void Bond2D_Threshold::bfs(int a, int b) {
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

bool Bond2D_Threshold::Check() {
    if ((find(li[r_A][r_B].begin(), li[r_A][r_B].end(), pair<int, int>(r_A + x[r_C], r_B + y[r_C])) == li[r_A][r_B].end()) && ((r_A + x[r_C] >= 0 && r_A + x[r_C] < Size) && (r_B + y[r_C] >= 0 && r_B + y[r_C] < Size)))
        return false;
    else
        return true;
}

void Bond2D_Threshold::Main() {
    Init();
    //Print();
    string s;
    s = format("{0}_{0}.txt", Size - 1);
    fout.open(s);

    for (int b = 0; b < Total; b++) {

        Set();

        while (1) {
            do {
                r_A = dist_i(eng);
                r_B = dist_i(eng);
                r_C = dist_i2(eng);

            } while (Check());

            open_n++;
            li[r_A][r_B].push_back(make_pair(r_A + x[r_C], r_B + y[r_C]));
            li[r_A + x[r_C]][r_B + y[r_C]].push_back(make_pair(r_A, r_B));

            fill(&check[0][0], &check[Size][Size], false);

            for (int i = 0; i < Size; i++)
                if (!li[0][i].empty() && !check[0][i])
                    bfs(0, i);

            if (isPercolate) {
                break;
            }

        }
        cout << (double)open_n / ((Size - 1) * Size * 2) << "\n";
        fout << (double)open_n / ((Size - 1) * Size * 2) << " ";
    }

    fout.close();
}
