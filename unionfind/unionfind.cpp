#include "pch.h"
#include "unionfind.h"

int main() {

    Init();
    s1 = std::format("{0}_data{1}.txt", s2, Size);
    fout.open(s1);

    for (n = 1; n <= total_n; n++) { // Num of Trial

        switch (demension) {
            case Demension::TwoDimension:
                Set_2D();
                Main_2D();
                break;
            case Demension::ThreeDimension:
                Set_3D();
                Main_3D();
                break;
            default:
                std::cout << "Error\n";
                return 0;
        }
    }
    fout.close();
}

// Setting ///// hearrrrrrrr
void Init() {
    srand((unsigned int)time(NULL));
    ///////////////////////////////// set this!
    total_n = 1000;
    Size = 20;
    demension = Demension::ThreeDimension;
    /////////////////////////////////
    dist_i = std::uniform_int_distribution<int>(0, Size - 1); // 
}

void Set_2D() {
    //Init Tile
    for (int i = 0; i < Size * Size; i++)
        arr[i] = i;
    std::fill(&check[0], &check[Size * Size], 0);

    // Init Variable
    open_n = 0;
}

void Set_3D() {
    for (int i = 0; i < Size * Size * Size; i++)
        arr[i] = i;
    std::fill(&check[0], &check[Size * Size * Size], 0);

    open_n = 0;
}

// UnionFind
int Find(int x) {
    if (arr[x] == x) return x;
    else return arr[x] = Find(arr[x]);
}

void Union(int x, int y) {
    int parent_x = Find(x);
    int parent_y = Find(y);

    if (parent_x < parent_y)
        arr[parent_y] = parent_x;
    else
        arr[parent_x] = parent_y;
}

void Union_Find_2D() {
    for (int i = 0; i < 4; i++) {
        int dx = r_A + x[i];
        int dy = r_B + y[i];

        // Check Corner and Open Tile
        if ((dx < 0) || (dx >= Size) || (dy < 0) || (dy >= Size)) continue;
        if (!isOpen_2D(dx, dy)) continue;

        Union(Find(r_A * Size + r_B), Find(dx * Size + dy));
    }
}

void Union_Find_3D() {
    for (int i = 0; i < 6; i++) {
        int dx = r_A + x[i];
        int dy = r_B + y[i];
        int dz = r_C + z[i];

        // Check Corner and Open Tile
        if ((dx < 0) || (dx >= Size) || (dy < 0) || (dy >= Size) || (dz < 0) || (dz >= Size)) continue;
        if (!isOpen_3D(dx, dy, dz)) continue;

        Union(Find(r_A * Size * Size + r_B * Size + r_C), Find(dx * Size * Size + dy * Size + dz));
    }
}

// Random Tile Open
void Random_2D() {
    do {
        r_A = dist_i(eng);
        r_B = dist_i(eng);
    } while (isOpen_2D(r_A, r_B));

    check[r_A * Size + r_B] = 1;
    open_n++;
}

void Random_3D() {
    do {
        r_A = dist_i(eng);
        r_B = dist_i(eng);
        r_C = dist_i(eng);
    } while (isOpen_3D(r_A, r_B, r_C));

    check[r_A * Size * Size + r_B * Size + r_C] = 1;
    open_n++;
}

bool isOpen_2D(int a, int b) { // Is the tile already open
    if (check[a * Size + b]) return true;
    return false;
}

bool isOpen_3D(int a, int b, int c) {
    if (check[a * Size * Size + b * Size + c]) return true;
    return false;
}

// Check Percolation State
bool isPercolate_2D() {
    for (int i = 0; i < Size; i++) {
        if (!isOpen_2D(Size - 1, i)) continue;
        if (Find(Size * (Size - 1) + i) < Size) return true;
    }
    return false;
}

bool isPercolate_3D() {
    for (int i = 0; i < Size * Size; i++) {
        if (!isOpen_3D(Size - 1, i / Size, i % Size)) continue; // 
        if (Find(Size * Size * (Size - 1) + i) < Size * Size) return true;
    }
    return false;
}

// Debug
void Print_2D(int* ar) {
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            std::cout << *(ar + i * Size + j) << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

// Main
void Main_2D() {
    while (1) {
        Random_2D();
        Union_Find_2D();
        if (isPercolate_2D()) break;
    }
    std::cout << "Open Tile : " << open_n << " Estimated probability : " << (double)open_n / ((double)Size * Size) << "\t#" << n << '\n';
    fout << (double)open_n / ((double)Size * Size) << " ";
}

void Main_3D() {
    while (1) {
        Random_3D();
        Union_Find_3D();
        if (isPercolate_3D()) break;
    }
    std::cout << "Open Tile : " << open_n << " Estimated probability : " << (double)open_n / ((double)Size * Size * Size) << "\t#" << n << '\n';
    fout << (double)open_n / ((double)Size * Size * Size) << " ";
}

