#include <iostream>
#include <algorithm>

using namespace std;

class GridUnit
{
public:
	int fish_num;
	int fish_direct;
	bool isShark;
	int shark_direct;

	GridUnit();
	~GridUnit();

private:

};

GridUnit::GridUnit()
{
	fish_num = 0;
	fish_direct = 0;
	isShark = false;
	shark_direct = 0;
}

GridUnit::~GridUnit()
{
}


GridUnit grid[4][4];
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };
int max_eat;



void DFS(int total_eat) {
	GridUnit BeforeGrid[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			BeforeGrid[i][j].fish_num = grid[i][j].fish_num;
			BeforeGrid[i][j].fish_direct = grid[i][j].fish_direct;
			BeforeGrid[i][j].isShark = grid[i][j].isShark;
			BeforeGrid[i][j].shark_direct = grid[i][j].shark_direct;

		}
	}


	//물고기 이동
	for (int fishNum = 1; fishNum <= 16; fishNum++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (fishNum == grid[i][j].fish_num) {

					int x = i; int y = j; int d = grid[i][j].fish_direct;
					for (int direct = 0; direct < 8; direct++) {
						int newD = (d + direct) % 8;
						int newX = x + dx[newD]; int newY = y + dy[newD];
						if (newX >= 0 && newX < 4 && newY >= 0 && newY<4 && !grid[newX][newY].isShark) {
							
							grid[i][j].fish_num = grid[newX][newY].fish_num;
							grid[i][j].fish_direct = grid[newX][newY].fish_direct;
							grid[newX][newY].fish_num = fishNum;
							grid[newX][newY].fish_direct = newD;
							break;
						}
					}
					i = 4; j = 4;
				}
			}
		}
	}


	//상어이동
	bool check = false;
	int sharkX, sharkY ,sharkD;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (grid[i][j].isShark) {
				sharkX = i; sharkY = j; sharkD = grid[i][j].shark_direct;
				i = 4; j = 4;
			}
		}
	}

	for (int i = 1; i <= 3; i++) {
		int nextX = sharkX + dx[sharkD] * i;
		int nextY = sharkY + dy[sharkD] * i;

		if (nextX >= 0 && nextX < 4 && nextY >= 0 && nextY<4) {
			if (grid[nextX][nextY].fish_num != 0) {
				GridUnit GU = grid[nextX][nextY];
				check = true;
				int eatFish = grid[nextX][nextY].fish_num;
				//잡아먹기			
				grid[nextX][nextY].isShark = true;
				grid[nextX][nextY].shark_direct = grid[nextX][nextY].fish_direct;
				grid[nextX][nextY].fish_num = 0;
				grid[nextX][nextY].fish_direct = 0;

				grid[sharkX][sharkY].isShark = false;
				grid[sharkX][sharkY].shark_direct = 0;				

				// 다음 판 진행
				DFS(total_eat + eatFish);

				//잡아 먹기 취소
				check = false;
				grid[nextX][nextY].isShark = false;
				grid[nextX][nextY].shark_direct = GU.shark_direct;
				grid[nextX][nextY].fish_num = GU.fish_num;
				grid[nextX][nextY].fish_direct = GU.fish_direct;

				grid[sharkX][sharkY].isShark = true;
				grid[sharkX][sharkY].shark_direct = sharkD;
				
			}
		}
		else {
			break;
		}

	}

	if (check == false) { //상어 이동 못함
		if (total_eat > max_eat) {
			max_eat = total_eat;
		}
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			grid[i][j].fish_num = BeforeGrid[i][j].fish_num;
			grid[i][j].fish_direct = BeforeGrid[i][j].fish_direct;
			grid[i][j].isShark = BeforeGrid[i][j].isShark;
			grid[i][j].shark_direct = BeforeGrid[i][j].shark_direct;

		}
	}


}





int main() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0;  j< 4; j++) {
			int num, direct;
			cin >> num >> direct;
			grid[i][j].fish_num = num;
			grid[i][j].fish_direct = direct-1;
		}
	}

	

	int eatFish = grid[0][0].fish_num;
	//잡아먹기			
	grid[0][0].isShark = true;
	grid[0][0].shark_direct = grid[0][0].fish_direct;
	grid[0][0].fish_num = 0;
	grid[0][0].fish_direct = 0;

	max_eat = eatFish;
	// 다음 판 진행
	DFS(eatFish);

	cout << max_eat;
}
