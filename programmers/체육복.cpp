#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    int get_person = 0;
    
    int student[35] ={0,};
    
    for(int i = 0; i<lost.size();i++){
        student[lost[i]]-=1;   
    }
    for(int k=0;k<reserve.size();k++){
        student[reserve[k]]+=1;
    }
    
  
    for(int i=1;i<=n;i++){
        if(student[i]<0){
            if(student[i-1]==1){
                student[i]=student[i-1]=0;
            }else if(student[i+1]==1){
                student[i]=student[i+1]=0;
            }
        }
    }
    
    for(int k =1;k<=n;k++){
        if(student[k]>=0)
            answer++;
    }
    
    return answer;
}