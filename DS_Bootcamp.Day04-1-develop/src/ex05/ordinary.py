#!/usr/bin/env python3
import sys
import psutil

def file_read(file_path):
    my_list =  []

    try:

        with open(file_path,"r") as file:
            my_list.append(file.readlines())
    
    except FileNotFoundError as e:
        print(f"Error: {e}")
    
    

    return my_list



def main():
    if len(sys.argv) !=2 :
        print("Использование: ./ordinary <file_path>")
        sys.exit(1)
    
    file_path = sys.argv[1]
    spis = file_read(file_path)
    process = psutil.Process()

    for i in spis:
        pass

    memory = process.memory_info().rss
    cpu = process.cpu_times().user + process.cpu_times().system
    
    print(f'Peak Memory Usage = {(memory / 1024 ** 3):.3f} GB')
    print(f'User Mode Time + System Mode Time = {cpu:.2f}s')

    
        
        
if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)