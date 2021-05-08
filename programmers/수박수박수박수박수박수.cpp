#include <string>
#include <vector>

using namespace std;

string solution(int n) {
    string answer = "";
    for(int k =0; k<n;k++){
        if(k%2==0)
            answer+="수";
        else
            answer+="박";
    }
    return answer;
}