#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <climits>

using namespace std;
int **inputGrid;
int **newGrid;
int **length;
bool **visited;

queue<pair<int, int>> qu;

int N, M;
int babySharkSize;
pair<int, int> babyShark_location;
vector<pair<int, int>> smallFish_location;

int totalSecond;
int babySharkEatCnt;

bool isRange(int x, int y) {
	return x >= 0 && x < N&&y >= 0 && y < N;
}

bool isThereSmallFish() {
	smallFish_location.clear(); //이전 기록은 비워주기.

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (newGrid[i][j]>0 && newGrid[i][j] < babySharkSize) {
				smallFish_location.push_back(make_pair(i, j));
			}
		}
	}
	if (smallFish_location.size()>0)
		return true;
	else
		return false;
}


bool canGo(int x, int y) {
	if (!isRange(x, y)) {
		return false;
	}
	else if (newGrid[x][y]>babySharkSize || length[x][y]>0) { //아기상어보다 크거나, 이미 들렸으면 못감
		return false;
	}
	else {
		return true;
	}
}

void BFS() {
	int x, y;
	int newX, newY;
	int dx[4] = { -1,1,0,0 };
	int dy[4] = { 0,0,-1,1 };
	while (!qu.empty())
	{
		tie(x, y) = qu.front();
		qu.pop();

		for (int i = 0; i < 4; i++) {
			newX = x + dx[i];
			newY = y + dy[i];
			if (canGo(newX, newY)) {
				qu.push(make_pair(newX, newY));
				length[newX][newY] = length[x][y] + 1;

			}
		}

	}
}

bool eatFish() {
	int minX, minY;
	tie(minX, minY) = babyShark_location;

	int minDist = INT_MAX;

	int x, y;
	for (int i = 0; i < smallFish_location.size(); i++) {
		tie(x, y) = smallFish_location[i];
		if (length[x][y] > 0 && length[x][y]<minDist) { // 이동가능하고, 최소거리일때
			minX = x;
			minY = y;
			minDist = length[x][y];
		}
	}
	int babyShark_X, babyShark_Y;
	tie(babyShark_X, babyShark_Y) = babyShark_location;
	if (minX == babyShark_X && minY == babyShark_Y) { //최소 거리로 이동 못했다는 소리,,,
		return false;
	}


	//원래 상어가 있었던 공간은 0으로 비워주기
	newGrid[babyShark_X][babyShark_Y] = 0;


	totalSecond += length[minX][minY]; // 이동 시간 더해주기
	babyShark_location = make_pair(minX, minY); //상어 위치 조정
	babySharkEatCnt += 1; //상어 먹은양 더해주기
	if (babySharkEatCnt == babySharkSize) { //상어먹은양 같아지면 사이즈 올라감
		babySharkSize += 1;
		babySharkEatCnt = 0;
	}
	newGrid[minX][minY] = 0;

	//length는 초기화 해주기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			length[i][j] = -1;
		}
	}
	/*
	for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	cout << newGrid[i][j];
	}
	cout << endl;
	}

	cout << endl<<totalSecond<<endl;
	*/

	return true;
}


bool babySharkStart() {
	if (isThereSmallFish() == true) {
		int x, y;
		tie(x, y) = babyShark_location;
		qu.push(babyShark_location);
		length[x][y] = 0;
		BFS();
		if (eatFish() == true) {
			return true;
		}
		else {
			return false;
		}

	}
	else {
		return false;
	}
}

void findSharkLocation() {
	//처음 상어 위치 찾기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (newGrid[i][j] == 9) {
				babyShark_location = make_pair(i, j);
				return;
			}
		}
	}
}

int main() {
	cin >> N;
	inputGrid = new int *[N];
	newGrid = new int*[N];
	length = new int*[N];
	for (int i = 0; i < N; i++) {
		inputGrid[i] = new int[N];
		newGrid[i] = new int[N];
		length[i] = new int[N];
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> inputGrid[i][j];
			newGrid[i][j] = inputGrid[i][j];
			length[i][j] = -1;
		}
	}

	totalSecond = 0;
	babySharkEatCnt = 0;
	babySharkSize = 2;
	findSharkLocation();


	while (true)
	{
		if (babySharkStart() == false) {
			break;
		}
	}

	cout << totalSecond;


	for (int i = 0; i < N; i++) {
		delete[] inputGrid[i];
		delete[] newGrid[i];
	}
	delete newGrid;

}