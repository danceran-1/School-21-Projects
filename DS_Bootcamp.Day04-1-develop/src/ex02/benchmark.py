#!/usr/bin/env python3
import timeit
import sys


def just_append(emails_new):
    listik = []
    for email in emails_new:
        if email.endswith("gmail.com"):
            listik.append(email)

    return listik
    


def comprehension(emails_new):
    return [email for email in emails_new if email.endswith("gmail.com")]
    


def mapik(emails_new):
    return list(map(lambda email: email if email.endswith("gmail.com") else None, emails_new))
    

def filterik(emails_new):
    return list(filter(lambda email: email.endswith("gmail.com"), emails_new))
    


def main():
    emails = ['john@gmail.com', 'james@gmail.com', 'alice@yahoo.com', 
'anna@live.com', 'philipp@gmail.com']
    
    emails_new = []
    for i in emails:
        for j in emails:
            emails_new.append(i)
    try:
        if len(sys.argv)==3:
            functions = ['loop', 'list_comprehension', 'map', 'filter']
            name, count = sys.argv[1] , int(sys.argv[2])
        
            if count > 0 and name in functions:
                match name:
            
                    case 'loop':
                        time = timeit.timeit(lambda: just_append(emails_new), number = count)
                        
                    case 'list_comprehension':
                        time = timeit.timeit(lambda: comprehension(emails_new), number = count)

                    case 'map':
                        time = timeit.timeit(lambda: mapik(emails_new), number = count)

                    case 'filter':
                        time = timeit.timeit(lambda: filterik(emails_new), number = count)

                print(f'{time:.6f}') 
            else: 
                print("There is no such function or time lower 0")
                sys.exit(1)
        else:
            print("Использование: ./benchmark <loop> 100")
            sys.exit(1)
    except ValueError as e:
        print(f'{e}')


if __name__ == '__main__':
    main()
    
