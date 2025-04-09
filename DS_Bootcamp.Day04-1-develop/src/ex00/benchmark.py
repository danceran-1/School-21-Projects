#!/usr/bin/env python3
import timeit

def just_append(emails_new):
    listik = []
    for email in emails_new:
        if email.endswith("gmail.com"):
            listik.append(email)

    return listik
    


def comprehension(emails_new):
    my_list = [email for email in emails_new if email.endswith("gmail.com")]
    
    return my_list


def main():
    emails = ['john@gmail.com', 'james@gmail.com', 'alice@yahoo.com', 
'anna@live.com', 'philipp@gmail.com']
    
    emails_new = []
    for i in emails:
        for j in emails:
            emails_new.append(i)


    time1 = timeit.timeit(lambda: just_append(emails_new), number=90000000)
    time2 = timeit.timeit(lambda: comprehension(emails_new), number=90000000)
    
    if time1 <= time2: print('it is better to use a list loop')
    else: print('it is better to use a list comprehension')
    print(f'{time2:.6f} vs {time1:.6f}')

if __name__ == '__main__':
    main()
    
