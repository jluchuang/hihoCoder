#! /usr/bin/python

# TLE 14075ms 

def topologicalSorting(n, adj, indegree):
    flag = [0 for i in range(n)]
    
    # initialize Queue with zero indegree
    zeroQ = []
    for i in range(n):
        if indegree[i] == 0:
            zeroQ.append(i)
    
    while len(zeroQ) != 0:
        cur = zeroQ[0]
        for i in range(len(adj[cur])):
            indegree[adj[cur][i]] -= 1
            if indegree[adj[cur][i]] == 0:
                zeroQ.append(adj[cur][i])
        del zeroQ[0]
        flag[cur] = 1
    
    for i in range(n):
        if flag[i] == 0:
            print 'Wrong'
            return 
    print 'Correct'
    

if __name__=="__main__":
    t = int(raw_input())
    for i in range(t):
        n, m = map(int, raw_input().split())
        
        # initialize Adjacency table
        adj = [[] for k in range(n)]
        # initialize indegree for each node 
        indegree = [0 for k in range(n)]
        
        for j in range(m):
            src, tar = map(int, raw_input().split())
            adj[src-1].append(tar-1)
            indegree[tar-1] += 1
        topologicalSorting(n, adj, indegree)
