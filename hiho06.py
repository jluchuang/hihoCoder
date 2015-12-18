#! /usr/bin/python
import sys
# TLE 16715ms
def dp():
    array = [0 for i in range(1000010)] 
    need = []
    value = []

    n, m = map(int, sys.stdin.readline().split())
    
    for i in range(0, n):  
        temp_need, temp_value = map(int, sys.stdin.readline().split())
        need.append(temp_need)
        value.append(temp_value)

    # dp
    for i in range(1, n+1):
        for j in range(m+1, need[i-1], -1): 
            if array[j] < array[j-need[i-1]] + value[i-1]:
                array[j] = array[j-need[i-1]] + value[i-1]

    print array[m]

if __name__=="__main__":
    dp()
