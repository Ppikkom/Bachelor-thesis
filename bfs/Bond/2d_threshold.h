#pragma once
#include "pch.h"

class Bond2D_Threshold : public Bond {

    vector<pair<int, int>> li[1001][1001];

    int x[4] = { -1 ,1 ,0, 0 };
    int y[4] = { 0, 0, -1 ,1 };

    int Size;
    int Total;

    int r_A, r_B, r_C;

    double per;

    bool check[1001][1001];
    bool isPercolate;
    int success_n = 0;

    int open_n;

    ofstream fout;

public: 
    virtual void Init() override;
    virtual void Set() override;
    virtual void Main() override;

    void Array_Erase(int a, int b, int x, int y);
    void Print();
    void bfs(int a, int b);
    bool Check();
};