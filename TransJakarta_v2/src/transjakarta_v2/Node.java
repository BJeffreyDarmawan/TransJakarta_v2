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
public class Node {
    String id;
    ArrayList<Adj> AdjList;
    
    Node(String nama){
        this.id=nama;
        this.AdjList = new ArrayList<Adj>();
    }
    
    void add_adj(Node tujuan, int weight, int line){
        AdjList.add(new Adj(tujuan, weight, line));
    }
    
}
