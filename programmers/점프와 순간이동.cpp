#include <iostream>
using namespace std;

int solution(int n)
{
	int ans = 0;

	int cur_N = n;

	while (cur_N > 0) {
		if (cur_N % 2 != 0) { //홀수 일때는 점프를 해야하는 상황.
			cur_N -= 1;
			ans += 1;
		}
		//홀수 아닐때는 순간이동 하면 되니까 횟수 추가 안해도됨.
		cur_N /= 2; 
	}

	return ans;
}