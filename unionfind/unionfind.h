#pragma once
#include "pch.h"

int arr[1000001];
int check[1000001];
int Size, n;

int x[6] = { -1, 0, 0, 1, 0, 0 };
int y[6] = { 0, -1, 1, 0, 0, 0 };
int z[6] = { 0, 0, 0, 0, -1, 1 };

std::string s1, s2;

int total_n; // Total Simulation
int open_n = 0; // Count Open Tile

std::ofstream fout; // Save File

// Random
std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_real_distribution<double> dist_d(0, 100);
std::uniform_int_distribution<int> dist_i;
int r_A, r_B, r_C;

Demension demension;

void Init();
void Set_2D();
void Set_3D();
int Find(int x);
void Union(int x, int y);
void Union_Find_2D();
void Union_Find_3D();
void Random_2D();
void Random_3D();
bool isOpen_2D(int a, int b);
bool isOpen_3D(int a, int b, int c);
bool isPercolate_2D();
bool isPercolate_3D();
void Print_2D(int* ar);
void Main_2D();
void Main_3D();