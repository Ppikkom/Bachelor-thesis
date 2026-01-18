#pragma once
#include "pch.h"


class Site2D_Percent : public Site{
public:

    int arr[1001][1001];
    int check[1001][1001];
    int Size; // X * Y
    int X1, Y1; // Set pos
    double per; // percent
    double rnum; // Random Number
    int tcnt; // Tile Cnt
    int total_n; // Total Simulation
    int success_n = 0; // Success Simulation
    bool success;

    int x[4] = { -1, 1, 0, 0 };
    int y[4] = { 0, 0, -1, 1 };

    ofstream fout; // Save File

    virtual void Init() override;
    virtual void Set() override;
    virtual void Main() override;
	void bfs(int a, int b);
};
