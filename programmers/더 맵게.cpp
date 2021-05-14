#include <string>
#include <vector>
#include <queue>


using namespace std;

int solution(vector<int> scoville, int K) {
	priority_queue<int> scovile_list;
	int answer = 0;
	for (int i = 0; i < scoville.size(); i++) {
		
		scovile_list.push(-1 * scoville[i]);
		
	}
	int minus_k = -1 * K;
	while (scovile_list.top() > minus_k)
	{
		
		int smallest = scovile_list.top();
		scovile_list.pop();

		if (scovile_list.empty()) { //새로운 섞은 음식 만들 수 없음.
			answer = -1;
			break;
		}

		int next_smallest = scovile_list.top();
		scovile_list.pop();

		int new_scovile = smallest + (next_smallest * 2);
		scovile_list.push(new_scovile);
		answer += 1;

	}
	return answer;
}