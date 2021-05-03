#include <iostream>
#include <deque>
#include <tuple>

using namespace std;

int N, M, K;



class Fireball
{
public:	
	int m;
	int d;
	int s;

	Fireball(int m, int s, int d) {
		this->m = m;
		this->s = s;
		this->d = d;
	}

	Fireball();
	~Fireball();

private:

};

Fireball::Fireball()
{
}

Fireball::~Fireball()
{
}


class GridUnit
{
public:
	deque<Fireball> fireballs;
	int before_move_size; // 이동하기 전인 파이어볼 수 기억하기 위함
	GridUnit();
	~GridUnit();

private:

};

GridUnit::GridUnit()
{
	before_move_size = 0;
}

GridUnit::~GridUnit()
{
}

GridUnit **grid;


void MoveFireBall(int x, int y, int d, int m, int s) {
	int dx[8] = { -1,-1,0,1,1,1,0,-1 };
	int dy[8] = { 0,1,1,1,0,-1,-1,-1 };


	int newX, newY;
	int speed = s%N;
	newX = x + dx[d] * speed;
	newY = y + dy[d] * speed;

	if (newX > N - 1) {
		newX = newX - N;
	}
	else if (newX < 0) {
		newX = newX + N;
	}

	if (newY > N - 1) {
		newY = newY - N;
	}
	else if (newY < 0) {
		newY = newY + N;
	}
	grid[newX][newY].fireballs.push_back(Fireball(m, s, d));
}
int main() {
	cin >> N >> M >> K;

	grid = new GridUnit*[N];
	for (int i = 0; i < N; i++) {
		grid[i] = new GridUnit[N];
	}

	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		grid[r-1][c-1].fireballs.push_back(Fireball(m, s, d));
		grid[r-1][c-1].before_move_size += 1;
	}

	while (K--) {

		//파이어볼 이동
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!grid[i][j].fireballs.empty()) {
					for (int k = 0; k < grid[i][j].before_move_size; k++) {
						Fireball FB = grid[i][j].fireballs.front();
						grid[i][j].fireballs.pop_front();
						MoveFireBall(i, j, FB.d, FB.m, FB.s);
					}
				}
			}
		}

		//파이어 볼 변신..?
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (grid[i][j].fireballs.size() >= 2) {
					int size = grid[i][j].fireballs.size();
					int new_M = 0, new_S = 0;
					int isEven = 0, isOdd = 0;
					//질량 , 속력, 방향 구하기
					while (!grid[i][j].fireballs.empty()) {
						Fireball FB = grid[i][j].fireballs.front();
						grid[i][j].fireballs.pop_front();
						new_M += FB.m; //질량 모두 더하기
						new_S += FB.s; //속도 모두 더하기
						if (FB.d % 2 == 0)
							isEven += 1;
						else
							isOdd += 1;
					}

					new_M = new_M / 5;
					new_S = new_S / size;
					if (new_M != 0) {
						if (isEven == size || isOdd == size) {
							int new_D[4] = { 0,2,4,6 };
							for (int num = 0; num < 4; num++) {
								grid[i][j].fireballs.push_back(Fireball(new_M, new_S, new_D[num]));
							}
						}
						else {
							int new_D[4] = { 1,3,5,7 };
							for (int num = 0; num < 4; num++) {
								grid[i][j].fireballs.push_back(Fireball(new_M, new_S, new_D[num]));
							}
						}
					}

				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				grid[i][j].before_move_size = grid[i][j].fireballs.size();
			}
		}
	}
	
	int total_mess=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!grid[i][j].fireballs.empty()) {
				for (Fireball FB : grid[i][j].fireballs) {
					total_mess += FB.m;
				}
			}
			
		}
	}


	cout << total_mess;

	
	
	for (int i = 0; i < N; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}