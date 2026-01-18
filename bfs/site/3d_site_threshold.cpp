#include "3d_site_threshold.h"

void Site3D_Threshold::Init() {

    srand((unsigned int)time(NULL));

    total_n = 1000;

    Size = 50;

    dist_i = uniform_int_distribution<int>(0, Size - 1); //
}

void Site3D_Threshold::Set() {
    fill(&arr[0][0][0], &arr[Size][Size][Size], 0);
    fill(&check[0][0][0], &check[Size][Size][Size], 0);

    open_n = 0;
    isPercolate = false;
}


bool Site3D_Threshold::isOpen(int a, int b) { // 이미 타일이 열렸는지
    if (arr[a][b]) return true;
    return false;
}

bool Site3D_Threshold::isVisit(int a, int b) {
    if (check[a][b]) return true;
    return false;
}

void Site3D_Threshold::BFS(int a, int b, int c) {
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(a, b, c));

    int Fst = a;
    int Snd = b;
    int Thr = c;

    check[a][b][c] = 1;

    while (!q.empty()) {

        Fst = get<0>(q.front());
        Snd = get<1>(q.front());
        Thr = get<2>(q.front());

        if (Fst == Size - 1) {
            isPercolate = true;
            return;
        }

        q.pop();


        for (int i = 0; i < 6; i++) {
            int dx = Fst + x[i];
            int dy = Snd + y[i];
            int dz = Thr + z[i];

            if ((dx >= 0 && dx < Size) && (dy >= 0 && dy < Size) && (dz >= 0 && dz < Size)) {
                if (arr[dx][dy][dz] && check[dx][dy][dz] == 0) {
                    check[dx][dy][dz] = 1;
                    q.push(make_tuple(dx, dy, dz));

                }

            }

        }

    }
}


void Site3D_Threshold::Main() {
    Init();
    string s;
    s = format("{0}_{0}_{0}.txt", Size);
    fout.open(s);

    for (int n = 1; n <= total_n; n++) {
        Set();
        while (1) {

            do {
                r_A = dist_i(eng);
                r_B = dist_i(eng);
                r_C = dist_i(eng);
            } while (arr[r_A][r_B][r_C]);

            // Open Tile
            open_n++;
            arr[r_A][r_B][r_C] = 1;

            fill(&check[0][0][0], &check[Size][Size][Size], 0);

            for (int i = 0; i < Size; i++)
                for (int j = 0; j < Size; j++)
                    if (arr[0][i][j] && !check[0][i][j])
                        BFS(0, i, j);

            if (isPercolate) {
                break;
            }

        }

        cout << "Open Tile : " << open_n << " Estimated probability : " << std::setprecision(10) << (double)open_n / (Size * Size * Size) << "      /////////////" << n << "\n";
        fout << std::setprecision(10) << (double)open_n / (Size * Size * Size) << " ";

    }

    fout.close();
}