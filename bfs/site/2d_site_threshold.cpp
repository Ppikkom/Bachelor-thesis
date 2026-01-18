#include "2d_site_threshold.h"

void Site2D_Thershold::Init() {

    srand((unsigned int)time(NULL));

    total_n = 1000;

    Size = 150;

    dist_i = uniform_int_distribution<int>(0, Size - 1); //
}

void Site2D_Thershold::Set() {

    fill(&arr[0][0], &arr[Size][Size], 0);
    fill(&check[0][0], &check[Size][Size], 0);

    // Init Vale
    open_n = 0;
    isPercolate = false;
}


bool Site2D_Thershold::isOpen(int a, int b) {
    if (arr[a][b]) return true;
    return false;
}

bool Site2D_Thershold::isVisit(int a, int b) {
    if (check[a][b]) return true;
    return false;
}


// BFS
void Site2D_Thershold::BFS(int a, int b) {
    queue<pair<int, int>> q;
    q.push(make_pair(a, b));

    int Fst = a;
    int Snd = b;

    check[a][b] = 1;

    while (!q.empty()) {

        Fst = q.front().first;
        Snd = q.front().second;

        //check[a][b] = 1;

        if (Fst == Size - 1) {
            isPercolate = true;
            return;
        }

        q.pop();


        for (int i = 0; i < 4; i++) {
            int dx = Fst + x[i];
            int dy = Snd + y[i];
            //cout << "Test 1" << "\n";
            if ((dx >= 0 && dx < Size) && (dy >= 0 && dy < Size)) {
                if (arr[dx][dy] && check[dx][dy] == 0) {
                   // cout << "Test 2" << "\n";
                    check[dx][dy] = 1;
                    q.push(make_pair(dx, dy));

                }

            }

        }

    }

}


void Site2D_Thershold::Main() {
    Init();
    string s;
    s = format("{0}_{0}.txt", Size);
    fout.open(s);

    for (int n = 1; n <= total_n; n++) { // Total Simulation
        Set();
        while (1) {

            do {
                r_A = dist_i(eng);
                r_B = dist_i(eng);
            } while (arr[r_A][r_B]);

            // Open Tile
            open_n++;
            arr[r_A][r_B] = 1;

            fill(&check[0][0], &check[Size][Size], 0);

            // BFS
            for (int i = 0; i < Size; i++)
                if (arr[0][i] && !check[0][i])
                    BFS(0, i);

            // Check
            if (isPercolate) {
                break;
            }

        }

        cout << "Open Tile : " << open_n << " Estimated probability : " << (double)open_n / (Size * Size) << "    #" << n << '\n';
        fout << (double)open_n / (Size * Size) << " ";
    }

    fout.close();
}