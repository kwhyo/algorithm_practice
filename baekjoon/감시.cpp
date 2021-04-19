#include <iostream>
#include <tuple>
#include <vector>
#include <climits>
#include <deque>

using namespace std;


int N, M, K;

int ***input_grid;


int ***new_grid;
int **temp_grid;


vector<int> CCTV_num;
vector<pair<int,int>> CCTV_locate;
int minimumVal;
bool isRange(int x ,int y) {
	return x >= 0 && x < N&&y >= 0 && y < M;
}

//윗방향 탐색 -> a 아랫방향 탐색 -> b 


void CCTV_look(int k,int x, int y, char direction) {

	if (direction == 'N') {
		//북쪽방향
		for (int i = x - 1; i >= 0; i--) {
			if (new_grid[k][i][y] == 6) { //벽 만나면 중단
				break;
			}
			new_grid[k][i][y] = 9; //볼수있는 공간 9로 설정
		}
	}
	else if (direction == 'S') {
		//남쪽방향
		for (int i = x + 1; i < N; i++) {
			if (new_grid[k][i][y] == 6) {
				break;
			}
			new_grid[k][i][y] = 9;
		}
	}
	else if (direction == 'W') {
		//서쪽방향
		for (int i = y - 1; i >= 0; i--) {
			if (new_grid[k][x][i] == 6) {
				break;
			}
			new_grid[k][x][i] = 9;
		}
	}
	else if (direction == 'E') {
		//동쪽방향
		for (int i = y + 1; i < M; i++) {
			if (new_grid[k][x][i] == 6) {
				break;
			}
			new_grid[k][x][i] = 9;
		}
	}

	/**/
}

int countCantSee(int k) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (new_grid[k][i][j] == 0 ) {
				cnt+=1;
			}
		}
	}
	return cnt;
}

void NewtoBefore(int k) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			new_grid[k+1][i][j] = new_grid[k][i][j];
		}
	}
}

void func(int k) {
	if (k == CCTV_num.size()) {
		int min = countCantSee(k);		
		if (min < minimumVal) {
			minimumVal = min;
		}
		/*
		cout << endl << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << new_grid[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;*/
		return;
	}

	int CCTV = CCTV_num[k];
	int x, y;
	tie(x, y) = CCTV_locate[k];


	if (CCTV == 1) {
		
		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1, x, y, 'N');
		func(k + 1);
		

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'S');
		func(k + 1);

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1, x, y, 'W');
		func(k + 1);
		

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1, x, y, 'E');
		func(k + 1);
	}
	else if (CCTV == 2) {

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'N');		
		CCTV_look(k+1,x, y, 'S');
		func(k + 1);

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'W');
		CCTV_look(k+1,x, y, 'E');
		func(k + 1);
	}
	else if (CCTV == 3) {
		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'N');
		CCTV_look(k+1,x, y, 'E');
		func(k + 1);

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'N');
		CCTV_look(k+1,x, y, 'W');
		func(k + 1);

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'W');
		CCTV_look(k+1,x, y, 'S');
		func(k + 1);

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'E');
		CCTV_look(k+1,x, y, 'S');
		func(k + 1);
	}
	else if (CCTV == 4) {
		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'N');
		CCTV_look(k+1,x, y, 'W');
		CCTV_look(k+1,x, y, 'E');
		func(k + 1);

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'N');
		CCTV_look(k+1,x, y, 'W');
		CCTV_look(k+1,x, y, 'S');
		func(k + 1);

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'W');
		CCTV_look(k+1,x, y, 'S');
		CCTV_look(k+1,x, y, 'E');
		func(k + 1);

		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'N');
		CCTV_look(k+1,x, y, 'E');
		CCTV_look(k+1,x, y, 'S');
		func(k + 1);
	}
	else if (CCTV == 5) {
		NewtoBefore(k); //k+1 에 k 복사
		CCTV_look(k+1,x, y, 'N');
		CCTV_look(k+1,x, y, 'W');
		CCTV_look(k+1,x, y, 'E');
		CCTV_look(k+1,x, y, 'S');
		func(k + 1);	
	}

	
}


int main() {
	cin >> N >> M ;

	input_grid = new int**[9];
	new_grid = new int**[9];
	

	for (int i = 0; i < 9; i++) {
		input_grid[i] = new int*[N];
		new_grid[i] = new int*[N];		
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < N; j++) {
			input_grid[i][j] = new int[M];
			new_grid[i][j] = new int[M];
		}
		
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> input_grid[0][i][j];
			new_grid[0][i][j] = input_grid[0][i][j];
			if (input_grid[0][i][j] > 0 && input_grid[0][i][j] != 6) {
				CCTV_num.push_back(input_grid[0][i][j]);
				CCTV_locate.push_back(make_pair(i, j));
			}
		}
	}

	minimumVal = N*M;

	func(0);
	cout << minimumVal;
	

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < N; j++) {
			delete[] input_grid[i][j];
			delete[] new_grid[i][j];			
		}

	}

	for (int j = 0; j < 9; j++) {
		delete[] input_grid[j];
		delete[] new_grid[j];
	}
	delete[] input_grid;
	delete[] new_grid;
}