#include <iostream>
#include <string>

using namespace std;

class Dot
{
public:
	int val;
	bool up;
	bool down;
	bool left;
	bool right;
	Dot();
	~Dot();

private:

};

Dot::Dot()
{
	val = 0;
	up = false;
	down = false;
	left = false;
	right = false;
}

Dot::~Dot()
{
}

Dot grid[11][11];

int dx[4] = {-1,1,0,0}; //up,down,right,left 순
int dy[4] = {0,0,1,-1};

bool isRange(int x, int y) {
	return x >= 0 && x < 11 && y >= 0 && y < 11;
}

int solution(string dirs) {

	int x = 5, y = 5;
	
	int next_x, next_y;
	int answer = 0;

	for (int i = 0; i < dirs.length(); i++) {
		char this_d = dirs.at(i);
		if (this_d == 'U') {
			next_x = x + dx[0];
			next_y = y + dy[0];
			if (isRange(next_x, next_y)) {
				if (grid[x][y].up == false && grid[next_x][next_y].down==false) {// 아직 위로 간 적 없음
					answer += 1;
					grid[x][y].up = true;
					grid[next_x][next_y].down == true;
				}
				grid[next_x][next_y].val = 1;
				x = next_x; y = next_y;
			}
		}
		else if (this_d == 'D') {
			next_x = x + dx[1];
			next_y = y + dy[1];
			if (isRange(next_x, next_y)) {
				if (grid[x][y].down == false && grid[next_x][next_y].up == false) {// 아직 위로 간 적 없음
					answer += 1;
					grid[x][y].down = true;
					grid[next_x][next_y].up == true;
				}
				grid[next_x][next_y].val = 1;
				x = next_x; y = next_y;
			}
		
		}
		else if(this_d == 'R') {
			next_x = x + dx[2];
			next_y = y + dy[2];
			if (isRange(next_x, next_y)) {
				if (grid[x][y].right == false && grid[next_x][next_y].left == false) {// 아직 위로 간 적 없음
					answer += 1;
					grid[x][y].right = true;
					grid[next_x][next_y].left == true;
				}
				grid[next_x][next_y].val = 1;
				x = next_x; y = next_y;
			}
		}
		else if (this_d == 'L') {
			next_x = x + dx[3];
			next_y = y + dy[3];
			if (isRange(next_x, next_y)) {
				if (grid[x][y].left == false && grid[next_x][next_y].right == false) {// 아직 위로 간 적 없음
					answer += 1;
					grid[x][y].left = true;
					grid[next_x][next_y].right == true;
				}
				grid[next_x][next_y].val = 1;
				x = next_x; y = next_y;
			}
		}

	}

	
	return answer;
}