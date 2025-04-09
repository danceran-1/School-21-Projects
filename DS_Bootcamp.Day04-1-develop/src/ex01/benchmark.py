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

def mapik(emails_new):
    my_list = list(map(lambda email: email if email.endswith("gmail.com") else None, emails_new))
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
    time3 = timeit.timeit(lambda: mapik(emails_new), number=90000000)

    time_expend = sorted([time1,time2,time3])

    if time1 <= time2 and time1 <= time3:
        print("it is better to use a list loop")
    elif time2 <= time1 and time2 <= time3:
        print("it is better to use a list comprehension")
    else:
        print("it is better to use a map")
    
    print(f'{time_expend[0]:.6f} vs {time_expend[1]:.6f} vs {time_expend[2]:.6f}')

if __name__ == '__main__':
    main()
    
