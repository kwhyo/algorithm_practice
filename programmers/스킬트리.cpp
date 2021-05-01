#include <string>
#include <vector>
#include <iostream>
#include <map>


using namespace std;


map <char,int>  map1;

int solution(string skill, vector<string> skill_trees) {
	int answer = 0;
	for (int i = 0; i < skill.length(); i++) {
		map1.insert({skill.at(i), i});
	}


	for (int i = 0; i < skill_trees.size(); i++) {
		bool isPossibleSkill = true;
		string skill_1 = skill_trees[i];
		int this_turn = 0;
		for (int j = 0; j < skill_1.length(); j++) {
			if (map1.find(skill_1.at(j)) != map1.end()) {//스킬에 들어있는 거면
				if (skill.at(this_turn) == skill_1.at(j)) { //이번 순서해당하는게 맞으면
					this_turn += 1;
				}
				else {
					isPossibleSkill = false;
					break;
				}
			}
		}
		if (isPossibleSkill == true) {
			answer += 1;
		}
	}

	return answer;
}