#!/usr/bin/env python3

import timeit
import random
from collections import Counter


def from_list_to_dict(list_my):
    ditct_my = {}
    for i in list_my:
        ditct_my[i] = list_my.count(i)
    return (ditct_my,"\n" ,"-"*15)


def best_ten(my_list):
    temp = my_list
    ten_best = []
    ditct_my = {}

    for i in range(10):
        popular = max(my_list, key= my_list.count)
        a = popular
        for k in range(my_list.count(a)):
            ten_best.append(a)
        for k in range(my_list.count(a)): 
            temp.remove(a)

    for i in ten_best:
        ditct_my[i] = ten_best.count(i)

    return (ditct_my,"*"*20)
        
def counter_from_list_to_dict(my_list):

    return (Counter(my_list))
    
    
def counter_best_ten(my_list):

    counter = Counter(my_list)  
    most_common = counter.most_common(10)  
    return (dict(most_common))  

        
        


def main():

    my_list = [random.randint(0,100) for _ in range(50)]
    
                    
    time1 = timeit.timeit(lambda: from_list_to_dict(my_list), number = 2)
    
    time2 = timeit.timeit(lambda: best_ten(my_list), number = 2)
    
    time3 = timeit.timeit(lambda: counter_from_list_to_dict(my_list), number = 2)

    time4 = timeit.timeit(lambda: counter_best_ten(my_list), number = 2)

    print(f"my function: {time1:.6f} \nCounter: {time3:.6f} \nmy top: {time2:.6f} \nCounter's top {time4:.6f}")


  
    
if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
    
