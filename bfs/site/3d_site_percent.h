#pragma once
#include "pch.h"

class Site3D_Percent : public Site{
public:
	int arr[101][101][101];
	int check[101][101][101];
	int Size; // X * Y * Z
	int X1, Y1, Z1; // Set Pos
	int per;
	int rnum; // Random Number
	int tcnt; // Tile Count
	int total_n; // Total Simualation
	int success_n = 0; // Success Simulation
	bool success;

	int x[6] = { -1, 1, 0, 0, 0, 0 };
	int y[6] = { 0, 0, -1, 1, 0 ,0 };
	int z[6] = { 0, 0, 0, 0, -1, 1 };

	ofstream fout; // Save File

	virtual void Init() override;
	virtual void Set() override;
	virtual void Main() override;

	void bfs(int a, int b, int c);
};
