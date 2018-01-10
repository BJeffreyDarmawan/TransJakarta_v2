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
public class Adj {
    String tujuan;
    int weight;
    int line;
    
    Adj(String tujuan, int weight, int line){
        this.tujuan = tujuan;
        this.weight = weight;
        this.line = line;
        System.out.println(this.weight);
    }
}
