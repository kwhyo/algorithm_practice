#include <iostream>
#include <vector>
#include <tuple>
#include <deque>

using namespace std;

int count_result;
vector<int> total_nums;
vector<int> select_nums;
void DFS(int cnt ,int chk) { //몇개 선택했는지, 고르기로 했는지

	if (cnt == 3) { //3개 뽑았으면 종료
		bool isCheck = false;
		int sum = 0;
		for (int i = 0; i < 3; i++) {
			sum += select_nums[i];
		}

		if (sum % 2 == 0) {
			return;
		}

		for (int i = 3; i < sum; i+=2) {
			if (sum%i == 0) {
				return;
			}
		}

		//여기 까지오면 소수라는 뜻
		count_result += 1;
		return;
	}

	if (chk == total_nums.size())
		return;

	
	select_nums.push_back(total_nums[chk]);
	DFS(cnt + 1, chk + 1);// 고르기로함
	select_nums.pop_back();
	DFS(cnt , chk+1); // 안고르기로함

}



int solution(vector<int> nums) {
	int answer = -1;
	count_result = 0;

	for (int i = 0; i < nums.size(); i++) {
		total_nums.push_back(nums[i]);
	}
	DFS(0, 0);
	answer = count_result;
	return answer;
}
