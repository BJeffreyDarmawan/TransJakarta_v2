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
public class main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here Map<String, String> unsortMap = new HashMap<String, String>();
        
        Graph g = new Graph();
        
        Node a = new Node("halte1");   
        g.add_node(a);
        a = new Node("halte2");
        g.add_node(a);
        a = new Node("halte3");
        g.add_node(a);
        a = new Node("halte4");
        g.add_node(a);
        a = new Node("halte5");
        g.add_node(a);
        a = new Node("halte6");
        g.add_node(a);
        a = new Node("halte7");
        g.add_node(a);
        a = new Node("halte8");
        g.add_node(a);
        a = new Node("halte9");
        g.add_node(a);
        a = new Node("halte10");
        g.add_node(a);
        
        //from, to, weight, line
        g.add_edge("halte1", "halte2", 9, 0);
        g.add_edge("halte1", "halte3", 1, 0);
        g.add_edge("halte1", "halte4", 5, 0);
        g.add_edge("halte2", "halte3", 2, 0);
        g.add_edge("halte2", "halte5", 5, 0);
        g.add_edge("halte3", "halte4", 5, 0);
        g.add_edge("halte3", "halte5", 5, 0);
        g.add_edge("halte3", "halte6", 5, 0);
        g.add_edge("halte4", "halte6", 5, 0);
        
        g.show_adjList();
        
        g.find_route("halte1", "halte2");
        
////        unsortMap.put("D", "d");
////        unsortMap.put("E", "e");
////        unsortMap.put("Y", "y");
////        unsortMap.put("N", "n");
////        unsortMap.put("J", "j");
////        unsortMap.put("M", "m");
////        unsortMap.put("F", "f");
//
//        System.out.println("Unsort Map......");
//        printMap(unsortMap);
//
//        System.out.println("\nSorted Map......By Key");
//        Map<String, Node> treeMap = new TreeMap<String, Node>(unsortMap);
//        printMap(treeMap);

    }

    //pretty print a map
//    public static <K, V> void printMap(Map<K, V> map) {
//        for (Map.Entry<K, V> entry : map.entrySet()) {
////            System.out.println("Key : " + entry.getKey()
////				+ " Value : " + entry.getValue());
//            Node a = (Node) entry.getValue();
//            Iterator<Adj> iterator = a.AdjList.iterator();
//            while(iterator.hasNext()){
//                System.out.println("abc");
//                System.out.print(iterator.next().tujuan);
//            }
//            System.out.println("");
//            
//        }
//    }
    
}
