#pragma once
#include "pch.h"

class Site3D_Threshold : public Site{
public:
	int arr[101][101][101];
	int check[101][101][101];
	int Size;

	int x[6] = { -1, 0, 0, 1, 0, 0 };
	int y[6] = { 0, -1, 1, 0, 0, 0 };
	int z[6] = { 0, 0, 0, 0, -1, 1 };

	bool isPercolate;

	int total_n;
	int open_n = 0;

	ofstream fout;
	int r_A, r_B, r_C;

	virtual void Init() override;
	virtual void Set() override;
	virtual void Main() override;
	bool isOpen(int a, int b);
	bool isVisit(int a, int b);
	void BFS(int a, int b, int c);
};
