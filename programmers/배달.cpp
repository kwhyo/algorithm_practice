#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

int INF = 12345678;

int solution(int N, vector<vector<int> > road, int K) {
	int answer = 0;
	//번호, 번호, 거리 
	vector<pair<int, int>>  graph[50];
	vector<int> distance (N, INF);
	
	for (int i = 0; i < road.size(); i++) {
		vector<int> input_road = road[i];
		
		int E1 = input_road[0]-1;
		int E2 = input_road[1]-1;
		int dist = input_road[2];
		
		graph[E1].push_back(make_pair(E2, dist));
		graph[E2].push_back(make_pair(E1, dist));
	}
	
	
	distance[0] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push({ 0,0 });

	//다익스트라,,,
	while (!pq.empty())
	{
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (distance[here] < cost) continue;

		for (int i = 0; i < graph[here].size(); i++) {
			int next = graph[here][i].first;
			int nextDist = cost + graph[here][i].second;
			if (nextDist < distance[next]) {
				distance[next] = nextDist;
				pq.push({ -nextDist,next });
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (distance[i] <= K) {
			answer += 1;
		}
	}

	

	

	

	return answer;
}
