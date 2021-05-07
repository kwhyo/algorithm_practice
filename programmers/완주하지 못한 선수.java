import java.util.LinkedList;
class Solution { 
    
    public String solution(String[] participant, String[] completion) {
        String answer = "";
        HashTable h1 = new HashTable(participant.length);
        
        
        for(int i=0;i<completion.length;i++){
            h1.put(completion[i],completion[i]);
        }
        for(int i=0;i<participant.length;i++){
            if(h1.get(participant[i])==0){
                answer = participant[i];
                break;
            }
        }
        
        
        return answer;
    }
}

class HashTable{
    class Node{
        String key;
        String value;
        int check = 0;
        
        public Node(String key, String value){
            this.key = key;
            this.value = value;
        }
        String getValue(){
            return value;
        }
        void setValue(String value){
            this.value = value;
        }
        
    }
    
    
    LinkedList<Node>[] data;
    HashTable(int size){
        this.data = new LinkedList[size];
    }
    
    int getHashCode(String key){
        int hashcode = 0;
        for(char c : key.toCharArray()){
            hashcode+=c;
        }
       return hashcode;
    }
    
    int convertToIndex(int code){
        return code%data.length;
    }
    
    Node searchNode(LinkedList<Node> list, String key){
       if(list==null) return null;
        for(Node node:list){
            if(node.key.equals(key)){
                return node;
            }
        }
        return null;
        
    }
    
    int get(String key){
        int code = getHashCode(key);
        int index = convertToIndex(code);
        LinkedList<Node> list = data[index];
    
        Node node = searchNode(list, key);
        if(node == null){
            return 0;
        }else{
            list.remove(node);
            return 1;
        }
        
    }
    
    void put(String key, String value){
        int code = getHashCode(key);
        int index = convertToIndex(code);
        LinkedList<Node> list = data[index];
        if(list==null){
            list = new LinkedList<Node>();
            data[index] = list;
        }
        
         Node new_node = new Node(key,value);
         list.add(new_node);
        /*
        Node node = searchNode(list,key);
        if(node==null){
            Node new_node = new Node(key,value);
            list.add(new_node);
        }else{
            node.setValue(value);
        }*/
       
     
    
    }
    
}