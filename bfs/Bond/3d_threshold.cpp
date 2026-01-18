#include "3d_threshold.h"

void Bond3D_Threshold::Init() {
    srand((unsigned int)time(NULL));
    Size = 21;
    Total = 100;

    dist_i = uniform_int_distribution<int>(0, Size - 1);
}

void Bond3D_Threshold::Set() {
    open_n = 0;
    isPercolate = false;
    fill(&check[0][0][0], &check[Size][Size][Size], false);
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            for (int k = 0; k < Size; k++)
                li[i][j][k].clear();
}

void Bond3D_Threshold::bfs(int a, int b, int c) {
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
        check[Fst][Snd][Thr] = 1;
        for (auto& pair : li[Fst][Snd][Thr]) {
            if (check[get<0>(pair)][get<1>(pair)][get<2>(pair)]) continue;
            q.push(make_tuple(get<0>(pair), get<1>(pair), get<2>(pair)));
            check[get<0>(pair)][get<1>(pair)][get<2>(pair)] = 1;
        }

    }
}

bool Bond3D_Threshold::Check() {
    if ((find(li[r_A][r_B][r_C].begin(), li[r_A][r_B][r_C].end(), tuple<int, int, int>(r_A + x[r_D], r_B + y[r_D], r_C + z[r_D])) == li[r_A][r_B][r_C].end()) && ((r_A + x[r_D] >= 0 && r_A + x[r_D] < Size) && (r_B + y[r_D] >= 0 && r_B + y[r_D] < Size) && (r_C + z[r_D] >= 0 && r_C + z[r_D] < Size)))
        return false;
    else
        return true;
}

void Bond3D_Threshold::Main() {
    Init();
    //Print();
    string s;
    s = format("{0}_{0}_{0}.txt", Size - 1);
    fout.open(s);

    for (int b = 0; b < Total; b++) {

        Set();

        while (1) {
            do {
                r_A = dist_i(eng);
                r_B = dist_i(eng);
                r_C = dist_i(eng);
                r_D = dist_i3(eng);

            } while (Check());

            open_n++;
            li[r_A][r_B][r_C].push_back(make_tuple(r_A + x[r_D], r_B + y[r_D], r_C + z[r_D]));
            li[r_A + x[r_D]][r_B + y[r_D]][r_C + z[r_D]].push_back(make_tuple(r_A, r_B, r_C));

            fill(&check[0][0][0], &check[Size][Size][Size], false);

            for (int i = 0; i < Size; i++)
                for (int j = 0; j < Size; j++)
                    if (!li[0][i][j].empty() && !check[0][i][j])
                        bfs(0, i, j);

            if (isPercolate) {
                break;
            }

        }
        cout << (double)open_n / (((Size - 1) * Size * Size) * 3) << "\n";
        fout << (double)open_n / (((Size - 1) * Size * Size) * 3) << " ";
    }

    fout.close();
}