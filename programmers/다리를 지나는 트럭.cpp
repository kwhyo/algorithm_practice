#include <iostream>
#include <vector>
#include <tuple>
#include <deque>

using namespace std;

deque<int> passed_truck;
deque<pair<int, int>> nonpassed_truck;
deque<pair<int, int>> moving_truck;
int sum_truck() {
	int sum = 0;
	for (int i = 0; i < moving_truck.size(); i++) {
		sum += moving_truck[i].second;
	}
	return sum;
}

int solution(int bridge_length, int weight, vector<int> truck_weights) {

	int answer = 1;
	

	for (int i : truck_weights) {
		nonpassed_truck.push_back(make_pair(bridge_length, i));
	}

	while (passed_truck.size() < truck_weights.size()) {
		answer += 1;
		int next_car = nonpassed_truck.front().second;
		if (!nonpassed_truck.empty()) {
			if (sum_truck() + next_car <= weight) {				
				moving_truck.push_back(nonpassed_truck.front());
				nonpassed_truck.pop_front();
			}
		}
		
		if (!moving_truck.empty()) {			
		
			for (int i = 0; i < moving_truck.size(); i++) {
				moving_truck[i].first -= 1; // 1칸 이동
			}
			if (moving_truck.front().first == 0) {//다 이동했으면 제거, pass에 추가
				passed_truck.push_back(moving_truck.front().second);
				moving_truck.pop_front();				
			}
		}
	}


	return answer;
}
