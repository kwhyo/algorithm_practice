#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
	int answer = 0;

	

	
	sort(B.begin(), B.end());
	sort(A.begin(), A.end());
	int N = A.size();
	int i = 0, j = 0;
	while (i < N && j < N) {
		if (A[i] < B[j]) {
			i++; j++;
			answer++;
		}
		else {
			j++;
		}
	}

	

	return answer;
}