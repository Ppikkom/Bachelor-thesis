#pragma once
#include "pch.h"

class Site2D_Thershold : public Site{
public:
	int arr[200][200];
	int check[200][200];
	int Size;

	int x[4] = { -1, 0, 0, 1 };
	int y[4] = { 0, -1, 1, 0 };

	bool isPercolate;

	int total_n; // Total Simualtion
	int open_n = 0; // Count Open Tile

	ofstream fout; // Save File

	// Random Value
	int r_A, r_B;

	virtual void Init() override;
	virtual void Set() override;
	virtual void Main() override;
	bool isOpen(int a, int b);
	bool isVisit(int a, int b);
	void BFS(int a, int b);
};
