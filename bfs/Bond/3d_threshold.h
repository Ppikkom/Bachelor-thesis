#pragma once
#include "pch.h"

class Bond3D_Threshold : public Bond{
    vector<tuple<int, int, int>> li[101][101][101];

    int x[6] = { -1 ,1 ,0, 0, 0, 0 };
    int y[6] = { 0, 0, -1 ,1, 0, 0 };
    int z[6] = { 0, 0, 0 , 0, -1, 1 };

    int Size;
    int Total;
    int r_A, r_B, r_C, r_D;

    double per;

    bool check[101][101][101];
    bool isPercolate;
    int success_n = 0;

    int open_n;

    ofstream fout;
public:
    virtual void Init() override;
    virtual void Set() override;
    virtual void Main() override;

    void bfs(int a, int b, int c);
    bool Check();
};