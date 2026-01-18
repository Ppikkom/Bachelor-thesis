#include "3d_site_percent.h"

void Site3D_Percent::Init() {
    srand((unsigned int)time(NULL));

    total_n = 1000;

    Size = 40;

}

void Site3D_Percent::Set() {
    fill(&arr[0][0][0], &arr[Size][Size][Size], 0);
    fill(&check[0][0][0], &check[Size][Size][Size], 0);
    tcnt = 1;
    success = false;

    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            for (int k = 0; k < Size; k++) {
                rnum = rand() % 100;
                if (rnum <= per)
                    arr[i][j][k] = 1;
                else
                    check[i][j][k] = -1;
            }

        }
    }
}

void Site3D_Percent::bfs(int a, int b, int c) {

    queue<tuple<int, int, int>> q;
    q.push(make_tuple(a, b, c));

    int Fst = a;
    int Snd = b;
    int Thr = c;

    while (!q.empty()) {
        Fst = get<0>(q.front());
        Snd = get<1>(q.front());
        Thr = get<2>(q.front());

        if (a == 0 && Fst == Size - 1) {
            success = true;
            return;
        }

        q.pop();
        check[Fst][Snd][Thr] = tcnt;
        for (int i = 0; i < 6; i++) {
            int dx = Fst + x[i];
            int dy = Snd + y[i];
            int dz = Thr + z[i];

            if (dx >= 0 && dy >= 0 && dz >= 0 && dx < Size && dy < Size && dz < Size) {
                if (arr[dx][dy][dz] == 1 && check[dx][dy][dz] == 0) {
                    q.push(tuple<int, int, int>(dx, dy, dz));
                    check[dx][dy][dz] = tcnt;
                }
            }
            else continue;


        }

    }
    return;
}


void Site3D_Percent::Main() {
    Init();

    string s;
    s = format("3d_{0}_{0}_{0}.txt", Size);
    fout.open(s);

    for (per = 1; per <= 100; per++) {
        success_n = 0;
        for (int n = 1; n <= total_n; n++) {

            Set();
            for (int i = 0; i < Size * Size; i++) {

                int Y2 = (i / Size) % Size;
                int Z2 = i % Size;

                if (check[0][Y2][Z2] != 0) continue;
                bfs(0, Y2, Z2);
                if (success) {
                    success_n++;
                    break;
                }
                tcnt++;
            }
        }
        fout << success_n << " ";
        cout << "Case #" << per << "\n";
    }


    //cout << "Success Count : " << success_n << "\n";
    fout.close();
}