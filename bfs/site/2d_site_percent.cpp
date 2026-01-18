#include "2d_site_percent.h"

void Site2D_Percent::Init() {
	srand((unsigned int)time(NULL));

	total_n = 100;

	//cout << "격자 크기 입력 : ";

	Size = 100;

}

void Site2D_Percent::Set() {
	//Init TIle
	fill(&arr[0][0], &arr[Size][Size], 0);
	fill(&check[0][0], &check[Size][Size], 0);
	tcnt = 1;
	success = false;


	//Set Tile
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {

				rnum = dist_d(eng);
				if (rnum <= per)
					arr[i][j] = 1;
				else
					check[i][j] = -1;


		}
	}
}

void Site2D_Percent::bfs(int a, int b) {

	queue<pair<int, int>> q;
	q.push(make_pair(a, b));

	int Fst = a;
	int Snd = b;

	while (!q.empty()) {
		Fst = q.front().first;
		Snd = q.front().second;

		// Check Break Condition
		if (a == 0 && Fst == Size - 1) {
			success = true;
			return;
		}

		q.pop();
		check[Fst][Snd] = tcnt;
		for (int i = 0; i < 4; i++) {
			int dx = Fst + x[i];
			int dy = Snd + y[i];

			if (dx >= 0 && dy >= 0 && dx < Size && dy < Size) {
				if (arr[dx][dy] == 1 && check[dx][dy] == 0) {
					q.push(pair<int, int>(dx, dy));
					check[dx][dy] = tcnt;
				}
			}
			else continue;


		}

	}
	return;
}


void Site2D_Percent::Main() {
	Init();
	string s;
	s = format("{0}_{0}.txt", Size);
	fout.open(s);

	for (per = 1; per <= 100; per++) {
		success_n = 0;
		for (int n = 1; n <= total_n; n++) { // Simulation Count

			Set();
			for (int i = 0; i < Size; i++) {

				int b = i % Size;
				if (check[0][b] != 0) continue;
				bfs(0, b);
				if (success) {
					success_n++;
					break;
				}
				tcnt++;
			}
		}
		cout << "#" << per << " Completed!\n";
		fout << success_n << " ";
	}

	fout.close();
}
