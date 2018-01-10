/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package transjakarta_v2;

/**
 *
 * @author Lenovo
 */
public class Distance implements Comparable<Distance>{
    String name;
    Integer dist;
    
    Distance(String name, int dist){
        this.name = name;
        this.dist = dist;
    }

    @Override
    public int compareTo(Distance o) {
        return this.dist.compareTo(o.dist);
    }
    
    
    
    
    
}
