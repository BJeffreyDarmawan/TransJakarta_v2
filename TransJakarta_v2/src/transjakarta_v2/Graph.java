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
    
    void add_edge(String A, String B, int weight, int line){
        NodeList.get(A).add_adj(B, weight, line);
        NodeList.get(B).add_adj(A, weight, line);
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
                System.out.print(iterator.next().tujuan + ", ");
            }
            System.out.println("");
        }
        
    }
    
    void find_route(String from, String dest){
        
        //Map<String, Integer> Distance = new HashMap<>();
        PriorityQueue<Distance> Dist = new PriorityQueue<>();
        Distance temp;
        
        
        for (Map.Entry<String, Node> entry : NodeList.entrySet()) {
//            System.out.println("Key : " + entry.getKey()
//				+ " Value : " + entry.getValue());
            if(!entry.getKey().equals(dest)) {
                temp = new Distance(entry.getKey(), Integer.MAX_VALUE);
                Dist.add(temp);
            }
            else {
                temp = new Distance(entry.getKey(), 0);
                Dist.add(temp);
            }
        }
        ArrayList<Node> Visited = new ArrayList<>();
        
        dijk(Dist, from, dest, Visited);
    }
    
    void dijk(PriorityQueue<Distance> Dist, String from, String dest, ArrayList<Node> Visited){//kaya nya ga jadi pake arraylist
        
        Visited.add(NodeList.get(from));
        Distance tempDist;
        Adj tempAdj;
        Node tempNode;
        Iterator<Adj> iterator = NodeList.get(from).AdjList.iterator();
        while(iterator.hasNext()){
            tempAdj = iterator.next();
            tempDist = new Distance(tempAdj.tujuan, tempAdj.weight);
            Dist.add(tempDist);
        }
        
        System.out.println(Dist.poll().dist);
        
        
    }
    
    
    
}
