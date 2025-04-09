#!/usr/bin/env python3
import timeit
import sys
from functools import reduce


def loop(num):
    suma = 0
    for i in range(1,num+1):
        suma = suma + i * i
    return suma

def reduce_sum(num):

    numbers = range(1, num + 1)
    result = reduce(lambda x, y: x + y * y, numbers, 0)
    return result


def main():
    
    try:
        if len(sys.argv)==4:
            functions = ['loop', 'reduce']
            name, count,num = sys.argv[1] , int(sys.argv[2]),int(sys.argv[3])

            if count > 0 and name in functions:
                match name:
                    case 'loop':
                        time = timeit.timeit(lambda: loop(num), number = count)
                        
                    case 'reduce':
                        time = timeit.timeit(lambda: reduce_sum(num), number = count)

                print(f'{time:.6f}')
            else:
                print("There is no such function or time lower 0")
                sys.exit(1)
        else:
            print("Use: ./benchmark <loop> 100 5")
            sys.exit(1)
    except ValueError as e:
        print(f'{e}')


if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
    
