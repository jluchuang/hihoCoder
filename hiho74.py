#! /usr/bin/python
import math

def calculate():
    tax = [0, 45, 345, 1245, 7745, 13745, 22495]
    tax_point = {0:3500, 45:5000, 345:8000, 1245:12500, 7745:38500, 13745:58500, 22495:83500}
    tax_rate_point = {0:0, 3500:0.03, 5000:0.1, 8000:0.2, 12500:0.25, 38500:0.3, 58500:0.35, 83500:0.45 }

    value = input()
    wage_base = 0
    wage_max = 3500
    tp = 0
    tp_base = 0
    for i in range(0, len(tax)) :
    	tp = tax[i]
        if (value <= tp): 
            wage_max = tax_point[tp]
            break;
        wage_base = tax_point[tp]
        tp_base = tp

    rate = tax_rate_point[wage_base]
    target = value - tp_base
    
    res = wage_base + target/rate 

    print int(math.floor(res))
    pass

if __name__=="__main__":
    calculate()
