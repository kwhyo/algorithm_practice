#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

int R, C, T;

int **A;
int **temp;


vector<pair<int, int>> airCleaner_location;
queue<pair<int, int>> qu;

void findDustLocation() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (A[i][j] > 0) {
				qu.push(make_pair(i, j));
			}
		}
	}
}

bool isRange(int x, int y) {
	return x >= 0 && x < R && y >= 0 && y < C;
}

int calculateDust(int x, int y) {
	return 0;
}



void dustSpread() {
	int dx[4] = { -1,1,0,0 };
	int dy[4] = { 0,0,-1,1 };

	int x, y;
	int newX, newY;
	int cnt = 0;
	while (!qu.empty())
	{
		cnt = 0;
		tie(x, y) = qu.front();
		qu.pop();

		int dust = A[x][y] / 5; //더해질 먼지 양
		for (int i = 0; i < 4; i++) {
			newX = x + dx[i];
			newY = y + dy[i];

			if (isRange(newX, newY) == true && A[newX][newY] != -1) {
				temp[newX][newY] += dust;
				cnt++;
			}
		}

		//남은 값이랑 다른 데서 동시에 들어오는 값 합쳐줘야됨....
		temp[x][y] = temp[x][y] + (A[x][y] - dust * cnt);


	}
}



void movingDust() {
	int top_x, top_y, down_x, down_y;
	tie(top_x, top_y) = airCleaner_location[0];
	tie(down_x, down_y) = airCleaner_location[1];
	

	/*위쪽 공기청정 작업*/
	int save_locate_value = temp[0][top_y];
	for (int k = 0; k < C - 1; k++) {
		temp[0][k] = temp[0][k + 1];
	}
	for (int k = 0; k < top_x; k++) {
		temp[k][C - 1] = temp[k+1][C-1];
	}
	for (int k = C - 1; k > top_y; k--) {
		temp[top_x][k] = temp[top_x][k - 1];
	}
	for (int k = top_x; k > 0; k--) {
		temp[k][top_y] = temp[k - 1][top_y];
	}

	temp[1][top_y] = save_locate_value;
	temp[top_x][top_y] = 0;



	/*아래쪽 공기 청정*/

	for (int k = down_x; k < R - 1; k++) {
		temp[k][down_y] = temp[k + 1][down_y];
	}
	for (int k = down_y; k < C - 1; k++) {
		temp[R - 1][k] = temp[R - 1][k+1];
	}
	for (int k = R - 1; k > down_x; k--) {
		temp[k][C - 1] = temp[k - 1][C - 1];
	}
	for (int k = C - 1; k > down_y; k--) {
		temp[down_x][k] = temp[down_x][k - 1];
	}

	temp[down_x][down_y+1] = 0;
	temp[top_x][top_y] = -1;
	temp[down_x][down_y] = -1;
	
}


void airCleanerWorking() {
	movingDust();

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			A[i][j] = temp[i][j];
			temp[i][j] = 0;
		}
	}

}
int main() {
	cin >> R >> C >> T;

	A = new int *[R];
	temp = new int *[R];
	for (int i = 0; i < R; i++) {
		A[i] = new int[C];
		temp[i] = new int[C];
	}


	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> A[i][j];
			temp[i][j] = 0;
			if (A[i][j] == -1) {
				airCleaner_location.push_back(make_pair(i, j));
			}
		}
	}



	while (T--)
	{
		findDustLocation();
		dustSpread();		
		airCleanerWorking();

	}

	int total_dust_cnt = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (A[i][j] > 0) {
				total_dust_cnt += A[i][j];
			}
		}
	}

	cout << total_dust_cnt;

	for (int i = 0; i < R; i++) {
		delete[] A[i];
		delete[] temp[i];
	}
	delete[] A;
	delete[] temp;


}