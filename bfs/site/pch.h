#pragma once
using namespace std;
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
#include <format>
#include <iomanip>


inline std::random_device rd;
inline std::default_random_engine eng(rd());
inline std::uniform_real_distribution<double> dist_d(0, 100);
inline std::uniform_int_distribution<int> dist_i;


class Site {
public :
	virtual void Init() = 0;
	virtual void Set() = 0;
	virtual void Main() = 0;
};
