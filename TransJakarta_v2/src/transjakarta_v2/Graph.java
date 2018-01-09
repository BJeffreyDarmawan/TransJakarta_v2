/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package transjakarta_v2;

import java.util.*;

/**
 *
 * @author Lenovo
 */
public class Graph {
    Map<String, Node> NodeList;
    
    Graph(){
        NodeList = new HashMap<>();
        
    }
    
    void add_node(Node A){
        NodeList.put(A.id, A);
    }
    
    void add_edge(String A, String B, int line, int weight){
        NodeList.get(A).add_adj(NodeList.get(B), weight, line);
        NodeList.get(B).add_adj(NodeList.get(A), weight, line);
    }
    
//    void add_edge(Node A, Node B, int line, int weight){
//        A.add_adj(NodeList.get(B.id), weight, line);
//        B.add_adj(NodeList.get(A.id), weight, line);
//    }
    
    void show_adjList(){
        //sort by key
        Map<String, Node> treeMap = new TreeMap<>(NodeList);
        
        for (Map.Entry<String, Node> entry : treeMap.entrySet()) {
//            System.out.println("Key : " + entry.getKey()
//				+ " Value : " + entry.getValue());
            Node a = (Node) entry.getValue();
            Iterator<Adj> iterator = a.AdjList.iterator();
            System.out.println(entry.getValue().id);
            while(iterator.hasNext()){
                System.out.print(iterator.next().tujuan.id + ", ");
            }
            System.out.println("");
        }
        
    }
    
    
    
}
