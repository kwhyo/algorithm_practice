#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int R, C, M;

int ** grid;
int ** newGrid;
pair<int, int> **s_d_grid;
pair<int, int> **new_s_d_grid;
int catchSharksWeight;

int fishingKing_location;


void doFishing() {

	//낚시왕 이동 -> 현재 위치에서 오른쪽(처음엔 -1)
	fishingKing_location += 1;

	for (int i = 0; i < R; i++) {
		if (grid[i][fishingKing_location] > 0) {
			catchSharksWeight += grid[i][fishingKing_location];

			grid[i][fishingKing_location] = 0;
			//상어 잡았다는 뜻~

			return;
		}
	}
}

bool isRange(int x, int y) {
	return x >= 0 && x < R && y >= 0 && y < C;
}

void sharkMove(int insert_x, int insert_y, int z) {
	int x = insert_x;
	int y = insert_y;

	int s, d;
	tie(s, d) = s_d_grid[x][y];

	int newX, newY;

	int dx[5] = { 0,-1,1,0,0 };
	int dy[5] = { 0,0,0,1,-1 };
	int N;
	if (d < 3) {
		N = R;
	}
	else {
		N = C;
	}

	int cnt = s %((N-1)*2) ;
	while (cnt--)
	{
		newX = x + dx[d];
		newY = y + dy[d];

		if (isRange(newX, newY)) { // 범위 안에 있으면
			x = newX;
			y = newY;
		}
		else {
			cnt++; // 방향 바꿔서 한번 더!
			if (d % 2 == 0) {
				d -= 1;
			}
			else {
				d += 1;
			}
		}
	}

	//마지막 남은 x, y, d 
	if (newGrid[x][y] > 0) { //이동한 칸에 다른 상어 있을 때
		if (z > newGrid[x][y]) { //지금 이동하는 상어가 기존에 이동한 상어보다 클 때
			newGrid[x][y] = z;
			new_s_d_grid[x][y] = make_pair(s, d);
		}
	}
	else { //이동할 칸에 상어 없으면 그냥 바로 집어넣기
		newGrid[x][y] = z;
		new_s_d_grid[x][y] = make_pair(s, d);
	}

}

void sharksMove() {

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (grid[i][j] > 0) { //상어가 있을 경우
				sharkMove(i, j, grid[i][j]);
			}
		}
	}


	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			grid[i][j] = newGrid[i][j];
			newGrid[i][j] = 0;
		}
	}


	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			s_d_grid[i][j] = new_s_d_grid[i][j];
			new_s_d_grid[i][j] = make_pair(0, 0); // 없애도,, 될수도,,?
		}
	}

}

int main() {
	cin >> R >> C >> M;

	grid = new int*[R];
	newGrid = new int*[R];
	s_d_grid = new pair<int, int>*[R];
	new_s_d_grid = new pair<int, int>*[R];
	for (int i = 0; i < R; i++) {
		grid[i] = new int[C];
		newGrid[i] = new int[C];
		s_d_grid[i] = new pair<int, int>[C];
		new_s_d_grid[i] = new pair<int, int>[C];
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			grid[i][j] = 0;
			newGrid[i][j] = 0;
		}
	}


	catchSharksWeight = 0;
	int r, c, s, d, z;

	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		grid[r - 1][c - 1] = z;
		s_d_grid[r - 1][c - 1] = make_pair(s, d);
	}


	fishingKing_location = -1;
	for (int i = 0; i < C; i++) {
		doFishing();
		sharksMove();

	}

	cout << catchSharksWeight;





	for (int i = 0; i < R; i++) {
		delete[] grid[i];
		delete[] newGrid[i];
		delete[] s_d_grid[i];
		delete[] new_s_d_grid[i];
	}

	delete[] grid;
	delete[] newGrid;
	delete[] s_d_grid;
	delete[] new_s_d_grid;
}