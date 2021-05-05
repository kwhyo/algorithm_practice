#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    int size = board.size();
    vector<int> stack(size);//초기화
    
    for(int chance =0; chance<moves.size();chance++){
        int locate = moves[chance]-1;
        for(int walk=0;walk<size;walk++){
            vector<int> this_line = board[walk];
            if(board[walk][locate]!=0){
                if(stack.back()==board[walk][locate]){
                    answer+=2;
                    stack.pop_back();
                }else{
                    stack.push_back(board[walk][locate]);
                }
                
                board[walk][locate]=0;
                walk=size; //끝내기
            }
            
        }
        
    }
    
    
    return answer;
}