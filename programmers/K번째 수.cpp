#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> sorting(vector<int> input){
    int i, j;
    for(i=1; i<input.size(); i++){
        int key = input[i];
        
        for(j=i-1; j>=0 && input[j]>key;j--){
            input[j+1] = input[j];
        }
        
        input[j+1] = key;
       
    }
    return input;
}


vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for(int total=0;total<commands.size();total++){
        vector<int> new_array = commands[total];
        int start = new_array[0];
        int end = new_array[1];
        int location = new_array[2];
        vector<int> pick_array;
        
        for(int k=start-1;k<end;k++){
            //분리
            pick_array.push_back(array[k]);
        }
         //정렬
        vector<int> hello = sorting(pick_array);
        //추출
        answer.push_back(hello[location-1]);
    
    }
    
   
    
    return answer;
}