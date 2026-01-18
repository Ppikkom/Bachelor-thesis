#pragma once
#include <iostream>
#include <random>
#include <format>
#include <vector>
#include <algorithm>
#include <ctime>
#include <queue>
#include <tuple>
#include <fstream>

using namespace std;

inline std::random_device rd;
inline std::default_random_engine eng(rd());
inline std::uniform_real_distribution<double> dist_d(0, 100);
inline std::uniform_int_distribution<int> dist_i;
inline std::uniform_int_distribution<int> dist_i2(0, 3);
inline std::uniform_int_distribution<int> dist_i3(0, 5);

class Bond {
public:
	virtual void Init() = 0;
	virtual void Set() = 0;
	virtual void Main() = 0;
};
