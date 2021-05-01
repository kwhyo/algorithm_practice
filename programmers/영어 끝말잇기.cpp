#include <string>
#include <vector>
#include <iostream>
#include <map>


using namespace std;

map<string, int> map1;

vector<int> solution(int n, vector<string> words) {
	vector<int> answer;
	int last = words[0].length() - 1;
	char before_last_word = words[0].at(last);
	map1.insert({words[0],0});
	int turn = 1;
	for (int i = 1; i < words.size();i++) {
		if (i%n == 0) { //한바퀴 돌아왔으면 턴 추가
			turn += 1;
		}
		char first = words[i].at(0);
		if (map1.find(words[i]) != map1.end()) { //중복이 있을경우
			answer.push_back((i%n)+1);
			answer.push_back(turn);
			break;
		}
		if (before_last_word != first) { //끝말잇기 실패한 경우
			answer.push_back((i%n) + 1);
			answer.push_back(turn);
			break;
		}
		
		
		map1.insert({ words[i],i%n});
		int last = words[i].length() - 1;
		before_last_word = words[i].at(last);
	}

	if (answer.empty()) {
		answer.push_back(0);
		answer.push_back(0);
	}

	return answer;
}