#include <iostream>
#include <tuple>

using namespace std;

int N;
int **grid;


int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

int out_range_total;
bool isRange(int x, int y) {
	return x >= 0 && x < N&&y >= 0 && y < N;
}
void sandMove(int direction, int x, int y) {
	if (direction == 0) {
		int sand_dx[9] = { -1,1,-2,-1,1,2,-1,1,0 };
		int sand_dy[9] = { 1,1,0,0,0,0,-1,-1,-2 };
		double sand_persent[9] = { 1,1,2,7,7,2,10,10,5 };

		int current_send = grid[x][y];
		int move_send = 0;

		for (int i = 0; i < 9; i++) {
			int newX = x + sand_dx[i];
			int newY = y + sand_dy[i];
			int calculate_send = (int)((current_send)*(sand_persent[i] / 100)); //값 맞는지 찍어보기
			if (isRange(newX, newY)) {
				grid[newX][newY] += calculate_send;
			}
			else {
				out_range_total += calculate_send;
			}
			move_send += calculate_send;
		}
		int a_x = x ; int a_y = y-1;
		if (isRange(a_x, a_y)) {
			grid[a_x][a_y] += current_send - move_send;
			grid[x][y] = 0;
		}
		else {
			out_range_total += current_send - move_send;
			grid[x][y] = 0;
		}
	}
	else if (direction == 1) {
		int sand_dx[9] = { -1,-1,0,0,0,0,1,1,2 };
		int sand_dy[9] = { -1,1,-2,-1,1,2,-1,1,0 };
		double sand_persent[9] = { 1,1,2,7,7,2,10,10,5 };

		int current_send = grid[x][y];
		int move_send = 0;

		for (int i = 0; i < 9; i++) {
			int newX = x + sand_dx[i];
			int newY = y + sand_dy[i];
			int calculate_send = (int)((current_send)*(sand_persent[i] / 100)); //값 맞는지 찍어보기
			if (isRange(newX, newY)) {
				grid[newX][newY] += calculate_send;
			}
			else {
				out_range_total += calculate_send;
			}
			move_send += calculate_send;
		}
		int a_x = x + 1; int a_y = y;
		if (isRange(a_x, a_y)) {
			grid[a_x][a_y] += current_send - move_send;
			grid[x][y] = 0;
		}
		else {
			out_range_total += current_send - move_send;
			grid[x][y] = 0;
		}
	}else if (direction == 2) {
		int sand_dx[9] = { -1,1,-2,-1,1,2,-1,1,0 };
		int sand_dy[9] = { -1,-1,0,0,0,0,1,1,2 };
		double sand_persent[9] = { 1,1,2,7,7,2,10,10,5 };

		int current_send = grid[x][y];
		int move_send = 0;

		for (int i = 0; i < 9; i++) {
			int newX = x + sand_dx[i];
			int newY = y + sand_dy[i];
			int calculate_send = (int)((current_send)*(sand_persent[i] / 100)); //값 맞는지 찍어보기
			if (isRange(newX, newY)) {
				grid[newX][newY] += calculate_send;
			}
			else {
				out_range_total += calculate_send;
			}
			move_send += calculate_send;
		}
		
		int a_x = x; int a_y = y+1;
		if (isRange(a_x, a_y)) {
			grid[a_x][a_y] += current_send - move_send;
			grid[x][y] = 0;
		}
		else {
			out_range_total += current_send - move_send;
			grid[x][y] = 0;
		}
		
	}else if (direction == 3) {
		int sand_dx[9] = { 1,1,0,0,0,0,-1,-1,-2 };
		int sand_dy[9] = { -1,1,-2,-1,1,2,-1,1,0 };
		double sand_persent[9] = { 1,1,2,7,7,2,10,10,5 };

		int current_send = grid[x][y];
		int move_send = 0;

		for (int i = 0; i < 9; i++) {
			int newX = x + sand_dx[i];
			int newY = y + sand_dy[i];
			int calculate_send = (int)((current_send)*(sand_persent[i] / 100)); //값 맞는지 찍어보기
			if (isRange(newX, newY)) {
				grid[newX][newY] += calculate_send;
			}
			else {
				out_range_total += calculate_send;
			}
			move_send += calculate_send;
		}
		int a_x = x - 1; int a_y = y;
		if (isRange(a_x, a_y)) {
			grid[a_x][a_y] += current_send - move_send;
			grid[x][y] = 0;
		}
		else {
			out_range_total += current_send - move_send;
			grid[x][y] = 0;
		}
	}
}

int main() {
	cin >> N;
	grid = new int*[N];
	for (int i = 0; i < N; i++) {
		grid[i] = new int[N];
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> grid[i][j];
		}
	}


	out_range_total = 0;
	//1. 토네이도 이동
	int block = 1; int check = 0;

	int x = N / 2;
	int y = N / 2;
	int d = 0;
	while (block < N) {
		/*
		cout << endl << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << grid[i][j]<<" ";
			}
			cout << endl;
		}
		cout << endl<<endl;
		*/


		for (int i = 0; i < block; i++) {

			x = x + dx[d];
			y = y + dy[d];
			sandMove(d, x, y);
			//모래확산(d,x,y) -> 그림상 y위치 좌표에 대해 진행되기 때문
		}
		check += 1;
		d = (d + 1) % 4;

		if (check % 2 == 0) {
			block += 1;
		}
	}
	//
	
	for (int i = 0; i < block-1; i++) {
		//모래확산(d,x,y)
		x = x + dx[d];
		y = y + dy[d];
		sandMove(d, x, y);


	}

	cout << out_range_total;
	for (int i = 0; i < N; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}
