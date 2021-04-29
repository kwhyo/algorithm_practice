#include <iostream>
#include <vector>
#include <tuple>
#include <deque>
#include <algorithm>

using namespace std;

int count_max;
int total_budget;
vector<int> total_d;




int solution(vector<int> d, int budget) {
	int answer = -1;
	count_max = 0;

	for (int i = 0; i < d.size(); i++) {
		total_d.push_back(d[i]);
	}

	sort(total_d.begin(), total_d.end()); //정렬하면 예산 넘는 뒤부터는 안봐도 됨.
	total_budget = budget;

	int temp = 0;
	int cnt = 0;
	for (int i = 0; i < total_d.size(); i++) {
		if (temp + total_d[i] <= budget) {
			temp += total_d[i];
			cnt += 1;
		}
		else {
			break;
		}
	}
	

	
	answer = cnt;
	return answer;
}
