#! /usr/bin/python

import sys 

def calc(k, n): 
    if n == 0:
        return 0
    if k%4 == 2 or k%4 == 3:
        return n
    return calc((k+3)/4, n-1)

if __name__=="__main__":
    t = input()
    while t > 0 :
        k,n = map(int, raw_input().split())
        print calc(k,n)
        t = t - 1    
              

