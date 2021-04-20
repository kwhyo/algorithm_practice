#include <iostream>
#include <tuple>
#include <algorithm>
#include <deque>


using namespace std;

int N, K;


int main() {
	cin >> N >> K;

	int robot_cnt = 1;
	int **belt_grid = new int*[2];
	int **robot_grid = new int*[2];

	for (int i = 0; i < 2; i++) {
		belt_grid[i] = new int[N];
		robot_grid[i] = new int[N];
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			cin >> belt_grid[i][j];
			robot_grid[i][j] = -1;
		}
	}

	deque<int> robot_list;

/*
	cout << endl << endl;
	for (int j = 0; j < N; j++) {
		cout << belt_grid[0][j] << " ";
	}
	cout << endl;
	for (int j = N - 1; j >= 0; j--) {
		cout << belt_grid[1][j] << " ";
	}
	cout << endl << endl;*/


	int count = 0;
	int answer = 0;
/*
	cout << endl << endl;
	for (int j = 0; j < N; j++) {
		cout << belt_grid[0][j] << " ";
	}
	cout << endl;
	for (int j = N - 1; j >= 0; j--) {
		cout << belt_grid[1][j] << " ";
	}
	cout << endl << endl;*/

	while(1) {
		answer += 1;
		//ȸ���ϱ�(�Ƹ� �κ��� ���� ȸ������ߴ�)
		int temp1 = belt_grid[0][N - 1];//N
		int robot_temp1 = robot_grid[0][N - 1];//N
		for (int i = N - 1; i > 0; i--) {
			belt_grid[0][i] = belt_grid[0][i - 1];
			robot_grid[0][i] = robot_grid[0][i - 1];
		}

		int temp2 = belt_grid[1][N - 1]; //2N
		int robot_temp2 = robot_grid[1][N - 1]; //2N
		for (int i = N - 1; i > 0; i--) {
			belt_grid[1][i] = belt_grid[1][i - 1];
			robot_grid[1][i] = robot_grid[1][i - 1];
		}
		belt_grid[0][0] = temp2;
		belt_grid[1][0] = temp1;

		robot_grid[0][0] = robot_temp2;
		robot_grid[1][0] = robot_temp1;

		if (robot_grid[0][N - 1] != -1) { //�κ��� �������� ��ġ�� ������!
			robot_grid[0][N - 1] = -1;			
		}

		int erase = 0;

		for (int y = N - 2; y >= 0; y--) { //���ٸ� �ϸ��, N-1�� ĭ���� �κ������� ����..
			if (robot_grid[0][y] > 0) {
				if (robot_grid[0][y + 1] == -1 && belt_grid[0][y + 1] > 0) {
					belt_grid[0][y + 1] -= 1; //������ ������
					robot_grid[0][y + 1] = robot_grid[0][y]; //�κ� �̵���Ű��
					robot_grid[0][y] = -1;
					if (y + 1 == N - 1) { //�ű� ĭ�� N�̴�,,?
						erase = 1;
						robot_grid[0][y + 1] = -1;
					}
				}

			}
		}
		
		


		//�κ� �ø���
		if (robot_grid[0][0] == -1 && belt_grid[0][0]>0) { 
			belt_grid[0][0] -= 1;
			int robot = robot_cnt++;
			robot_grid[0][0] = robot;
		}


		//������ 0 ���� ����
		count = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < N; j++) {
				if (belt_grid[i][j] == 0)
					count += 1;
			}
		}

		
		
		if (count >= K) {
			break;
		}
		
	}
	

	cout<<answer;
	delete[] belt_grid[0];
	delete[] belt_grid[1];

	delete belt_grid;

}