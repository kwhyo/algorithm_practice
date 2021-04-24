#include <iostream>
#include<tuple>
#include <deque>
#include <queue>

using namespace std;

int N, M, T;

int **grid;
int **before;
deque<int> X_i;
deque<int> D_i;
deque<int> K_i;

queue<int> qu;
double average_circle;

void clearCircle() {
	int left, right;
	int up, down;
	bool isClose = false;
	//인접한 것 지우기
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < M; col++) {
			

			// 양 옆 먼저 검사
			left = col - 1; right = col + 1;
			if (left < 0)
				left += M;
			if (right > M - 1)
				right -= M;

			if (before[row][col] == -1) { //내가 이미 값이 없는 경우 무조건 패스
				continue;
			}
			if (before[row][left] == before[row][col]) { //나랑 왼쪽이랑 같은 경우
				isClose = true;
				grid[row][col] = -1;
				grid[row][left] = -1;
			}
			if (before[row][right] == before[row][col]) {// 나랑 오른쪽 같은 경우
				isClose = true;
				grid[row][col] = -1;
				grid[row][right] = -1;
			}

			//위 아래 검사
			if (row < 1) { // 첫째 줄 :가장 안 쪽 이므로 아래만 검사
				down = row + 1;
				if (before[row][col] == before[down][col]) {// 나랑 아래 같은 경우
					isClose = true;
					grid[row][col] = -1;
					grid[down][col] = -1;
				}
			}
			else if (row == N - 1) {
				up = row - 1;
				if (before[row][col] == before[up][col]) {// 나랑 아래 같은 경우
					isClose = true;
					grid[row][col] = -1;
					grid[up][col] = -1;
				}
			}
			else { //나머지 경우는 위 아래 다 검사
				up = row - 1; down = row + 1;

				if (before[row][col] == before[down][col]) {// 나랑 아래 같은 경우
					isClose = true;
					grid[row][col] = -1;
					grid[down][col] = -1;
				}

				if (before[row][col] == before[up][col]) {// 나랑 아래 같은 경우
					isClose = true;
					grid[row][col] = -1;
					grid[up][col] = -1;
				}
			}

		}
	}


	//인접한게 없을경우 
	if (isClose == false) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (before[i][j] > 0) {
					if (before[i][j] > average_circle) {
						grid[i][j] -= 1;
					}
					else if (before[i][j] < average_circle) {
						grid[i][j] += 1;
					}
				}
				
			}
		}		
	}

}

int main() {
	cin >> N >> M >> T;
	grid = new int *[N];
	before = new int *[N];
	
	//원판 입력 
	for (int i = 0; i < N; i++) {
		grid[i] = new int[M];
		before[i] = new int[M];
		for (int j = 0; j < M; j++) {
			cin >> grid[i][j];			
		}
	}

	//횟수 입력
	for (int i = 0; i < T; i++) {
		int x, d, k;
		cin >> x >> d >> k;
		X_i.push_back(x);
		D_i.push_back(d);
		K_i.push_back(k);
	}

	

	//원판 돌리기
	int this_x, this_d, this_k; //Xi에서 하나 꺼내기.

	while (T--)
	{
		this_x = X_i.front();
		this_k = K_i.front();
		this_d = D_i.front();

		X_i.pop_front();
		D_i.pop_front();
		K_i.pop_front();

		for (int k = 0; k < N; k++) {
			if ((k + 1) % this_x == 0) { //Xi의 배수일때!

				for (int rotate = 0; rotate < this_k; rotate++) { //Ki번 실시
					if (this_d == 1) { //반시계 방향 회전
						int temp = grid[k][0];
						for (int i = 0; i < M - 1; i++) {
							grid[k][i] = grid[k][i + 1];
						}
						grid[k][M - 1] = temp;
					}
					else { //시계방향 회전
						int temp = grid[k][M - 1];
						for (int i = M - 1; i > 0; i--) {
							grid[k][i] = grid[k][i - 1];
						}
						grid[k][0] = temp;
					}
				}


			}
			
		}
		//배열 복사하기. 값 있는 것 평균 구하기
		double total_cnt = 0, total_sum = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (grid[i][j] != -1) {
					total_cnt++;
					total_sum += grid[i][j];
				}
				before[i][j] = grid[i][j];
			}
		}
		average_circle = total_sum / total_cnt;

	
		
		//인접 한 것 삭제
		clearCircle();

	

	}

	
	int total_last=0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (grid[i][j] > 0) {
				total_last += grid[i][j];
			}
		}
	}

	cout << total_last;
	/*
	cout << endl << endl;
	for (int p = 0; p < N; p++) {
		for (int q = 0; q < M; q++) {
			cout << grid[p][q] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	*/
	for (int i = 0; i < N; i++) {
		delete[] grid[i];
		delete[] before[i];
	}
	delete[] grid;
	delete[] before;
}