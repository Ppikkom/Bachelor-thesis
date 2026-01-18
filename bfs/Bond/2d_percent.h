#pragma once
#include "pch.h"

class Bond2D_Percent : public Bond {
    vector<pair<int, int>> li[1001][1001];

    int x[4] = { -1 ,1 ,0, 0 };
    int y[4] = { 0, 0, -1 ,1 };

    int Size;
    int Total;

    double rnum;
    double per;

    bool check[1001][1001];
    bool isPercolate;
    int success_n = 0;

    ofstream fout;
public:
    virtual void Init() override;
    virtual void Set() override;
    virtual void Main() override;

    void Array_Erase(int a, int b, int x, int y);
    template <typename T>
    void quick_remove_at(vector<T>& v, typename vector<T>::iterator it);
    void Print();
    void bfs(int a, int b);
};