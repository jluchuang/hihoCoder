#! /usr/bin/python
import sys

comps = [[] for i in range (100001)]
edgeNum = [0 for i in range (100001)]
virus = [0 for i in range(100001)]

def delete(nodeNo):
    for i in range(len(comps[nodeNo])):
        # add virus for target
        virus[comps[nodeNo][i]-1] += virus[nodeNo]
        # delete target node's input edge
        edgeNum[comps[nodeNo][i]-1] -= 1

def topologicalSorting (n):
    flag = [0 for i in range(n)]
    for j in range(n-1):
        for i in range(n):
            if (edgeNum[i] == 0) and (flag[i] == 0):
                flag[i] = 1
                delete(i)
                #print virus
    sum = 0
    for i in range(n):
        sum += virus[i];
    return sum % 142857

if __name__=="__main__":
    n, m, k = map(int, raw_input().split())
    
    # initialize virus in node
    num = map(int, raw_input().split())
    for i in range(len(num)):
        virus[num[i]-1] = 1
    #print virus
    for i in range(0, m):
        edge = map(int, raw_input().split())
        comps[edge[0]-1].append(edge[1])
        edgeNum[edge[1]-1] += 1 
    print topologicalSorting(n)



