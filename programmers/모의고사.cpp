class Solution {
    public int[] solution(int[] answers) {
        
        int[] pick_1 = {1,2,3,4,5};
        int[] pick_2 = {2,1,2,3,2,4,2,5};
        int[] pick_3 = {3,3,1,1,2,2,4,4,5,5};
        
        int supoza2_think=0,supoza3_think=0;
        int supoza1 = 0, supoza2 = 0,supoza3 = 0;
        int[] points = {0,0,0};
        for(int k = 0; k<answers.length;k++){
            int this_problem = answers[k];
            if((k%5+1) == this_problem){
                points[0]+=1;
            }
            
            supoza2_think = pick_2[k%8];
            if(supoza2_think == this_problem){
                 points[1]+=1;
            }
            supoza3_think = pick_3[k%10];
            if(supoza3_think == this_problem){
                 points[2]+=1;
            }
            
        }
        int max_val = 0;
        
        //max값은?
        for(int i = 0;i<3;i++){
            if(points[i]>max_val){
                max_val = points[i];
            }
        }
        //max값을 가진 사람 수?
        int count = 0;
        for(int i = 0;i<3;i++){
            if(points[i]==max_val){
                count++;
            }
        }
        //출력
        int[] answer = new int[count];
        System.out.println(count);
        count = 0;
        
        for(int i = 0;i<3;i++){
            if(points[i]==max_val){
                answer[count++] = i+1;
            }
        }
        return answer;
    }
}