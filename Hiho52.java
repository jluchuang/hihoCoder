/****************************************************
        coding: utf-8
        Author: jluchuang
        File Name: hiho52.java
        Email: jlu_chuang@163.com
        Last modified: 2016-01-12 17:08
*****************************************************/

import java.util.Scanner; 
import java.util.List;
import java.util.ArrayList;  
public class Hiho52{
    
    public class Edge{ 
        public int tar; 
        public Edge next;
        public Edge(int _tar) {
            this.tar = _tar; 
            this.next = null;
        } 
    };
    
    public class EdgeRes {
        public int tar; 
        public int src; 
        public EdgeRes(int _tar, int _src){
            tar = _tar;
            src = _src; 
        }
    };
   
    public int n; 
    public int m; 
    int[] index; 
    int[] lowIndex; 
    int[] parent; 
    Edge[] adj;
    List<Integer> nodeRes = new ArrayList<Integer>(); 
    List<EdgeRes> edgeRes = new ArrayList<EdgeRes>();  
    int globalIndex = 0;
    public Hiho52(int _n, int _m) {
        n = _n; 
        m = _m; 
        index = new int[n];
        lowIndex = new int[n];
        adj = new Edge[n];
        // System.out.println(adj.get(0));
        for(int i = 0; i < n; i ++) {
            index[i] = -1; 
            lowIndex[i] = 0;
            parent[i] = -1;  
            adj[n] = null;
        }  
    }    
     
    public void addEdge(int src, int tar) {
        Edge edge = new Edge(tar);
        edge.next = adj[src]; 
        adj[src] = edge; 
    }

    public void addNodeRes(int v) {
        for(int i = 0; i < nodeRes.size(); i++){
            if(v < nodeRes.get(i)) {
                nodeRes.add(i, v); 
            }
        }
    }    

    public void addEdgeRes(EdgeRes edge) {
        int i = 0;
        for (i = 0; i < edgeRes.size(); i++){
            if(edge.src < edgeRes.get(i).src) {
                break;
            } 
            else {
                if(edge.src == edgeRes.get(i).src && edge.tar < edgeRes.get(i).tar) { 
                    break; 
                }
            }
        } 
        edgeRes.add(i, edge);
    }
    
    public void dfs(int u) {
        int children = 0; 
        
        index[u] = lowIndex[u] = ++ globalIndex; 
        
        Edge tmp = adj[u];
        while (tmp != null) {
            int v = tmp.tar; 
            if(index[u] == -1) {
                children ++; 
                parent[v] = u;
                dfs[v]; 
                
                if(lowIndex[v] < lowIndex[u]) {
                    lowIndex[v] = lowIndex[u]; 
                }
                
                if(parent[u] == null && children > 1) {
                    addNodeRes(u); 
                }
                
                if(parent[u] != null && lowIndex[v] >= index[u]) {
                    addNodeRes(u);
                }
                        
                if(lowIndex[v] > index[u]) {
                    addEdgeRes(new EdgeRes(u, v)); 
                }
            } 
            else {
                if(v != parent[u]) {
                     if(lowIndex[u] < index[v]) {
                         lowIndex[u] = index[v];
                     }
                }
            } 
            tmp = tmp.next; 
        }        
    }    

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in); 
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        // System.out.println(n);
        Hiho52 testcase = new Hiho52(n, m);
        for(int i = 0; i < testcase.m; i ++) {
            int src = scanner.nextInt(); 
            int tar = scanner.nextInt(); 
            testcase.addEdge(src - 1, tar - 1);
            testcase.addEdge(tar - 1, src - 1);  
        } 
    }
}
